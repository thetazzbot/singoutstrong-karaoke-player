#ifndef SONGSEARCH_H
#define SONGSEARCH_H

#include "sossubwindow.h"
#include "httphandler.h"
#include <QtXml>
#include <QHash>
#include <QList>
#include <QButtonGroup>

/// \cond 0

namespace Ui {
	class SongSearch;
}

/// \endcond

/*!
 *  \addtogroup SoS
 *  @{
 */

//! Main SingOutStrong namespace
namespace SoS
{
	/*!
	 *  \addtogroup QtGui
	 *  @{
	 */

	//! User Interface
	namespace QtGui
	{

		struct SearchSite
		{
				HttpHandler::RequestType requestType;
				QString baseUrl;
				QString searchUrl;
				QStringList searchForParamNames;
				QStringList searchForParamValues;
				QString queryParamName;
				QString regExp;
				QStringList resultGroups;
		};

		class SongSearch : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit SongSearch(QWidget *parent = 0);
				~SongSearch();

			private slots:
				void gotResponse(QString response);
				void on_pushButton_clicked();

			private:
				Ui::SongSearch *ui;
				HttpHandler httpHandler;
				QList<SearchSite> searchSites;
				QHash<QString, QString> searchResults;
				QString resultString;
				QButtonGroup* searchForGroup;
				QButtonGroup* searchTypeGroup;
				int currSite;
				int resultCount;
				int maxResults;

				void getSearchSites();
				void getNextSearch();
				void displayResults();
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SONGSEARCH_H
