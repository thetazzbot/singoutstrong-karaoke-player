/** @file playlist.h
 * Header file with the Playlist class
*/


#ifndef Playlist_H
#define Playlist_H

#include <QDockWidget>
#include <QtXml>
#include <QListWidget>
#include "soscontext.h"
#include "sossubwindow.h"
#include "fileformats.h"

/// \cond 0

namespace Ui {
	class Playlist;
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
		 * @brief The playlist window
		 *
		 */
		class Playlist : public SoSSubWindow
		{
				Q_OBJECT

			public:
				explicit Playlist(QWidget *parent = 0);
				~Playlist();

				QDir lastOpenedDir; /**< @brief Stores the directory of the last opened file */

				/**
				 * @brief Clears the playlist
				 *
				 */
				void clearPlaylist();

				/**
				 * @brief Saves the contents of the playlist to a specified file
				 *
				 * @param filename Path and filename
				 */
				void savePlaylist(QString filename);

				/**
				 * @brief Loads the playlist from a specified file
				 *
				 * @param filename Path and filename
				 */
				void loadPlaylist(QString filename);

				/**
				 * @brief Loads the next song on the list
				 *
				 */
				void loadNextSong();

				/**
				 * @brief Loads the previous song on the list
				 *
				 */
				void loadPrevSong();

				/**
				 * @brief Adds a file to the playlist
				 *
				 * @param filename The filename
				 */
				void addFile(QString filename);

				/**
				 * @brief Intercepts events from other objects when Playlist is installed as their event filter
				 *
				 * @param target The object that calls the event
				 * @param event The event the is called
				 * @return bool Return \c true if you DON'T want the event to be passed to the target object and be handled be it too, otherwise return \c false
				 */
				bool eventFilter(QObject *target, QEvent *event);

			signals:
				/**
				 * @brief A signal thtat is emitted when a new song is loaded
				 *
				 */
				void songLoaded();

			protected:

				/**
				 * @brief Loads the song from the list at the specified index
				 *
				 * Emits the songLoaded signal.
				 *
				 * @param songIndex
				 */
				void loadSongFromList(int songIndex);

				/**
				 * @brief Called when the user drags an item into the window
				 *
				 * Allows an item to be dropped into the window if it's a file, or file list. Otherwise it is rejected.
				 *
				 * @param event
				 */
				void dragEnterEvent(QDragEnterEvent *event);

				/**
				 * @brief Called when the user drops an item into the window
				 *
				 * Adds the file(s) into the playlist.
				 *
				 * @param event
				 */
				void dropEvent(QDropEvent *event);

				/**
				 * @brief Called when the user presses a keyboard key
				 *
				 * Handles pressing of the del key, to delete a song from the playlist.
				 *
				 * @param event
				 */
				void keyPressEvent(QKeyEvent *event);

			private slots:

				/**
				 * @brief Called when the user doubleclicks an item on the list
				 *
				 * Loads a new song and plays it.
				 *
				 * @param item
				 */
				void on_PlaylistBox_itemDoubleClicked(QListWidgetItem *item);

				/**
				 * @brief Called when the newListButton is clicked
				 *
				 * Clears the playlist
				 *
				 */
				void on_newListButton_clicked();

				/**
				 * @brief Called when the saveListButton is clicked
				 *
				 * Opens a FileDialog and saves the playlist to the file that is returned by the dialog.
				 *
				 */
				void on_saveListButton_clicked();

			private:
				Ui::Playlist *ui; /**< @brief Qt's container for the window's subwidgets */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // Playlist_H
