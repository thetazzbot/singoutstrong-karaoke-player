/** @file windowbar.h
 * Header file with the WindowBar class
*/

#ifndef WINDOWBAR_H
#define WINDOWBAR_H

#include <QFrame>
#include <QResizeEvent>

/// \cond 0

namespace Ui {
	class WindowBar;
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
		 * @brief The title bar displayed on top of every window
		 *
		 */
		class WindowBar : public QFrame
		{
				Q_OBJECT

			public:
				explicit WindowBar(QWidget *parent = 0);
				~WindowBar();

				/**
				 * @brief Shows the minimize button
				 *
				 */
				void showMinimize();

				/**
				 * @brief Hides the minimize button
				 *
				 */
				void hideMinimize();

			signals:
				/**
				 * @brief A signal emitted when the exit button is pushed
				 *
				 */
				void exitPushed();

			protected:
				/**
				 * @brief Called when the widget is resized
				 *
				 * Rearrenges the buttons so they will always be to the right, and the label width to fit the size of the widget
				 *
				 * @param e
				 */
				void resizeEvent(QResizeEvent *e);

				/**
				 * @brief Called when the user presses the left mouse button over the widget
				 *
				 * Used for moving the whole window.
				 *
				 * @param event
				 */
				void mousePressEvent(QMouseEvent *event);

				/**
				 * @brief Called when the user moves the mouse over the widget
				 *
				 * Used for moving the topWidget.
				 *
				 * @param event
				 */
				void mouseMoveEvent(QMouseEvent *event);

			private slots:

				/**
				 * @brief Called when the user clicks the exitButton
				 *
				 * Closes the topWidget
				 *
				 */
				void on_exitButton_clicked();

				/**
				 * @brief Called when the user clicks the minimizeButton
				 *
				 * Minimizes the topWidget
				 *
				 */
				void on_minimizeButton_clicked();

			private:
				Ui::WindowBar *ui; /**< @brief Qt's container for the window's subwidgets */
				QWidget* topWidget;  /**< @brief The top level widget the title bar belongs to */
				QPoint dragPosition;  /**< @brief The location where dragging the window began */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // WINDOWBAR_H
