/** @file outputsettings.h
 * Header file with the OutputSettings class
*/

#ifndef OUTPUTSETTINGS_H
#define OUTPUTSETTINGS_H

#include <QDockWidget>
#include <QFrame>
#include <QCheckBox>
#include <QProgressBar>
#include <QLabel>
#include <QScrollBar>
#include <QSizeGrip>
#include "soscontext.h"
#include "sossubwindow.h"

/// \cond 0

namespace Ui {
	class OutputSettings;
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
		 * @brief The output settings window
		 *
		 */
		class OutputSettings : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit OutputSettings(QWidget *parent = 0);
				~OutputSettings();

				/**
				 * @brief Updated the values of child widgets with the values stored in SongSettings
				 *
				 */
				void updateSettings();

				/**
				 * @brief Updates the names and the number of tracks displayed in the outputTracks widget
				 *
				 * Should be called when a new song is loaded
				 */
				void updateTracks();

				/**
				 * @brief Updates the values of progress bars for displaying track volume in the outputTracks widget
				 *
				 */
				void updateVolumes();

				/**
				 * @brief Clears the lists of outputTracks' child widgets
				 *
				 * Clears the following lists:\n
				 * \li vocalTracks
				 * \li mutes
				 * \li solos
				 * \li volumes
				 * \li trackNames
				 * \li trackIndeces
				 *
				 */
				void clearLists();

				/**
				 * @brief Highlights the subwidgets for the purposes of the tutorial in the TutorialWindow
				 *
				 * The method sets the \c tutorialHighlight property to the value of the \c active parameter, for the
				 * child widgets of the outputTracks widget. \n
				 * This allows them to be highlighted when the user enters the fourth page of the TutorialWizard. \n\n
				 * You can set the style of these widgets while in tutorial mode by referring to the \c tutorialHighlight property
				 * in the skins' stylesheets.\n
				 * For examlple:\n
				 * \code #widgetID[tutorialHighlight="true"] {
				 * ...
				 * } \endcode
				 *
				 * @param active The value to which the \n tutorialHighlight property of subwidgets will be set
				 */
				void setTutorialHighlight(bool active);

				/**
				 * @brief Shows the window
				 *
				 */
				virtual void show();

			protected:
				int lastSolo;					/**< @brief The index of the previously checked solo button */
				QList<QCheckBox*> vocalTracks;	/**< @brief List of checkboxes for selecting the vocals track */
				QList<QCheckBox*> mutes;		/**< @brief List of checkboxes for selecting which tracks to mute */
				QList<QCheckBox*> solos;		/**< @brief List of checkboxes for selecting the track for solo playback */
				QList<QProgressBar*> volumes;	/**< @brief List of volume progress bars */
				QList<QLabel*> trackNames;		/**< @brief List of track name labels */
				/** @brief List of indices (referring to the track's index in the Song class)
				 *
				 * Since only the tracks that contain notes are displayed, the index of a track does not necessarily
				 * correspond to it's place in the outputTracks widget (or any of the subwidget lists). \n
				 * So this list stores indices of all displayed tracks. For example \c trackIndices[0] will return the index
				 * of the first displayed track.
				 */
				QList<int> trackIndeces;

				/**
				 * @brief Makes sure only one checkbox from a group is checked at any given time
				 *
				 * @param list The list of grouped checkboxes
				 * @param buttonChecked The state of the clicked checkbox
				 * @param lastChecked The index of the previously checked checkbox
				 * @param allowUncheck Set to \c true if unchecking is allowed in this group
				 * @return int The index of the checkbox that was set
				 */
				int handleGroupedCheckboxes(QList<QCheckBox*> &list, bool buttonChecked, int lastChecked, bool allowUncheck);

				/**
				 * @brief Called when the window is resized
				 *
				 * @param e
				 */
				void resizeEvent(QResizeEvent *e);

			private slots:
				/**
				 * @brief Called when the user moves the keyShiftSlider
				 *
				 * Changes the key of the song by calling the ISongSettings::setKeyShift method
				 *
				 * @param value
				 */
				void on_keyShiftSlider_valueChanged(int value);

				/**
				 * @brief Called when the user moves the volumeSlider
				 *
				 * Changes the volume of the song by calling the ISongSettings::setVolume method
				 *
				 * @param value
				 */
				void on_volumeSlider_valueChanged(int value);

				/**
				 * @brief Called when the user clicks one of the vocalTracks checkboxes
				 *
				 * Sets the vocal track by calling the ISongSettings::setSelectedTrackIndex method
				 *
				 * @param buttonChecked
				 */
				void setVocalTrack(bool buttonChecked);

				/**
				 * @brief Called when the user clicks one of the solos checkboxes
				 *
				 * Sets the track for solo playback by calling the ISongSettings::setSolo method
				 *
				 * @param buttonChecked
				 */
				void setSolo(bool buttonChecked);

				/**
				 * @brief Called when the user clicks one of the mutes checkboxes
				 *
				 * Mutes the track by calling the ISongSettings::setMute method
				 *
				 * @param buttonChecked
				 */
				void setMute();

			private:
				Ui::OutputSettings *ui; /**< @brief Qt's container for the window's subwidgets */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // OUTPUTSETTINGS_H
