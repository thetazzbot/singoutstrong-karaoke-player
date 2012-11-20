/** @file isongsettings.h
 * Header file with the ISongSettings interface
*/

#pragma once

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
		 * @brief Interface for accessing the SongSettings
		 *
		 */
		class ISongSettings
		{
			public:
				virtual ~ISongSettings(){}

				/**
				 * @brief Gets the delay between the Song current playback time, and the actual playback.
				 *
				 * It takes a while for the user to react to what he hears, and for the audio input to be processed.\n
				 * Therefore it is useful to have a small delay between the stated playback time of the song,
				 * and when it's actually played back, for everything to sync up properly.
				 *
				 * @return long The delay time in miliseconds
				 */
				virtual long getOutputLatency() const = 0;

				/**
				 * @brief Sets the delay between the Song current playback time, and the actual playback.
				 *
				 * It takes a while for the user to react to what he hears, and for the audio input to be processed.\n
				 * Therefore it is useful to have a small delay between the stated playback time of the song,
				 * and when it's actually played back, for everything to sync up properly.
				 *
				 * @param latency The delay time in miliseconds
				 */
				virtual void setOutputLatency(long latency) = 0;

				/**
				 * @brief Gets the Song's current playback time
				 *
				 * @return long The current playback time in miliseconds
				 */
				virtual long getCurrentTime() const = 0;

				/**
				 * @brief Gets the Song's current playback time
				 *
				 * @param currTime The Song's current playback time
				 */
				virtual void setCurrentTime(long currTime) = 0;

				/**
				 * @brief Gets the time of the beginning, of the Song's section to be displayed
				 *
				 * @return long The viewed time in miliseconds
				 */
				virtual long getViewedTime() const = 0;

				/**
				 * @brief Sets the time of the beginning, of the Song's section to be displayed
				 *
				 * @param viewedTime The viewed time in miliseconds
				 */
				virtual void setViewedTime(long viewedTime) = 0;

				/**
				 * @brief Gets the time range of the Song's section to be displayed
				 *
				 * @return long Time range in miliseconds
				 */
				virtual long getViewTimeRange() const = 0;

				/**
				 * @brief Sets the time range of the Song's section to be displayed
				 *
				 * @param timeRange The time range in miliseconds
				 */
				virtual void setViewTimeRange(long timeRange) = 0;

				/**
				 * @brief Gets the index of the selected Track
				 *
				 * @return int Selected track index
				 */
				virtual char getSelectedTrackIndex() const = 0;

				/**
				 * @brief Sets the index of the selected Track
				 *
				 * @param index The index of the Track
				 */
				virtual void setSelectedTrackIndex(char index) = 0;

				/**
				 * @brief Gets the number of notes the Song's key was shifted by.
				 *
				 * @return int The key shift
				 */
				virtual char getKeyShift() const = 0;

				/**
				 * @brief Sets the number of notes the Song's key is to be shifted by.
				 *
				 * @param keyShift the key shift
				 */
				virtual void setKeyShift(char keyShift) = 0;

				/**
				 * @brief Gets the song's tempo.
				 *
				 * @return The tempo
				 */
				virtual float getTempo() const = 0;

				/**
				 * @brief Sets the song's tempo.
				 *
				 * @param tempo The tempo. 1.0 is 100%
				 */
				virtual void setTempo(float tempo) = 0;

				/**
				 * @brief Gets the Song's master volume.
				 *
				 * @return unsigned char The volume (0-255)
				 */
				virtual unsigned char getVolume() = 0;

				/**
				 * @brief Sets the Song's master volume
				 *
				 * @param volume The volume (0-255)
				 */
				virtual void setVolume(unsigned char volume) = 0;

				/**
				 * @brief Gets the number of lines of lyrics to be displayed.
				 *
				 * @return unsigned char The number of lines of lyrics to be displaed
				 */
				virtual unsigned char getTextLineCount() const = 0;

				/**
				 * @brief Sets the number of lines of lyrics to be displayed.
				 *
				 * @param lineCount The number of lines of lyrics to be displayed.
				 */
				virtual void setTextLineCount(unsigned char lineCount) = 0;

				/**
				 * @brief Gets the number of lines the lyrics are going to be grouped by when displayed
				 *
				 * @return unsigned char The number of lines the lyrics are going to be grouped by when displayed
				 */
				virtual unsigned char getTextGroupBy() const = 0;

				/**
				 * @brief Sets the number of lines the lyrics are going to be grouped by when displayed
				 *
				 * @param groupBy The number of lines the lyrics are going to be grouped by when displayed
				 */
				virtual void setTextGroupBy(unsigned char groupBy) = 0;

				/**
				 * @brief Gets the start time of the Song's section that was selected
				 *
				 * @return long The selection start time
				 */
				virtual long getSelectionStart() const = 0;

				/**
				 * @brief Sets the start time of the Song's section that is to be selected
				 *
				 * @param time The selection start time
				 */
				virtual void setSelectionStart(long time) = 0;

				/**
				 * @brief Gets the end time of the Song's section that was selected
				 *
				 * @return long The selection start time
				 */
				virtual long getSelectionEnd() const = 0;

				/**
				 * @brief Sets the end time of the Song's section that is to be selected
				 *
				 * @param time The selection start time
				 */
				virtual void setSelectionEnd(long time) = 0;
		};

	}  /*! @} End of Doxygen Group Core */
} /*! @} End of Doxygen Group SoS */
