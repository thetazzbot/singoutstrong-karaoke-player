/** @file itrack.h
 * Header file with the ITrack interface
*/
#pragma once

#include "inote.h"
#include "itextdata.h"

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
		 * @brief Interface for accessing information about the song's track
		 *
		 */
		class ITrack
		{
			public:
				virtual ~ITrack(){}

				/**
				 * @brief Gets the note at a specified index
				 *
				 * @param index The index of the note
				 * @return INote Pointer to a INote interface
				 */
				virtual INote* getNote(int index) = 0;

				/**
				 * @brief Gets the note at a specified index
				 *
				 * @param index The index of the note
				 * @return INote Readonly pointer to a INote interface
				 */
				virtual const INote* getNote(int index) const = 0;

				/**
				 * @brief Gets the index of the first note after the viewTime specified in the SongControl settings
				 *
				 * @return int The index of the note
				 */
				virtual int getNoteIndexForViewTime() const = 0;

				/**
				 * @brief Gets the number of notes in this track
				 *
				 * @return int The number of notes
				 */
				virtual int getNoteCount() const = 0;

				/**
				 * @brief Gets the TextData at a specified index, and of specified type
				 *
				 * @param index The index of the text data
				 * @param type The type of the text data. ITextData::LYRIC_TEXT by default
				 * @return ITextData Pointer to a ITextData interface
				 */
				virtual ITextData* getTextData(int index, ITextData::TextDataType type = ITextData::LYRIC_TEXT) = 0;

				/**
				 * @brief Gets the TextData at a specified index, and of specified type
				 *
				 * @param index The index of the text data
				 * @param type The type of the text data. ITextData::LYRIC_TEXT by default
				 * @return ITextData Readonly pointer to a ITextData interface
				 */
				virtual const ITextData* getTextData(int index, ITextData::TextDataType type = ITextData::LYRIC_TEXT) const = 0;

				/**
				 * @brief Gets the number of text datas of specified type in this track
				 *
				 * @param type The type of the text data. ITextData::LYRIC_TEXT by default
				 * @return int The number of text datas
				 */
				virtual int getTextDataCount(ITextData::TextDataType type = ITextData::LYRIC_TEXT) const = 0;

				/**
				 * @brief Checks if the track contains information about the song's lyrics
				 *
				 * @return bool True if track contains lyrics otherwise false
				 */
				virtual bool hasLyrics() const = 0;

				/**
				 * @brief Gets the start and end indices for lyrics to be displayed at the viewTime specified in the SongControl settings
				 *
				 * @param[out] start Variable to be set to the start index
				 * @param[out] end Variable to be set to the end index
				 */
				virtual void getLineIndicesForTime(int& start, int& end) const = 0;

				/**
				 * @brief Gets the pitch of the highest note in the track
				 *
				 * @return int The highest note in the track
				 */
				virtual int getTopNote() const = 0;

				/**
				 * @brief Gets the pitch of the lowest note in the track
				 *
				 * @return int The lowest note in the track
				 */
				virtual int getBottomNote() const = 0;

				/**
				 * @brief Gets the track name
				 *
				 * @return const char The name
				 */
				virtual const char* getName() const = 0;

				/**
				 * @brief Gets the current volume on the track
				 *
				 * @return int The current volume
				 */
				virtual unsigned char getCurrVolume() const = 0;

				/**
				 * @brief
				 *
				 * @param pitch
				 * @return bool
				 */
				virtual bool isWithinNoteRange(float pitch, int marigin) const = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
