/** @file sossubwindow.h
 * Header file with the SoSSubWindow class
*/

#ifndef SOSSUBWINDOW_H
#define SOSSUBWINDOW_H

#include "soscontext.h"
#include <QSizeGrip>
#include <QResizeEvent>
#include <QFrame>

/// \cond 0

namespace Ui {
	class SoSSubWindow;
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
		 * @brief Class for handling common subwindow widgets and events
		 *
		 */
		class SoSSubWindow : public QFrame
		{
			protected:
				SoSContext* context;	/**< @brief The context storing interfaces to the Core library */
				QSizeGrip* sizeGrip;	/**< @brief The size grip widget of the window */
				QWidget* windowBar;		/**< @brief The title bar of the window */
				QWidget* content;		/**< @brief The container with the window content */
				bool allowShow;			/**< @brief Variable for allowing the window to shown */

				/**
				 * @brief Called when the window is resized
				 *
				 * Resizes the windowBar, content, and moves the sizeGrip to remain at the corner of a window
				 *
				 * @param
				 */
				void resizeEvent(QResizeEvent *);

			public:
				explicit SoSSubWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

				/**
				 * @brief Initializes the window
				 *
				 * Sets the context, and/or does whatever inheriting classes need for initialization.
				 *
				 * @param sosContext
				 */
				virtual void init(SoSContext* sosContext = NULL);

				/**
				 * @brief Sets which widgets are the windowBar and contents, for easy access later
				 *
				 * @param bar
				 * @param content
				 */
				virtual void setSubWidgets(QWidget* bar, QWidget* winContent);

				/**
				 * @brief Gets whether the window can be shown
				 *
				 * @return bool
				 */
				bool getAllowShow();

				/**
				 * @brief Sets whether the window can be shown
				 *
				 * @param v
				 */
				void setAllowShow(bool v);

				/**
				 * @brief Shows the window if allowShow is true
				 *
				 */
				virtual void show();

		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SOS_DOCK_WINDOW_H
