/** @file generalsettings.h
 * Header file with the GeneralSettings class
*/

#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QDockWidget>
#include <QMainWindow>
#include "highlightlist.h"
#include "sossubwindow.h"

/// \cond 0

namespace Ui {
	class GeneralSettings;
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
		 * @brief The general settings window class
		 *
		 */
		class GeneralSettings : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit GeneralSettings(QWidget *parent = 0);
				~GeneralSettings();

				/**
				 * @brief Shows the window
				 *
				 * Calls refresh() to update the widgets' values, before becoming visible
				 */
				void show();

				/**
				 * @brief Updates the widget's values with the values stored in the SongSettings
				 *
				 */
				void refresh();

				/**
				 * @brief Gets the currently selected skin's name
				 *
				 * @return QString The skin name
				 */
				QString getCurrentSkin();

				/**
				 * @brief Stores the currently selected skin name for future reference
				 *
				 * @param name The current skin name
				 */
				void setCurrentSkin(QString name);

			signals:

				/**
				 * @brief A signal sent when a new skin is set
				 *
				 * @param name The name of the new skin
				 */
				void skinSet(QString name);

				/**
				 * @brief A signal sent when the number of displayed lines of lyrics is changed
				 *
				 * @param number The new number of displayed lines of lyrics
				 */
				void textLinesSet(int number);

			private slots:

				/**
				 * @brief Called when the user moves the latencySlider
				 *
				 * Calls the setOutputLatency method of the ISongSettings interface
				 *
				 * @param value
				 */
				void on_latencySlider_valueChanged(int value);

				/**
				 * @brief Called when the user moves the timeRangeSlider
				 *
				 * Calls the setViewTimeRange method of the ISongSettings interface
				 *
				 * @param value
				 */
				void on_timeRangeSlider_valueChanged(int value);

				/**
				 * @brief Called when the user dounleclicks an intem on the skinList
				 *
				 * Highlights the doubleclicked item (see more in HighlightList), sets the current skin name to the value
				 * of the doubleclicked item, and emits the skinSet signal
				 *
				 * @param item
				 */
				void on_skinsList_itemDoubleClicked(QListWidgetItem *item);

				/**
				 * @brief Called when the user changes the value of the textLinesBox
				 *
				 * Calls the setTextLineCount method of the ISongSettings interface
				 *
				 * @param arg1
				 */
				void on_textLinesBox_valueChanged(int arg1);

				/**
				 * @brief Called when the user changes the value of the groupedByBox
				 *
				 * Calls the setTextGroupBy method of the ISongSettings interface
				 *
				 * @param arg1
				 */
				void on_groupedByBox_valueChanged(int arg1);

			private:
				Ui::GeneralSettings *ui;	/**< @brief Qt's container for the window's subwidgets */
				QString currentSkin;		/**< @brief The name of the currently selected skin */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // GENERALSETTINGS_H
