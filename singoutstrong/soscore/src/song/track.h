/** @file track.h
 * Header file with the Track class
*/

#pragma once

#include "note.h"
#include "textdata.h"
#include "../essentials.h"
#include "../../include/itrack.h"
#include "../../include/isongsettings.h"

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
		 * @brief Class implementing the ITrack interface
		 *
		 */
		class Track : public ITrack
		{
			public:
				Track();
				~Track();

				std::string name;										/**< @brief The name of the track */
				std::vector<Note*> notes;								/**< @brief Notes contained in the track */
				std::vector<TextData*> textData[TEXT_DATA_TYPES_COUNT];	/**< @brief Text data contained in the track */
				static const ISongSettings* settings;					/**< @brief the settings from the SongControl class */

				int topNote;			/**< @brief The top note in the track */
				int bottomNote;			/**< @brief The bottom note in the track */
				unsigned char volume;	/**< @brief The track's current volume */


				/**
				 * @brief Clears the track of all notes and text data
				 *
				 *
				 */
				void clear();

				/**
				 * @brief Gets the total count of text data of all types in the track
				 *
				 * @return int Count of all text data in the track
				 */
				int getAllTextDataCount() const;

				/**
				 * @brief Gets the note at a specified index
				 *
				 * @param index The index of the note
				 * @return INote Pointer to a INote interface
				 */
				virtual INote* getNote(int index);

				/**
				 * @brief Gets the note at a specified index
				 *
				 * @param index The index of the note
				 * @return INote Readonly pointer to a INote interface
				 */
				virtual const INote* getNote(int index) const;

				/**
				 * @brief Gets the index of the first note after the viewTime specified in the SongControl settings
				 *
				 * @return int The index of the note
				 */
				virtual int getNoteCount() const;

				/**
				 * @brief Gets the number of notes in this track
				 *
				 * @return int The number of notes
				 */
				virtual int getNoteIndexForViewTime() const;

				/**
				 * @brief Gets the TextData at a specified index, and of specified type
				 *
				 * @param index The index of the text data
				 * @param type The type of the text data. ITextData::LYRIC_TEXT by default
				 * @return ITextData Pointer to a ITextData interface
				 */
				virtual ITextData* getTextData(int index, ITextData::TextDataType type = ITextData::LYRIC_TEXT);

				/**
				 * @brief Gets the TextData at a specified index, and of specified type
				 *
				 * @param index The index of the text data
				 * @param type The type of the text data. ITextData::LYRIC_TEXT by default
				 * @return ITextData Readonly pointer to a ITextData interface
				 */
				virtual const ITextData* getTextData(int index, ITextData::TextDataType type = ITextData::LYRIC_TEXT) const;

				/**
				 * @brief Gets the number of text datas of specified type in this track
				 *
				 * @param type The type of the text data. ITextData::LYRIC_TEXT by default
				 * @return int The number of text datas
				 */
				virtual int getTextDataCount(ITextData::TextDataType type = ITextData::LYRIC_TEXT) const;

				/**
				 * @brief Checks if the track contains information about the song's lyrics
				 *
				 * @return bool True if track contains lyrics otherwise false
				 */
				virtual bool hasLyrics() const;

				/**
				 * @brief Gets the start and end indices for lyrics to be displayed at the viewTime specified in the SongControl settings
				 *
				 * @param[out] start Variable to be set to the start index
				 * @param[out] end Variable to be set to the end index
				 */
				virtual void getLineIndicesForTime(int& start, int& end) const;

				/**
				 * @brief Gets the pitch of the highest note in the track
				 *
				 * @return int The highest note in the track
				 */
				virtual int getTopNote() const;

				/**
				 * @brief Gets the pitch of the lowest note in the track
				 *
				 * @return int The lowest note in the track
				 */
				virtual int getBottomNote() const;

				/**
				 * @brief Gets the track name
				 *
				 * @return const char The name
				 */
				virtual const char* getName() const;

				/**
				 * @brief Gets the current volume on the track
				 *
				 * @return int The current volume
				 */
				unsigned char getCurrVolume() const;

				/**
				 * @brief
				 *
				 * @param pitch
				 * @return bool
				 */
				virtual bool isWithinNoteRange(float pitch, int marigin) const;
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
