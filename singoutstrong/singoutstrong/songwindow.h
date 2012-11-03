/** @file songwindow.h
 * Header file with the SongWindow class
*/

#ifndef SONGWINDOW_H
#define SONGWINDOW_H

#include <QDockWidget>
#include "sossubwindow.h"

/// \cond 0

namespace Ui {
	class SongWindow;
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
		 * @brief Window for displaying the song notes, PitchRecord, and song lyrics
		 *
		 */
		class SongWindow : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit SongWindow(QWidget *parent = 0);
				~SongWindow();

				/**
				 * @brief Initializes the widnow
				 *
				 * Passes the context to the notes and lyrics widgets
				 *
				 * @param context
				 */
				void init(SoSContext *context);

				/**
				 * @brief Updates the widget
				 *
				 * Schedules the widget, and the notes and lyrics widgets for redrawing
				 *
				 */
				void update();

				/**
				 * @brief Called when the window is resized
				 *
				 * Resizes the lyrics and notes widgets
				 *
				 * @param event
				 */
				void resizeEvent(QResizeEvent *event);

				/**
				 * @brief Called when the user doubleclicks on the window
				 *
				 * Hides the title bar, shows an information label, and enters full screen mode.
				 *
				 * @param event
				 */
				void mouseDoubleClickEvent(QMouseEvent *event);

				/**
				 * @brief Called when exiting full screen mode
				 *
				 * Shows the title bar, and hides the information label.
				 *
				 */
				void showNormal();

			public slots:
				/**
				 * @brief Sets the number lines of lyrics in the lyrics widget
				 *
				 * @param number
				 */
				void setTextLines(int number);

			private:
				Ui::SongWindow *ui; /**< @brief Qt's container for the window's subwidgets */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SONGWINDOW_H
