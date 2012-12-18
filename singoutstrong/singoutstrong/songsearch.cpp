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
			maxResults(10),
			currentTask(TT_SEARCH)
		{
			ui->setupUi(this);

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

			ui->searchIcon->setMovie(new QMovie("./skins/search.png"));
			ui->searchIcon->movie()->start();
		}

		SongSearch::~SongSearch()
		{
			delete ui;
		}

		void SongSearch::keyPressEvent(QKeyEvent *event)
		{
			if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
				on_searchButton_clicked();
		}

		void SongSearch::timerEvent(QTimerEvent *event)
		{
			if(event->timerId() == timerId)
			{
				switch(currentTask)
				{
				case TT_CLEAR_RESULTS:
					timedClearResults(95);
					if(ui->resultTable->rowCount() == 0)
						currentTask = TT_SEARCH;
					break;
				case TT_PROCESS_RESULTS:
					timedProcessResponse(50);
					if(regexPos == -1)
					{
						currentTask = TT_SEARCH;
						currentSite++;
					}
					break;
				case TT_SEARCH:
				default:
					this->killTimer(timerId);
					timerId = 0;
					getNextSearch();
					break;
				}
			}
		}

		void SongSearch::setColumnWidhts(QString columnWidths)
		{
			QStringList widths = columnWidths.split(';');
			for(int i = 0; i < widths.size() && i < ui->resultTable->columnCount() - 1; i++)
			{
				ui->resultTable->setColumnWidth(i, widths[i].toInt());
			}
		}

		QString SongSearch::getColumnWidths()
		{
			QString widths = "";
			for(int i = 0; i < ui->resultTable->columnCount()-1; i++)
			{
				widths += QString("%1%2").arg(i > 0 ? ";" : "")
						.arg(ui->resultTable->columnWidth(i));
			}
			return widths;
		}

		void SongSearch::on_searchButton_clicked()
		{
			currentSite = 0;
			ui->searchIcon->setMovie(new QMovie("./skins/wait.gif"));
			ui->searchIcon->movie()->start();
			ui->searchButton->setEnabled(false);
			ui->resultTable->setEnabled(false);
			ui->resultTable->setSortingEnabled(false);
			getSearchSites();
			currentTask = TT_CLEAR_RESULTS;
			timerId = this->startTimer(100);
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
					site.songType = node.attributes().namedItem("Type").nodeValue();

					if(ui->anyTypeButton->isChecked() ||
					   (site.songType == "MIDI" && ui->midiButton->isChecked()) ||
					   (site.songType == "UltraStar" && ui->ultraStarButton->isChecked())
					   )
					{
						site.requestType = node.attributes().namedItem("Request").nodeValue() == "POST" ?
									HttpHandler::REQUEST_POST : HttpHandler::REQUEST_GET;
						site.baseUrl = node.attributes().namedItem("BaseUrl").nodeValue();
						site.searchUrl = node.attributes().namedItem("SearchUrl").nodeValue();
						site.searchForParamNames = node.attributes().namedItem("SearchForParamNames").nodeValue().split(';');
						site.searchForParamValues = node.attributes().namedItem("SearchForParamValues").nodeValue().split(';');
						site.queryParamName = node.attributes().namedItem("QueryParamName").nodeValue();
						site.regExp = node.attributes().namedItem("Regex").nodeValue();
						site.resultGroups = node.attributes().namedItem("Groups").nodeValue().split(';');
						site.additionalParams = node.attributes().namedItem("AdditionalParams").nodeValue().split(';');
						searchSites.append(site);
					}
					node = node.nextSiblingElement();
				}
			}
		}

		void SongSearch::getNextSearch()
		{
			if(currentSite < searchSites.size())
			{
				QUrl request = searchSites[currentSite].searchUrl;
				request.addQueryItem(searchSites[currentSite].queryParamName, ui->queryField->text());

				int searchForIndex = searchForGroup->checkedId() - 1;
				if(searchForIndex >= 0 && searchForIndex < searchSites[currentSite].searchForParamNames.size())
					request.addQueryItem(searchSites[currentSite].searchForParamNames[searchForIndex],
										 searchSites[currentSite].searchForParamValues[searchForIndex]);

				for(int i = 0; i < searchSites[currentSite].additionalParams.count(); i++)
				{
					QStringList paramValue = searchSites[currentSite].additionalParams[i].split("=");
					if(paramValue.count() == 2)
						request.addQueryItem(paramValue[0], paramValue[1]);
				}

				httpHandler.sendRequest(searchSites[currentSite].requestType, request);
			}
			else
			{
				ui->searchButton->setEnabled(true);
				ui->resultTable->setSortingEnabled(true);
				ui->searchIcon->setMovie(new QMovie("./skins/search.png"));
				ui->searchIcon->movie()->start();
			}
		}

		void SongSearch::gotResponse(QString response)
		{
			currentResponse = response;
			regexPos = 0;
			currentTask = TT_PROCESS_RESULTS;
			timerId = this->startTimer(100);
		}

		void SongSearch::timedClearResults(int timeLength)
		{
			long startTime = clock();
			while(clock() - startTime < timeLength && ui->resultTable->rowCount() > 0)
				ui->resultTable->removeRow(0);
		}

		void SongSearch::timedProcessResponse(int timeLength)
		{
			ui->resultTable->setEnabled(true);
			QRegExp regExp(searchSites[currentSite].regExp, Qt::CaseSensitive, QRegExp::RegExp2);
			regExp.setMinimal(true);
			long startTime = clock();

			while (clock() - startTime < timeLength &&
				   (regexPos = regExp.indexIn(currentResponse, regexPos)) != -1)
			{
				int row = ui->resultTable->rowCount();
				QTextDocument htmlEscape;
				ui->resultTable->insertRow(row);
				for(int i = 0; i < searchSites[currentSite].resultGroups.size(); i++)
				{
					htmlEscape.setHtml(regExp.cap(i));
					QTableWidgetItem* item = new QTableWidgetItem(htmlEscape.toPlainText());
					item->setTextAlignment(Qt::AlignCenter);

					if(searchSites[currentSite].resultGroups[i] == "Artist")
						ui->resultTable->setItem(row, 0, item);
					else if(searchSites[currentSite].resultGroups[i] == "Title")
						ui->resultTable->setItem(row, 1, item);
					else if(searchSites[currentSite].resultGroups[i] == "Size")
						ui->resultTable->setItem(row, 2, item);
					else if(searchSites[currentSite].resultGroups[i] == "AbsoluteLink")
					{
						item->setData(Qt::UserRole, item->text());
						item->setText(QUrl(item->text()).host());
						ui->resultTable->setItem(row, 3, item);
					}
					else if(searchSites[currentSite].resultGroups[i] == "RelativeLink")
					{
						htmlEscape.setHtml(searchSites[currentSite].baseUrl + regExp.cap(i));
						item->setData(Qt::UserRole, htmlEscape.toPlainText());
						item->setText(QUrl(htmlEscape.toPlainText()).host());
						ui->resultTable->setItem(row, 3, item);
					}
					else
					{
						if(!ui->resultTable->item(row, 4))
						{
							item->setText(searchSites[currentSite].songType);
							ui->resultTable->setItem(row, 4, item);
						}
						else delete item;
					}
				}

				regexPos += regExp.matchedLength();
			}
		}

		void SongSearch::gotError(QString error)
		{
			int row = ui->resultTable->rowCount();
			ui->resultTable->insertRow(row);
			ui->resultTable->setItem(row, 0, new QTableWidgetItem("Error!"));
			ui->resultTable->setItem(row, 1, new QTableWidgetItem(error));

			currentSite++;
			getNextSearch();
		}

		void SongSearch::on_resultTable_itemClicked(QTableWidgetItem *item)
		{
			if (item > 0)
				QDesktopServices::openUrl(ui->resultTable->item(item->row(), 3)->data(Qt::UserRole).toString());
		}
	}
}


