/** @file audioinsettings.h
 * Header file with the AudioInSettings class
*/

#ifndef AUDIOINSETTINGS_H
#define AUDIOINSETTINGS_H

#include <QDockWidget>
#include <QtXml>
#include <QtGui>
#include <math.h>
#include "soscontext.h"
#include "sossubwindow.h"

/// \cond 0

namespace Ui {
	class AudioInSettings;
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
		 * @brief The audio input settings window class
		 *
		 */
		class AudioInSettings : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit AudioInSettings(QWidget *parent = 0);
				~AudioInSettings();

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


			private slots:

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
				Ui::AudioInSettings *ui; /**< @brief Qt's container for the window's subwidgets */
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // AUDIOINSETTINGS_H
