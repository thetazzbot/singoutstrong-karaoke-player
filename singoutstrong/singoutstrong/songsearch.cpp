#include "songsearch.h"
#include "ui_songsearch.h"

namespace SoS
{
	namespace QtGui
	{

		SongSearch::SongSearch(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::SongSearch),
			searchForGroup(new QButtonGroup()),
			searchTypeGroup(new QButtonGroup()),
			maxResults(10)
		{
			ui->setupUi(this);

			allowShow = true;
			setSubWidgets(ui->windowBar, ui->content);
			connect(&httpHandler, SIGNAL(receivedResponse(QString)),
					this, SLOT(gotResponse(QString)));
			connect(&httpHandler, SIGNAL(responseError(QString)),
					this, SLOT(gotError(QString)));

			searchForGroup->addButton(ui->titleButton, 1);
			searchForGroup->addButton(ui->artistButton, 2);
			searchForGroup->addButton(ui->searchInAllButton, 3);

			searchTypeGroup->addButton(ui->ultraStarButton, 1);
			searchTypeGroup->addButton(ui->midiButton, 2);
			searchTypeGroup->addButton(ui->anyTypeButton, 3);

			ui->resultTable->resizeColumnsToContents();
			QHeaderView *headerView = ui->resultTable->horizontalHeader();
			headerView->setResizeMode(QHeaderView::Stretch);
			headerView->setResizeMode(2, QHeaderView::Interactive);
			headerView->setResizeMode(4, QHeaderView::Interactive);

			waitAnimationLabel = new QLabel(ui->content);
			waitAnimationLabel->setObjectName("loadAnimLabel");
			waitAnimationLabel->setMovie(new QMovie("./skins/wait.gif"));
			waitAnimationLabel->setAlignment(Qt::AlignCenter);
			waitAnimationLabel->movie()->start();
			ui->gridLayout->addWidget(waitAnimationLabel, 3, 0, 1, 4);
			waitAnimationLabel->hide();
		}

		SongSearch::~SongSearch()
		{
			delete ui;
		}

		void SongSearch::on_pushButton_clicked()
		{
			currSite = 0;
			while(ui->resultTable->rowCount() > 0) ui->resultTable->removeRow(0);
			waitAnimationLabel->show();
			getSearchSites();
			getNextSearch();
			ui->pushButton->setEnabled(false);
		}

		void SongSearch::getSearchSites()
		{
			searchSites.clear();
			QFile file("searchsites.xml");

			if(file.open(QIODevice::ReadOnly))
			{
				QDomDocument doc("SearchSites");
				doc.setContent(&file);
				file.close();

				QDomElement docElement = doc.documentElement();

				QDomNode node = docElement.firstChildElement("Site");
				while(!node.isNull())
				{
					SearchSite site;
					site.requestType = node.attributes().namedItem("Request").nodeValue() == "POST" ?
								HttpHandler::REQUEST_POST : HttpHandler::REQUEST_GET;
					site.songType = node.attributes().namedItem("Type").nodeValue();
					site.baseUrl = node.attributes().namedItem("BaseUrl").nodeValue();
					site.searchUrl = node.attributes().namedItem("SearchUrl").nodeValue();
					site.searchForParamNames = node.attributes().namedItem("SearchForParamNames").nodeValue().split(';');
					site.searchForParamValues = node.attributes().namedItem("SearchForParamValues").nodeValue().split(';');
					site.queryParamName = node.attributes().namedItem("QueryParamName").nodeValue();
					site.regExp = node.attributes().namedItem("Regex").nodeValue();
					site.resultGroups = node.attributes().namedItem("Groups").nodeValue().split(';');
					searchSites.append(site);
					node = node.nextSiblingElement();
				}
			}
		}

		void SongSearch::getNextSearch()
		{
			if(currSite < searchSites.size())
			{
				QUrl request = searchSites[currSite].searchUrl;
				request.addQueryItem(searchSites[currSite].queryParamName, ui->lineEdit->text());

				int searchForIndex = searchForGroup->checkedId() - 1;
				if(searchForIndex >= 0 && searchForIndex < searchSites[currSite].searchForParamNames.size())
					request.addQueryItem(searchSites[currSite].searchForParamNames[searchForIndex],
										 searchSites[currSite].searchForParamValues[searchForIndex]);

				httpHandler.sendRequest(searchSites[currSite].requestType, request);
			}
			else
			{
				ui->pushButton->setEnabled(true);
				waitAnimationLabel->hide();
			}
		}

		void SongSearch::gotResponse(QString response)
		{
			waitAnimationLabel->hide();
			QRegExp regExp(searchSites[currSite].regExp);
			int pos = 0;

			while ((pos = regExp.indexIn(response, pos)) != -1)
			{
				int row = ui->resultTable->rowCount();
				QTextDocument htmlEscape;
				ui->resultTable->insertRow(row);
				for(int i = 0; i < searchSites[currSite].resultGroups.size(); i++)
				{
					QTableWidgetItem* item = new QTableWidgetItem(regExp.cap(i));
					item->setTextAlignment(Qt::AlignCenter);

					if(searchSites[currSite].resultGroups[i] == "Artist")
						ui->resultTable->setItem(row, 0, item);
					else if(searchSites[currSite].resultGroups[i] == "Title")
						ui->resultTable->setItem(row, 1, item);
					else if(searchSites[currSite].resultGroups[i] == "Size")
						ui->resultTable->setItem(row, 2, item);
					else if(searchSites[currSite].resultGroups[i] == "AbsoluteLink")
					{
						htmlEscape.setHtml(regExp.cap(i));
						item->setText(QUrl(htmlEscape.toPlainText()).host());
						item->setData(Qt::UserRole, htmlEscape.toPlainText());
						ui->resultTable->setItem(row, 3, item);
					}
					else if(searchSites[currSite].resultGroups[i] == "RelativeLink")
					{
						htmlEscape.setHtml(searchSites[currSite].baseUrl + regExp.cap(i));
						item->setText(QUrl(htmlEscape.toPlainText()).host());
						item->setData(Qt::UserRole, htmlEscape.toPlainText());
						ui->resultTable->setItem(row, 3, item);
					}
					else
					{
						if(!ui->resultTable->item(row, 4))
						{
							item->setText(searchSites[currSite].songType);
							ui->resultTable->setItem(row, 4, item);
						}
						else delete item;
					}
				}

				pos += regExp.matchedLength();
			}

			currSite++;
			getNextSearch();
		}

		void SongSearch::gotError(QString error)
		{
			int row = ui->resultTable->rowCount();
			ui->resultTable->insertRow(row);
			ui->resultTable->setItem(row, 0, new QTableWidgetItem("Error!"));
			ui->resultTable->setItem(row, 1, new QTableWidgetItem(error));

			currSite++;
			getNextSearch();
		}

		void SongSearch::on_resultTable_itemClicked(QTableWidgetItem *item)
		{
			if (item > 0)
				QDesktopServices::openUrl(ui->resultTable->item(item->row(), 3)->data(Qt::UserRole).toString());
		}
	}
}


