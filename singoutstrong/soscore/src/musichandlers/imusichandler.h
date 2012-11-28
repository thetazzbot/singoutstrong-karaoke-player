/** @file imusichandler.h
 * Header file with the IMusicHandler interface
*/

#ifndef IMIDIHANDLER_H
#define IMIDIHANDLER_H

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

		/**
		 * @brief Interface for handling music files and controlling audio playback
		 *
		 */
		class IMusicHandler
		{
			public:
				virtual ~IMusicHandler(){}

				/**
				 * @brief Loads an audio file
				 *
				 * @return bool \c True if loading was sucessful, otherwise \c false
				 */
				virtual bool loadMusic() = 0;

				/**
				 * @brief Rewinds the audio to the currentTime from SongSettings
				 *
				 */
				virtual void rewind() = 0;

				/**
				 * @brief Starts audio playback
				 *
				 */
				virtual void startPlaying() = 0;

				/**
				 * @brief Stops audio playback
				 *
				 */
				virtual void stopPlaying() = 0;

				/**
				 * @brief Checks if audio is currently playing
				 *
				 * @return bool \c True if audio is playing, otherwise \c false
				 */
				virtual bool isPlaying() const = 0;

				/**
				 * @brief Gets the current time if audio playback
				 *
				 * @return long The current audio playback time
				 */
				virtual long getCurrTime() const = 0;

				/**
				 * @brief Updates the time of playback of a note on each track (used to calculate current track volume)
				 *
				 */
				virtual void updateTrackPlayedTime() = 0;

				/**
				 * @brief Set's the specified Track for solo playback.
				 *
				 * If the Track is set as a solo track, every other track is muted.
				 *
				 * @param solo The solo state to be set
				 * @param track The index of the Track (-1 will set all tracks to a given state, should only be used to turn off solo state).
				 */
				virtual void setSolo(bool solo, int track = -1) = 0;

				/**
				 * @brief Mutes or unmutes the specified track
				 *
				 * @param mute /c True if the Track is to be muted, or /c false if it's to be unmuted
				 * @param track The Track's index
				 */
				virtual void setMute(bool mute, int track) = 0;


				/**
				 * @brief Changes the key of the audio to what is specified in the SongSettings
				 *
				 */
				virtual void changeKey() = 0;

				/**
				 * @brief Changes the tempo of the audio to what is specified in the SongSettings
				 *
				 */
				virtual void changeTempo() = 0;

				/**
				 * @brief Changes the volume of the audio to what is specified in the SongSettings
				 *
				 */
				virtual void changeVolume() = 0;


				/**
				 * @brief Frees any external files used by the handler
				 *
				 */
				virtual void free() = 0;
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/

#endif // IMIDIHANDLER_H
