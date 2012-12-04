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

			searchForGroup->addButton(ui->titleButton, 1);
			searchForGroup->addButton(ui->artistButton, 2);
			searchForGroup->addButton(ui->searchInAllButton, 3);

			searchTypeGroup->addButton(ui->ultraStarButton, 1);
			searchTypeGroup->addButton(ui->midiButton, 2);
			searchTypeGroup->addButton(ui->anyTypeButton, 3);
		}

		SongSearch::~SongSearch()
		{
			delete ui;
		}

		void SongSearch::on_pushButton_clicked()
		{
			//httpHandler.postRequest("http://ultrastar-base.com/index.php?section=search_result");
			currSite = 0;
			resultCount = 0;
			resultString = "";
			searchResults.clear();
			getSearchSites();
			getNextSearch();
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
			else displayResults();
		}

		void SongSearch::gotResponse(QString response)
		{
			QRegExp regExp(searchSites[currSite].regExp);
			QStringList results;
			int pos = 0;
			int resultNo = 0;

			while ((pos = regExp.indexIn(response, pos)) != -1)
			{
				for(int i = 0; i < searchSites[currSite].resultGroups.size(); i++)
				{
					if(!searchSites[currSite].resultGroups.at(i).isEmpty())
						searchResults[QString("%1:%2").arg(resultNo).arg(searchSites[currSite].resultGroups.at(i))] = regExp.cap(i);
				}
				results << regExp.cap(0);
				pos += regExp.matchedLength();
				resultNo++;
			}

			for(int x = resultCount; x < resultCount + resultNo && x < maxResults; x++)
			{
				QString key = QString("%1:%2").arg(x);
				resultString += QString("<tr><td>%1</td><td><a href=\"%2\">%3</a></td><td>%4</td></tr>")
						.arg(searchResults[key.arg("Artist")])
						.arg(searchResults[key.arg("RelativeLink")].isEmpty() ?
								searchResults[key.arg("AbsoluteLink")] :
								searchSites[currSite].baseUrl + searchResults[key.arg("RelativeLink")]
							)
						.arg(searchResults[key.arg("Title")])
						.arg(searchResults[key.arg("Size")]);
			}

			resultCount = resultNo;
			currSite++;
			getNextSearch();
		}

		void SongSearch::displayResults()
		{
			ui->label->setText(QString("<html><body><table>%1</table></body></html>").arg(resultString));
		}

	}
}
