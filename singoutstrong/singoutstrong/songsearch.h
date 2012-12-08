#ifndef SONGSEARCH_H
#define SONGSEARCH_H

#include "sossubwindow.h"
#include "httphandler.h"
#include <QtXml>
#include <QHash>
#include <QList>
#include <QButtonGroup>
#include <QTableWidget>
#include <QMovie>
#include <QLabel>
#include <QDesktopServices>
#include <QTextDocument>

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
				QString songType;
				QStringList searchForParamNames;
				QStringList searchForParamValues;
				QStringList additionalParams;
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

				void setColumnWidhts(QString columnWidths);
				QString getColumnWidths();

			private slots:
				void gotResponse(QString response);
				void gotError(QString error);
				void on_pushButton_clicked();

				void on_resultTable_itemClicked(QTableWidgetItem *item);

			private:
				Ui::SongSearch *ui;
				HttpHandler httpHandler;
				QList<SearchSite> searchSites;
				QButtonGroup* searchForGroup;
				QButtonGroup* searchTypeGroup;
				QLabel* waitAnimationLabel;
				int currSite;
				int resultCount;
				int maxResults;

				void getSearchSites();
				void getNextSearch();
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SONGSEARCH_H
