/** @file songcontrol.h
 * Header file with the SongControl class
*/

#pragma once

#include "../../include/iaudioanalyzer.h"
#include "../../include/iaudioio.h"
#include "../../include/isongcontrol.h"
#include "../../include/isongsettings.h"
#include "../audio/pitchrecord/pitchrecord.h"
#include "../musichandlers/imusichandler.h"
#include "../musichandlers/audiohandler.h"
#include "song.h"
#include "log.h"

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
		 * @brief A struct holding the display and playback settings for a Song
		 *
		 */
		struct SongSettings
		{
			public:
				long selectionStart;			/**< @brief Start time of the Song's selected section */
				long selectionEnd;				/**< @brief End time of the Song's selected section */
				long outputLatency;				/**< @brief Delay between stated playback time and actual playback */
				long currTime;					/**< @brief The cuutent playback time */
				long viewedTime;				/**< @brief The beginning of the displayed section */
				long viewTimeRange;				/**< @brief The time range of the displayed section */
				char selectedTrackIndex;		/**< @brief The index of the selected track */
				char keyShift;					/**< @brief The song's key shift */
				float tempo;					/**< @brief The song's tempo */
				unsigned char volume;			/**< @brief The song's master volume */
				unsigned char textLineCount;	/**< @brief The number of lyric lines to be displayed */
				unsigned char textGroupBy;		/**< @brief The number of lines the lyrics are to be grouped by */
		};

		/**
		 * @brief The main class managing the Song, it's playback, and settings
		 *
		 */
		class SongControl : public ISongControl, ISongSettings
		{
			private:
				IAudioAnalyzer* audioAnalyzer;	/**< @brief The audio analyzer */
				IMusicHandler* midiHandler;		/**< @brief The midi audio handler */
				IMusicHandler* streamHandler;	/**< @brief The audio stream handler */
				IMusicHandler* currentHandler;	/**< @brief The current audio handler, switched depending on what kind of file is loaded */
				PitchRecord* pitchRecord;		/**< @brief The SongControl's pitch record */
				Song* song;						/**< @brief The Song */

				SongSettings settings;			/**< @brief The SongSettings */
				float averageAccuracy;			/**< @brief The average accuracy of the song */
				float sumAccuracy;				/**< @brief The sum of all accuracy points of the PitchRecord samples */
				bool analyzed;					/**< @brief Specifies whether the average accuracy was calculated */
				bool loaded;					/**< @brief Specifies whether the song was loaded */
				bool playing;					/**< @brief Specifies whether the song is currently played */
				float lastSamplePitchShift;		/**< @brief The amount of notes the last sample's pitch was shifted, to fit to the last note's octave */
				long lastClock;					/**< @brief The clock() value when update() was last called */

				/**
				 * @brief Checks if the specified time is beyond the section of the song that was selected
				 *
				 * @param time The time
				 * @return bool \c True if specified time is outside of the selected section, otherwise \c false
				 */
				bool timeBeyondSelection(long time);

				/**
				 * @brief Analyzes the excercise (calculates the average accuracy)
				 *
				 */
				virtual void checkExcercise();

				/**
				 * @brief Copies the specified PitchRecord to the one stored in the SongControl
				 *
				 * @param[in] record The record to be copied
				 * @param time The time the samples are to be inserted in.
				 */
				virtual void copyRecord(const IPitchRecord* record, long time);

			public:
				SongControl(IAudioAnalyzer* audioAnalyzer);
				~SongControl();

				/**
				 * @brief Gets the song
				 *
				 * @return const ISong Readonly pointer to ISong interface
				 */
				virtual const ISong* getSong() const;

				/**
				 * @brief Gets the PitchRecord of the processed audio samples
				 *
				 * @return const IPitchRecord Readonly PitchRecord
				 */
				virtual const IPitchRecord* getRecord() const;

				/**
				 * @brief Gets the SongSettings
				 *
				 * @return ISongSettings The song settings
				 */
				virtual ISongSettings* getSettings();

				/**
				 * @brief Gets the SongSettings
				 *
				 * @return ISongSettings Readonly song settings
				 */
				virtual const ISongSettings* getSettings() const;

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
				virtual bool isRecordSampleVisible(int sampleIndex, int marigin) const;

				/**
				 * @brief Checks if the song is currently played
				 *
				 * @return bool \c True if the song is playing, otherwise \c false
				 */
				virtual bool isPlaying() const;

				/**
				 * @brief Checks if the song was sucessfully loaded
				 *
				 * @return bool True if the song was sucessfully loaded otherwise false
				 */
				virtual bool isLoaded() const;

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
				virtual void update();

				/**
				 * @brief Loads the song.
				 *
				 * @param filename Path to the song.
				 * @return \c True if the song was succefully loaded, otherwise \c false
				 */
				virtual bool load(const char* filename);

				/**
				 * @brief Rewinds the Song to the beginning
				 *
				 */
				virtual void rewind();

				/**
				 * @brief Starts the playback of the Song
				 *
				 */
				virtual void start();

				/**
				 * @brief Stops (pauses) the playback of the Song
				 *
				 */
				virtual void stop();

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
				 * @brief Gets the number of notes the last sample had to be moved by, to fit the last note's octave.
				 *
				 * @return int The number of notes
				 */
				virtual int getLastSamplePitchShift() const;

/*================================ SONG SETTINGS ==================================*/

				/**
				 * @brief Gets the delay between the Song current playback time, and the actual playback.
				 *
				 * It takes a while for the user to react to what he hears, and for the audio input to be processed.\n
				 * Therefore it is useful to have a small delay between the stated playback time of the song,
				 * and when it's actually played back, for everything to sync up properly.
				 *
				 * @return long The delay time in miliseconds
				 */
				virtual long getOutputLatency() const;

				/**
				 * @brief Sets the delay between the Song current playback time, and the actual playback.
				 *
				 * It takes a while for the user to react to what he hears, and for the audio input to be processed.\n
				 * Therefore it is useful to have a small delay between the stated playback time of the song,
				 * and when it's actually played back, for everything to sync up properly.
				 *
				 * @param latency The delay time in miliseconds
				 */
				virtual void setOutputLatency(long latency);

				/**
				 * @brief Gets the Song's current playback time
				 *
				 * @return long The current playback time in miliseconds
				 */
				virtual long getCurrentTime() const;

				/**
				 * @brief Gets the Song's current playback time
				 *
				 * @param currTime The Song's current playback time
				 */
				virtual void setCurrentTime(long currTime);

				/**
				 * @brief Gets the time of the beginning, of the Song's section to be displayed
				 *
				 * @return long The viewed time in miliseconds
				 */
				virtual long getViewedTime() const;

				/**
				 * @brief Sets the time of the beginning, of the Song's section to be displayed
				 *
				 * @param viewedTime The viewed time in miliseconds
				 */
				virtual void setViewedTime(long viewedTime);

				/**
				 * @brief Gets the time range of the Song's section to be displayed
				 *
				 * @return long Time range in miliseconds
				 */
				virtual long getViewTimeRange() const;

				/**
				 * @brief Sets the time range of the Song's section to be displayed
				 *
				 * @param timeRange The time range in miliseconds
				 */
				virtual void setViewTimeRange(long timeRange);

				/**
				 * @brief Gets the index of the selected Track
				 *
				 * @return int Selected track index
				 */
				virtual char getSelectedTrackIndex() const;

				/**
				 * @brief Sets the index of the selected Track
				 *
				 * @param index The index of the Track
				 */
				virtual void setSelectedTrackIndex(char index);

				/**
				 * @brief Gets the number of noted the Song's key was shifted by.
				 *
				 * @return int The key shift
				 */
				virtual char getKeyShift() const;

				/**
				 * @brief Sets the number of noted the Song's key is to be shifted by.
				 *
				 * @param keyShift the key shift
				 */
				virtual void setKeyShift(char keyShift);

				/**
				 * @brief Gets the number of notes the Song's key was shifted by.
				 *
				 * @return int The key shift
				 */
				virtual float getTempo() const;

				/**
				 * @brief Sets the number of notes the Song's key is to be shifted by.
				 *
				 * @param keyShift the key shift
				 */
				virtual void setTempo(float tempo);

				/**
				 * @brief Gets the Song's master volume.
				 *
				 * @return unsigned char The volume (0-255)
				 */
				virtual unsigned char getVolume();

				/**
				 * @brief Sets the Song's master volume
				 *
				 * @param volume The volume (0-255)
				 */
				virtual void setVolume(unsigned char volume);

				/**
				 * @brief Gets the number of lines of lyrics to be displayed.
				 *
				 * @return unsigned char The number of lines of lyrics to be displaed
				 */
				virtual unsigned char getTextLineCount() const;

				/**
				 * @brief Sets the number of lines of lyrics to be displayed.
				 *
				 * @param lineCount The number of lines of lyrics to be displayed.
				 */
				virtual void setTextLineCount(unsigned char lineCount);

				/**
				 * @brief Gets the number of lines the lyrics are going to be grouped by when displayed
				 *
				 * @return unsigned char The number of lines the lyrics are going to be grouped by when displayed
				 */
				virtual unsigned char getTextGroupBy() const;

				/**
				 * @brief Sets the number of lines the lyrics are going to be grouped by when displayed
				 *
				 * @param groupBy The number of lines the lyrics are going to be grouped by when displayed
				 */
				virtual void setTextGroupBy(unsigned char groupBy);

				/**
				 * @brief Gets the start time of the Song's section that was selected
				 *
				 * @return long The selection start time
				 */
				virtual long getSelectionStart() const;

				/**
				 * @brief Sets the start time of the Song's section that is to be selected
				 *
				 * @param time The selection start time
				 */
				virtual void setSelectionStart(long time);

				/**
				 * @brief Gets the end time of the Song's section that was selected
				 *
				 * @return long The selection start time
				 */
				virtual long getSelectionEnd() const;

				/**
				 * @brief Sets the end time of the Song's section that is to be selected
				 *
				 * @param time The selection start time
				 */
				virtual void setSelectionEnd(long time);
		};
	}  /*! @} End of Doxygen Group Core */
} /*! @} End of Doxygen Group SoS */
