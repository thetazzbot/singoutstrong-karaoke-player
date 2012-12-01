#ifndef SONGSEARCH_H
#define SONGSEARCH_H

#include "sossubwindow.h"
#include "httphandler.h"

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
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SONGSEARCH_H
