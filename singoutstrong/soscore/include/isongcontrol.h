/** @file isongcontrol.h
 * Header file with the ISongControl interface
*/

#pragma once

#include "isongsettings.h"
#include "ipitchrecord.h"
#include "isong.h"
#include "inote.h"

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
		 * @brief Main interface for accessing the Song, the PitchRecord of processed audio samples, and playback control
		 *
		 */
		class ISongControl
		{
			public:
				virtual ~ISongControl() {}

				/**
				 * @brief Gets the song
				 *
				 * @return const ISong Readonly pointer to ISong interface
				 */
				virtual const ISong* getSong() const = 0;

				/**
				 * @brief Gets the PitchRecord of the processed audio samples
				 *
				 * @return const IPitchRecord Readonly PitchRecord
				 */
				virtual const IPitchRecord* getRecord() const = 0;

				/**
				 * @brief Gets the SongSettings
				 *
				 * @return ISongSettings The song settings
				 */
				virtual ISongSettings* getSettings() = 0;

				/**
				 * @brief Gets the SongSettings
				 *
				 * @return ISongSettings Readonly song settings
				 */
				virtual const ISongSettings* getSettings() const = 0;

				/**
				 * @brief Checks if the PitchSample at the specified index is visible at the viewTime specified in SongSettings
				 *
				 * Specifically, checks if the pitch is between the selected track's top and bottom note, and if the timestamp is between the viewTime and timePageLength. \n
				 * Also makes sure this isn't the last sample of a section.
				 *
				 * @param sampleIndex The index of the sample in the PitchRecord
				 * @param marigin Number of notes that a sample's pitch can go beyond the track's top and bottom notes, that will still meet the visibility criteria.
				 * @return bool \c True if the sample is visible, otherwise \c false
				 */
				virtual bool isRecordSampleVisible(int sampleIndex, int marigin) const = 0;

				/**
				 * @brief Checks if the song is currently played
				 *
				 * @return bool True if the song is playing, otherwise false
				 */
				virtual bool isPlaying() const = 0;

				/**
				 * @brief Checks if the song was sucessfully loaded
				 *
				 * @return bool True if the song was sucessfully loaded otherwise false
				 */
				virtual bool isLoaded() const = 0;

				/**
				 * @brief Updates all the information about the Song, and the PitchRecord
				 *
				 * If the Song is playing, the function updates the current playback time in the SongSettings,
				 * and the last time a note was played in each track (which is later used to calculate the track's volume).\n
				 * It also copies the PitchRecord from the AudioAnalyzer, and adjust's it to the octave of the currently
				 * selected track. \n
				 * \n
				 * If the Song is not playing, the function does nothing.
				 */
				virtual void update() = 0;

				/**
				 * @brief Loads the song.
				 *
				 * @param filename Path to the song.
				 * @return \c True if the song was succefully loaded, otherwise \c false
				 */
				virtual bool load(const char* filename) = 0;

				/**
				 * @brief Rewinds the Song to the beginning
				 *
				 */
				virtual void rewind() = 0;

				/**
				 * @brief Starts the playback of the Song
				 *
				 */
				virtual void start() = 0;

				/**
				 * @brief Stops (pauses) the playback of the Song
				 *
				 */
				virtual void stop() = 0;

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
				 * @brief Gets the number of notes the last sample had to be moved by, to fit the last note's octave.
				 *
				 * @return int The number of notes
				 */
				virtual int getLastSamplePitchShift() const = 0;
		};
	}  /*! @} End of Doxygen Group Core */
} /*! @} End of Doxygen Group SoS */
