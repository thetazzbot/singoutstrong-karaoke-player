/** @file sosnoteswidget.h
 * Header file with the SoSNotesWidget class
*/

#ifndef SOSEXCERCISEWIDGET_H
#define SOSEXCERCISEWIDGET_H

#include <QGLWidget>
#include "soscontext.h"
#include <QStyle>
#include <QtGui>

/** @def NOTE_MARIGIN
 * @brief The size of the marigin on each side (top, and bottom) for displaying notes and the PitchRecord */

/** @def TOTAL_MARIGINS
 * @brief The combined size of both top and bottom marigins */

#define NOTE_MARIGIN 2
#define TOTAL_MARIGINS NOTE_MARIGIN * 2

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
		 * @brief Widget for displaying song's notes
		 *
		 */
		class SoSNotesWidget : public QGLWidget
		{
				Q_OBJECT

				Q_PROPERTY(QBrush noteColor READ getNoteColor WRITE setNoteColor)
				Q_PROPERTY(QBrush selectionColor READ getSelectionColor WRITE setSelectionColor)

				Q_PROPERTY(QBrush recPerfectColor READ getRecPerfectColor WRITE setRecPerfectColor)
				Q_PROPERTY(QBrush recGoodColor READ getRecGoodColor WRITE setRecGoodColor)
				Q_PROPERTY(QBrush recOkColor READ getRecOkColor WRITE setRecOkColor)
				Q_PROPERTY(QBrush recPoorColor READ getRecPoorColor WRITE setRecPoorColor)
				Q_PROPERTY(QBrush recBadColor READ getRecBadColor WRITE setRecBadColor)

				Q_PROPERTY(QImage indicator READ getIndicator WRITE setIndicator)
				Q_PROPERTY(QImage indicator_inactive READ getIndicatorInactive WRITE setIndicatorInactive)
				Q_PROPERTY(QImage indicator_high READ getIndicatorHigh WRITE setIndicatorHigh)
				Q_PROPERTY(QImage indicator_high_inactive READ getIndicatorHighInactive WRITE setIndicatorHighInactive)
				Q_PROPERTY(QImage indicator_low READ getIndicatorLow WRITE setIndicatorLow)
				Q_PROPERTY(QImage indicator_low_inactive READ getIndicatorLowInactive WRITE setIndicatorLowInactive)

			protected:
				QBrush noteColorVar;				/**< @brief Stores the note color */
				QBrush selectionColorVar;			/**< @brief Stores the selection color */

				QBrush recPerfectColorVar;			/**< @brief Stores the color of the pitchSample with perfect accuracy */
				QBrush recGoodColorVar;				/**< @brief Stores the color of the pitchSample with good accuracy */
				QBrush recOkColorVar;				/**< @brief Stores the color of the pitchSample with ok accuracy */
				QBrush recPoorColorVar;				/**< @brief Stores the color of the pitchSample with poor accuracy */
				QBrush recBadColorVar;				/**< @brief Stores the color of the pitchSample with bad accuracy */

				QImage indicatorVar;				/**< @brief Stores the indicator image */
				QImage indicatorInactiveVar;		/**< @brief Stores the inactive indicator */
				QImage indicatorHighVar;			/**< @brief Stores the indicator image showing the current sample is over widget's bounds */
				QImage indicatorHighInactiveVar;	/**< @brief Stores the inactive indicator image showing the last sample was over widget's bounds */
				QImage indicatorLowVar;				/**< @brief Stores the indicator image showing the current sample is under widget's bounds */
				QImage indicatorLowInactiveVar;		/**< @brief Stores the inactive indicator image showing the last sample was under widget's bounds */

				SoSContext* sosContext;				/**< @brief The context storing interfaces to the Core library*/
				QList<int> lineYs;					/**< @brief List of Y coordinates of note lines (drawn in background) */
				int lineHeight;						/**< @brief The distance between the note lines */

				const ISong* song;					/**< @brief The song */
				const ISongSettings* settings;		/**< @brief The song settings */
				const ITrack* track;				/**< @brief The currently selected track, that will be drawn */

				float widthMultiplier;				/**< @brief Multiplier for translating timestampes into x coordinates */
				float timeOffset;					/**< @brief ViewedTime offset, for translating timestamps into x coordinates */
				float pitchMultiplier;				/**< @brief Multiplier for translating pitches into y coordinates */
				float notesRange;					/**< @brief The range of the currently selected track's notes + marigin defined in TOTAL_MARIGINS */
				float currPitchY;					/**< @brief The y coordinate of the last detected pitch from the audio analyzer */

				/**
				 * @brief Draws the note lines
				 *
				 * @param event
				 * @param painter
				 */
				void drawNoteLines(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Draws the selection of a section
				 *
				 * @param event
				 * @param painter
				 */
				void drawSelection(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Draws the track notes
				 *
				 * @param event
				 * @param painter
				 */
				void drawTrack(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Draws the time cursor
				 *
				 * @param event
				 * @param painter
				 */
				void drawTimeLine(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Draws the PitchRecord
				 *
				 * @param event
				 * @param painter
				 */
				void drawRecord(QPaintEvent* event, QPainter* painter);

				/**
				 * @brief Translates x coordinates into time in miliseconds
				 *
				 * @param x The coordinate
				 * @return long The time
				 */
				long xToTime(float x);

				/**
				 * @brief Translates the time in miliseconds into x coordinates
				 *
				 * @param time The time
				 * @return float The coordinate
				 */
				float timeToX(long time);

			public:

				explicit SoSNotesWidget(QWidget *parent = 0);

				/**
				 * @brief Sets the context storing interfaces to the Core library
				 *
				 * @param context
				 */
				void setSoSContext(SoSContext* context);

				/**
				 * @brief Gets the note bar's color
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush The current note color
				 */
				QBrush getNoteColor();

				/**
				 * @brief Sets the note bar's color
				 *
				 * Set by the stylesheet.
				 *
				 * @param c The new note color
				 */
				void setNoteColor(QBrush c);

				/**
				 * @brief Gets the selection color
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush The current selection color
				 */
				QBrush getSelectionColor();

				/**
				 * @brief Sets the selection color
				 *
				 * Set by the stylesheet.
				 *
				 * @param c The new selection color
				 */
				void setSelectionColor(QBrush c);

				/**
				 * @brief Get's the color the PitchSample with a perfect accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush
				 */
				QBrush getRecPerfectColor();

				/**
				 * @brief Set's the color the PitchSample with a perfect accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @param c
				 */
				void setRecPerfectColor(QBrush c);

				/**
				 * @brief Get's the color the PitchSample with a good accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush
				 */
				QBrush getRecGoodColor();

				/**
				 * @brief Set's the color the PitchSample with a good accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @param c
				 */
				void setRecGoodColor(QBrush c);

				/**
				 * @brief Get's the color the PitchSample with a ok accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush
				 */
				QBrush getRecOkColor();

				/**
				 * @brief Set's the color the PitchSample with a ok accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @param c
				 */
				void setRecOkColor(QBrush c);

				/**
				 * @brief Get's the color the PitchSample with a poor accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush
				 */
				QBrush getRecPoorColor();

				/**
				 * @brief Set's the color the PitchSample with a poor accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @param c
				 */
				void setRecPoorColor(QBrush c);

				/**
				 * @brief Get's the color the PitchSample with a bad accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @return QBrush
				 */
				QBrush getRecBadColor();

				/**
				 * @brief Set's the color the PitchSample with a bad accuracy will be drawn with
				 *
				 * Set by the stylesheet.
				 *
				 * @param c
				 */
				void setRecBadColor(QBrush c);

				/**
				 * @brief Get's the image of the current pitch indicator
				 *
				 * Set by the stylesheet.
				 *
				 * @return QImage
				 */
				QImage getIndicator();

				/**
				 * @brief Set's the image of the current pitch indicator
				 *
				 * Set by the stylesheet.
				 *
				 * @param i
				 */
				void setIndicator(QImage i);

				/**
				 * @brief Get's the image of the current pitch indicator
				 *
				 * Set by the stylesheet.
				 *
				 * @return QImage
				 */
				QImage getIndicatorInactive();

				/**
				 * @brief Set's the image of the current pitch indicator
				 *
				 * Set by the stylesheet.
				 *
				 * @param i
				 */
				void setIndicatorInactive(QImage i);

				/**
				 * @brief Get's the image of the current pitch indicator, when the current sample is over the boundaries of the widget
				 *
				 * Set by the stylesheet.
				 *
				 * @return QImage
				 */
				QImage getIndicatorHigh();

				/**
				 * @brief Set's the image of the current pitch indicator, when the current sample is over the boundaries of the widget
				 *
				 * Set by the stylesheet.
				 *
				 * @param i
				 */
				void setIndicatorHigh(QImage i);

				/**
				 * @brief Get's the image of the current pitch indicator, when the last sample was over the boundaries of the widget, and the current sample's volume is below the volume threshold
				 *
				 * Set by the stylesheet.
				 *
				 * @return QImage
				 */
				QImage getIndicatorHighInactive();

				/**
				 * @brief Set's the image of the current pitch indicator, when the last sample was over the boundaries of the widget, and the current sample's volume is below the volume threshold
				 *
				 * Set by the stylesheet.
				 *
				 * @param i
				 */
				void setIndicatorHighInactive(QImage i);

				/**
				 * @brief Get's the image of the current pitch indicator, when the current sample is under the boundaries of the widget
				 *
				 * Set by the stylesheet.
				 *
				 * @return QImage
				 */
				QImage getIndicatorLow();

				/**
				 * @brief Set's the image of the current pitch indicator, when the current sample is under the boundaries of the widget
				 *
				 * Set by the stylesheet.
				 *
				 * @param i
				 */
				void setIndicatorLow(QImage i);

				/**
				 * @brief Get's the image of the current pitch indicator, when the last sample was under the boundaries of the widget, and the current sample's volume is below the volume threshold
				 *
				 * Set by the stylesheet.
				 *
				 * @return QImage
				 */
				QImage getIndicatorLowInactive();

				/**
				 * @brief Set's the image of the current pitch indicator, when the last sample was under the boundaries of the widget, and the current sample's volume is below the volume threshold
				 *
				 * Set by the stylesheet.
				 *
				 * @param i
				 */
				void setIndicatorLowInactive(QImage i);

				/**
				 * @brief Repaints the widget
				 *
				 * @param event
				 */
				void paintEvent(QPaintEvent *event);

				/**
				 * @brief Called when the user presses a mouse button over the widget
				 *
				 * Handles selecting sections of the song.
				 *
				 * @param event
				 */
				void mousePressEvent(QMouseEvent *event);

				/**
				 * @brief Called when the user moves the mouse cursor over the widget
				 *
				 * Handles selecting sections of the song.
				 *
				 * @param event
				 */
				void mouseMoveEvent(QMouseEvent *event);

				/**
				 * @brief Called when the user releases a mouse button over the widget
				 *
				 * Handles selecting sections of the song, and moving the currentTime cursor.
				 *
				 * @param event
				 */
				void mouseReleaseEvent(QMouseEvent *event);

			signals:

			public slots:
		};
	}
}

#endif // SOSEXCERCISEWIDGET_H
