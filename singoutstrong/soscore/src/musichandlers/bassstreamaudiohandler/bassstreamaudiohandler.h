/** @file bassstreamaudiohandler.h
 * Header file with the BassStreamAudioHandler class
*/


#ifndef BASSSTREAMHANDLER_H
#define BASSSTREAMHANDLER_H

#include "../imusichandler.h"
#include "../../song/song.h"
#include "../include/isongsettings.h"
#include "../ultrastarparser/ultrastarparser.h"
#include <log.h>
#include <bass.h>
#include <bass_fx.h>

/*!
 *  \addtogroup SoS
 *  @{
 */

//! Main SingOutStrong namespace
namespace SoS
{
	/*!
	 *  \addtogroup Core
	 *  @{
	 */

	//! Core functionalisties: loading files, audio processing, playback control, etc.
	namespace Core
	{

#define SOS_TIME_RESOLUTION 5

		/**
		 * @brief Class for handling stream audio files and playback based on the BASS library
		 *
		 */
		class BassStreamAudioHandler : public IMusicHandler
		{
			private:
				Song* song;					/**< @brief The song used by SongControl */
				ISongSettings* settings;	/**< @brief The SongSettings from SongControl */

				HSTREAM stream;				/**< @brief The audio stream */

				/**
				 * @brief Moves the playback to the specified time
				 *
				 * @param time New playback time
				 */
				virtual void moveTo(long time);

			public:
				BassStreamAudioHandler(Song* song, ISongSettings* settings);
				~BassStreamAudioHandler();

				/**
				 * @brief Loads an audio file
				 *
				 * @return bool \c True if loading was sucessful, otherwise \c false
				 */
				virtual bool loadMusic();

				/**
				 * @brief Rewinds the audio to the beginning
				 *
				 */
				virtual void rewind();

				/**
				 * @brief Starts audio playback
				 *
				 */
				virtual void startPlaying();

				/**
				 * @brief Stops audio playback
				 *
				 */
				virtual void stopPlaying();

				/**
				 * @brief Checks if audio is currently playing
				 *
				 * @return bool \c True if audio is playing, otherwise \c false
				 */
				virtual bool isPlaying() const;

				/**
				 * @brief Gets the current time if audio playback
				 *
				 * @return long The current audio playback time
				 */
				virtual long getCurrTime() const;

				/**
				 * @brief Updates the time of playback of a note on each track (used to calculate current track volume)
				 *
				 */
				virtual void updateTrackPlayedTime();

				/**
				 * @brief Set's the specified Track for solo playback.
				 *
				 * If the Track is set as a solo track, every other track is muted.
				 *
				 * @param solo The solo state to be set
				 * @param track The index of the Track (-1 will set all tracks to a given state, should only be used to turn off solo state).
				 */
				virtual void setSolo(bool solo, int track = -1);

				/**
				 * @brief Mutes or unmutes the specified track
				 *
				 * @param mute /c True if the Track is to be muted, or /c false if it's to be unmuted
				 * @param track The Track's index
				 */
				virtual void setMute(bool mute, int track);

				/**
				 * @brief Changes the key of the audio to what is specified in the SongSettings
				 *
				 */
				virtual void changeKey();

				/**
				 * @brief Changes the tempo of the audio to what is specified in the SongSettings
				 *
				 */
				virtual void changeTempo();

				/**
				 * @brief Changes the volume of the audio to what is specified in the SongSettings
				 *
				 */
				virtual void changeVolume();

				/**
				 * @brief Frees any external files used by the handler
				 *
				 */
				virtual void free();
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/

#endif // JDKMIDIHANDLER_H
