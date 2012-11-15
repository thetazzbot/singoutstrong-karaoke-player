/** @file soslyricswidget.h
 * Header file with the SoSLyricsWidget class
*/

#ifndef SOSLYRICSWIDGET_H
#define SOSLYRICSWIDGET_H

#include <QWidget>
#include <QStyle>
#include <QtGui>
#include "soscontext.h"

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
		 * @brief Widget for displaying the song lyrics
		 *
		 */
		class SoSLyricsWidget : public QWidget
		{
				Q_OBJECT

				Q_PROPERTY(QColor sungTextColor READ getSungTextColor WRITE setSungTextColor)
			public:
				explicit SoSLyricsWidget(QWidget *parent = 0);

				/**
				 * @brief Sets the context storing interfaces to the Core library
				 *
				 * @param context
				 */
				void setSoSContext(const SoSContext *context);

				/**
				 * @brief Gets the sung text color
				 *
				 * @return QColor
				 */
				QColor getSungTextColor();

				/**
				 * @brief Sets the sung text color
				 *
				 * @param value
				 */
				void setSungTextColor(QColor value);

				/**
				 * @brief Sets the number of text lines to be displayed
				 *
				 * @param count
				 */
				void setLineCount(int count);

			protected:
				QList<QStringList> lines; /**< @brief Lines of text to be displayed */

				QPen sungText;			/**< @brief Stores the sung text color */
				int oldStart;			/**< @brief Stores the previous index of the first displayed text data */
				int oldEnd;				/**< @brief Stores the previous index of the last displayed text data */
				int linesTextIndex;		/**< @brief Stores the index of the first displayed TextData*/

				const ISongControl* songControl;	/**< @brief The song control interface*/
				const ISong* song;					/**< @brief The song interface*/
				const ISongSettings* settings;		/**< @brief The song settings interface*/

				/**
				 * @brief Called when the widget is to be repainted
				 *
				 *
				 * @param event
				 */
				void paintEvent(QPaintEvent *event);

				/**
				 * @brief Draws the background
				 *
				 * @param event
				 * @param painter
				 */
				void drawBackground(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Draws the lyrics
				 *
				 * @param event
				 * @param painter
				 */
				void drawLyrics(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Sets the size of the font to fit the widget's size
				 *
				 */
				void setupFont();

				/**
				 * @brief Clears all lines of text
				 *
				 */
				void clearLines();

				/**
				 * @brief Handles the resizing of the widget
				 *
				 * Recalculates the font size.
				 *
				 * @param event
				 */
				void resizeEvent(QResizeEvent *event);

			signals:

			public slots:

		};
	}
}

#endif // SOSLYRICSWIDGET_H
