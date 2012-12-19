/** @file generalsettings.h
 * Header file with the GeneralSettings class
*/

#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QDockWidget>
#include <QMainWindow>
#include "highlightlist.h"
#include "sossubwindow.h"
#include "skinmanager.h"

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
				 * @brief Stores the currently selected skin name for future reference
				 *
				 * @param name The current skin name
				 */
				void setCurrentSkin(QString name);

				/**
				 * @brief Updated the values of child widgets with the values stored in SongSettings
				 *
				 */
				void refreshSettings();

				/**
				 * @brief Highlights the subwidgets for the purposes of the tutorial in the TutorialWindow
				 *
				 * The method sets the \c tutorialHighlight property to the value of the \c active parameter, for the
				 * deviceBox, deviceLabel, and applyButton widgets. \n
				 * This allows these widgets to be highlighted when the user enters the seocnd page of the TutorialWizard. \n\n
				 * You can set the style of these widgets while in tutorial mode by referring to the \c tutorialHighlight property
				 * in the skins' stylesheets.\n
				 * For examlple:\n
				 * \code #widgetID[tutorialHighlight="true"] {
				 * ...
				 * } \endcode
				 *
				 * @param active The value to which the \n tutorialHighlight property of subwidgets will be set
				 */
				void setTutorialHighlight(int stage);

			signals:

				/**
				 * @brief A signal sent when a new skin is set
				 *
				 * @param name The current skin manager
				 */
				void skinSet(const SkinManager* smgr);

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

				/**
				 * @brief Called when the user clicks the applyButton
				 *
				 * Attempts to set the device selected in the deviceBox as the AudioInput device
				 */
				void on_applyButton_clicked();

				/**
				 * @brief Called when the user selects a different item in the deviceBox
				 *
				 * Enables the applyButton
				 *
				 * @param index The new item's index
				 */
				void on_deviceBox_currentIndexChanged(int index);

				/**
				 * @brief Called when the user moves the samplesSlider
				 *
				 * Changes the size of the AudioAnalyzer's audio input samples array, and updates the samplesLabel to display
				 * the current size of the array
				 *
				 * @param value The new value of the slider
				 */
				void on_samplesSlider_valueChanged(int value);

				/**
				 * @brief Called when the user moves the volumeTresholdSlider
				 *
				 * Changes the volume threshold of the AudioAnalyzer, and updates the volumeTresholdLabel to display the
				 * current threshold
				 *
				 * @param value The new value of the slider
				 */
				void on_volumeTresholdSlider_valueChanged(int value);

			private:
				Ui::GeneralSettings *ui;	/**< @brief Qt's container for the window's subwidgets */
				SkinManager skinManager;		/**< @brief Helper object that handles the currently selected skin */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // GENERALSETTINGS_H
