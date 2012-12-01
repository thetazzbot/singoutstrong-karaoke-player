/** @file mainwindow.h
 * Header file with the MainWindow class
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*! \mainpage SingOutStrong Karaoke Player
 *
 * \section intro_sec Introduction
 *
 * SingOutStrong Karaoke Player is a free, open source music player, with a pitch detection and display feature similar to that
 * of SingStar like games. \n
 * Our goal is to create an easy to use and versitile player for practicing singing skills.
 *
 * This code documenation may not be too elaborate at the moment, but it should give you a rough idea about what's what.
 *
 * \section build_sec Building
 *
 * The project was created in QtCreator 2.5 with Qt 4.8.0.
 * The simplest way to build is to open the included .pro files in QtCreator.
 *
 * \section release_sec Release Packages
 *
 * The latest release package is available for download at http://singoutstrong.org/karaokeplayer
 *
 * \section src_sec Source code
 *
 * Get the source code at https://github.com/singoutstrong/singoutstrong-karaoke-player
 */

#include <QMainWindow>
#include <QBasicTimer>
#include <QtGui>
#include "soscontext.h"
#include "audioinsettings.h"
#include "outputsettings.h"
#include "Playlist.h"
#include "songwindow.h"
#include "generalsettings.h"
#include "tutorialwindow.h"
#include "fileformats.h"
#include "songsearch.h"
#include <log.h>

#ifdef DEBUG
#include <time.h>
#endif

#define SOS_LAUNCHES_TO_PROMO 3

// Don't generate documentation for this napesace
/// \cond 0
using namespace std;

namespace Ui {
	class MainWindow;
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
		 * @brief Main application window
		 *
		 */
		class MainWindow : public QMainWindow
		{
				Q_OBJECT

			public:
				/**
				 * @brief Constructor.
				 *
				 * Sets up event handling, and settings for every window, and provides initial values for ISongSettings.
				 *
				 * @param parent
				 */
				explicit MainWindow(QWidget *parent = 0);
				~MainWindow();

				/**
				 * @brief Shows this window, and every sub window that was also visible during the prior run of the application, or before this window was minimized
				 *
				 * Altough evert sub window's show method is called, the SoSSubWindow only allows the windows to be shown when
				 * the allowShow flag is set.\n
				 * Therefore the visibility is managed through the respective windows' checkboxes
				 *
				 */
				void show();

				/**
				 * @brief Called when the user activates (sets the focus on) the main window, and when it's state is changed (minimize/maximize/normal)
				 *
				 * When the window is activate, all the sub windows are also brought to the top of the desktop.\n
				 * When it is minimized all the sub windows are hidden, and when it is brought back from the minimized state
				 * the sub windows that were previously shown, are shown again.
				 *
				 * @param e
				 */
				void changeEvent(QEvent *e);

				/**
				 * @brief Brings all windows to the top of the desktop
				 *
				 */
				virtual void bringToTop();

			protected:

				AudioInSettings audioInSettingsWindow;	/**< @brief The audio input settings window */
				OutputSettings outputSettings;			/**< @brief The output settings window */
				Playlist playlist;						/**< @brief The playlist window */
				SongWindow songWindow;					/**< @brief The song display window */
				GeneralSettings generalSettings;		/**< @brief The general settings window */
				TutorialWindow tutorial;				/**< @brief The tutorial window */
				SongSearch songSearch;
				ISongSettings* settings;				/**< @brief The SongSettings from SongControl */

				Ui::MainWindow *ui;						/**< @brief Qt's container for the window's subwidgets */
				SoSContext* sosContext;					/**< @brief The context for accessing the core interfaces */
				QBasicTimer timer;						/**< @brief Timer for refreshing the song display and recalculating variables */

				long elapsed;							/**< @brief The elapsed time since the timerEvent was last called (for debugging purposes only) */
				float lowestFPS;						/**< @brief The lowest average framerate that was achieved in this run of the application (for debugging purposes only */
				vector<float> fps;						/**< @brief The vector storing the framerates from the last 50 frames (for debugging purposes only) */
				bool detachViewTime;					/**< @brief When set to \c true, the currentTime of SongSettings will not be automatically set when the viewTime is changed */
				bool showTutorial;						/**< @brief When set to \c true, the tutorial will be showed at the start of the application */
				int timesLaunched;						/**< @brief The number of times the app was luanched (used by promo screen) */
				bool promoShown;						/**< @brief Was the promo screen shown? */

				/**
				 * @brief Starts or stops the song's playback depending on it's current state
				 *
				 * Used by keyPressEvent to allow playback control from keyboard.
				 *
				 */
				void toggleSongPlay();

				/**
				 * @brief Loads the application settings from the user's appData folder
				 *
				 * The location of the settings file is accessed through the QDesktopServices::storageLocation() method, and it
				 * depends on the operating system the application is ran on.\n
				 * If there is no settings file then we assume this is the first run of the application and we show the tutorial. \n
				 * \n
				 * The settings that are loaded are the windows' location, size, and visibility, and the SongSettings variables
				 * that can be set by the sub windows.
				 *
				 */
				void loadSettings();

				/**
				 * @brief Saves the application settings from the user's appData folder
				 *
				 * The location of the settings file is accessed through the QDesktopServices::storageLocation() method, and it
				 * depends on the operating system the application is ran on.\n
				 * \n
				 * The settings that are loaded are the windows' location, size, and visibility, and the SongSettings variables
				 * that can be set by the sub windows.
				 *
				 */
				void saveSettings();

				/**
				 * @brief Gets a xml child node with a specified name, from a specified parent node, in the specified document.
				 *
				 * If no such node is found, then one is created and added to the parent.
				 *
				 * @param name The name of the child node
				 * @param doc The xml document
				 * @param parent The xml parent node
				 * @return QDomElement The found or created child node
				 */
				QDomElement getNode(QString name, QDomDocument* doc, QDomNode* parent);

				/**
				 * @brief Saves the location, size, and visibility of a specified widget to a parent node in the specified xml document.
				 *
				 * @param window The window whose properties are to be saved
				 * @param doc The xml document
				 * @param parent The xml parent node
				 */
				void saveWinProperties(QWidget* window, QDomDocument* doc, QDomNode* parent);

				/**
				 * @brief Loads the location, size, and visibility of the specified window from the xml document
				 *
				 * @param window The window whose properties are to be restored
				 * @param docElement The xml document
				 */
				void loadWinProperties(QWidget *window, QDomElement *docElement);

				/**
				 * @brief Sets the allowShow flag of a subwindow, and the shows or hides it depending on it's value
				 *
				 * @param window The subwindow to be shown/hidden
				 * @param show The new value of the allowShow flag
				 */
				void handleSubwinVisibilisty(SoSSubWindow* window, bool show);

				/**
				 * @brief Called when the timer times out
				 *
				 * Animates the SongWindow, calls SongControl::update(), refreshes the values of the currTime
				 * label and viewTimeSlider.
				 *
				 * @param event
				 */
				void timerEvent(QTimerEvent *event);

				/**
				 * @brief Called when the main window is closed
				 *
				 * Saves the settings and the current playlist, and closes the application
				 *
				 * @param event
				 */
				void closeEvent(QCloseEvent *event);

				/**
				 * @brief Called when the user presses a keyboard key
				 *
				 * Handles pressing of following keys:\n
				 * \li \c Ctrl for setting the \c detachViewTime variable to true
				 * \li \c Space for starting/stopping a song
				 * \li \c Esc for exitting fullscreen mode
				 *
				 * @param event
				 */
				void keyPressEvent(QKeyEvent *event);

				/**
				 * @brief Called when the user releases a keyboard key
				 *
				 * Handles the release of the \c Ctrl key to set the \c detachViewTime variable back to false
				 *
				 * @param event
				 */
				void keyReleaseEvent(QKeyEvent *event);

				/**
				 * @brief Intercepts events from other objects when MainWindow is installed as their event filter
				 *
				 * @param target The object that calls the event
				 * @param event The event the is called
				 * @return bool Return \c true if you DON'T want the event to be passed to the target object and be handled be it too, otherwise return \c false
				 */
				bool eventFilter(QObject *target, QEvent *event);

				/**
				 * @brief Shows the promo screen if the user opened enough songs.
				 *
				 * The amount of opened songs is greater or equal to SOS_LAUNCHES_TO_PROMO, and the promo screen wasn't shown before
				 */
				void processPromo();

			private slots:

				/**
				 * @brief Called when the user clicks the playButton
				 *
				 * Starts the playback of the song.
				 *
				 */
				void on_playButton_clicked();

				/**
				 * @brief Called when the user clicks the stopButton
				 *
				 * Stops the playback of the song, and rewinds it.
				 *
				 */
				void on_stopButton_clicked();

				/**
				 * @brief Called when the user clicks the pauseButton
				 *
				 * Stops the playback of the song without rewinding it.
				 *
				 */
				void on_pauseButton_clicked();

				/**
				 * @brief Called when the user clicks the rewindButton
				 *
				 * Loads the previous song on the playlist
				 *
				 */
				void on_rewindButton_clicked();

				/**
				 * @brief Called when the user clicks the ffworwardButton
				 *
				 * Loads the next song on the playlist
				 *
				 */
				void on_fforwardButton_clicked();

				/**
				 * @brief Called when the user clicks the ejectButton
				 *
				 * Opens a dialog for loading new files
				 *
				 */
				void on_ejectButton_clicked();

				/**
				 * @brief Called when the viewTimeSlider is moved, and the user is still holding the left mouse button
				 *
				 * Changes the viewedTime to the relative position of the slider.\n
				 * \c on_viewTimeSlider_valueChanged will not be called while the user is holding the mouse button
				 *
				 * @param position
				 */
				void on_viewTimeSlider_sliderMoved(int position);

				/**
				 * @brief Called when the viewTimeSlider's value is changed by the \c update() method, or when the user releases the mouse button after moving the slider
				 *
				 * Changes the viewedTime to the relative position of the slider, and if the \c detachViewTime variable is set
				 * to true, changes the currentTime to the middle of the section displayed in the SongWindow.
				 *
				 * @param value
				 */
				void on_viewTimeSlider_valueChanged(int value);

				/**
				 * @brief Called when a new skin is selected in the \c GeneralSettings window
				 *
				 * Loads a stylesheet from the ./skins/\c skinName directory and applies it to all windows.
				 *
				 * @param skinName
				 */
				void setSkin(QString skinName);

				/**
				 * @brief Called when a new song is loaded
				 *
				 * Updates the totalTimeLabel, sets the viewTimeSlider to 0, updates the title and description of the song
				 * and the tracks in the OutputSettings window
				 *
				 */
				void updateSong();

				/**
				 * @brief Called when the user moves to another page in the tutorialWizard
				 *
				 * Highlights the widgets mentioned in the tutorial, loads an example song
				 *
				 * @param pageId
				 */
				void tutorialPageChange(QString docName, int pageId);

				/**
				 * @brief Called when the user closes the tutorial.
				 *
				 * Turns off all tutorial highlights
				 *
				 */
				void tutorialClose();

				/**
				 * @brief Called when the songCheckbox is clicked
				 *
				 * Shows/hides the SongWindow
				 *
				 * @param checked
				 */
				void on_songCheckbox_clicked(bool checked);

				/**
				 * @brief Called when the playlistCheckbox is clicked
				 *
				 * Shows/hides the OutputSettings window
				 *
				 * @param checked
				 */
				void on_playlistCheckbox_clicked(bool checked);

				/**
				 * @brief Called when the outputCheckbox is clicked
				 *
				 * Shows/hides the playlist window
				 *
				 * @param checked
				 */
				void on_outputCheckbox_clicked(bool checked);

				/**
				 * @brief Called when the audioInCheckbox is clicked
				 *
				 * Shows/hides the audioInSettings window
				 *
				 * @param checked
				 */
				void on_audioInCheckbox_clicked(bool checked);

				/**
				 * @brief Called when the settingsCheckbox is clicked
				 *
				 * Shows/hides the generalSettings window
				 *
				 * @param checked
				 */
				void on_settingsCheckbox_clicked(bool checked);

				/**
				 * @brief Called when the tutoriaCheckbox is clicked
				 *
				 * Shows the TutorialWindow
				 *
				 * @param checked
				 */
				void on_tutorialCheckbox_clicked(bool checked);
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // MAINWINDOW_H
