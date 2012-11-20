/** @file tutorialwindow.h
 * Header file with the TutorialWindow class
*/

#ifndef TUTORIALWINDOW_H
#define TUTORIALWINDOW_H

#include "sossubwindow.h"
#include <QWizard>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>

/// \cond 0

namespace Ui {
	class TutorialWindow;
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

		/**
		 * @brief Window for displaying the application tutorial
		 *
		 * The QWizard class was causing some problems on Windows 7, so this tutorial was moved to a custom window. \n
		 * This class tries to load the contents of each page from htm files in the /docs/tutorial directory.
		 * The files should be named after the page number, starting from 0 (e.g.: 0.htm, 1.htm... etc.)
		 */
		class TutorialWindow : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit TutorialWindow(QWidget *parent = 0);
				~TutorialWindow();

				/**
				 * @brief Attempts to show the window (depends on allowShow)
				 *
				 * Shows the wizard widget as well
				 */
				void show();

				void setDocumentName(QString name);
				void setPage(int page);

			signals:
				/**
				 * @brief A signal sent when the wizard page is changed
				 *
				 * @param pageNo The current page number
				 */
				void pageChanged(QString docName, int pageNo);

			private slots:
				/**
				 * @brief Called when the nextButton is clicked
				 *
				 * Moves to the next page, or closes the window if we're on the last page
				 */
				void on_nextButton_clicked();

				/**
				 * @brief Called when the prevButton is clicked
				 *
				 * Moves to the previous page, or closes the window if we're on the first page
				 */
				void on_prevButton_clicked();

				void on_label_linkActivated(const QString &link);

			private:
				Ui::TutorialWindow *ui; /**< @brief Qt's container for the window's subwidgets */
				int pageNumber;			/**< @brief The current page of the wizard */
				QString documentName;

				/**
				 * @brief Tries to load the current page
				 *
				 * Also changes the text on the "Next" and "Previous" buttons to "Finish" when the last page is reached
				 * and "Cancel" if the first page is reached.
				 *
				 * @return bool \c True if the page was loaded successfully, otherwise \c false.
				 */
				bool reload();


		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // TUTORIALWINDOW_H
