/** @file textdata.h
 * Header file with the TextData class
*/

#pragma once

#include "../essentials.h"
#include "../../include/itextdata.h"
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
		 * @brief Class implementing the ITextData interface
		 *
		 */
		class TextData : public ITextData
		{
			public:
				TextData();

				std::string text;						/**< @brief The text */
				long time;								/**< @brief The display time of the text */
				int lineNo;								/**< @brief The line number of the text */
				int paragraphNo;						/**< @brief The paragraph number of the text */
				TextDataType type;						/**< @brief The text's type */
				static const ISongSettings* settings;	/**< @brief the settings from the SongControl class */

				/**
				 * @brief Gets the time in miliseconds that the text should be displayed
				 *
				 * @return long The display time
				 */
				virtual long getTime() const;

				/**
				 * @brief Gets the text
				 *
				 * @return const char The text
				 */
				virtual const char* getText() const;

				/**
				 * @brief Gets the number of the text's line
				 *
				 * @return int The line number
				 */
				virtual int getLineNo() const;

				/**
				 * @brief Gets the text's type
				 *
				 * @return TextDataType
				 */
				virtual ITextData::TextDataType getType() const;

				/**
				 * @brief Compares the time of the first textData and the currentTime in the SongControl settings
				 *
				 * Used to quickly find the index of the lyrics at current time
				 *
				 * @param td1 The text data
				 * @param td2 Second text data needed for the method's signature, but not used
				 * @return bool True if the text's time is lower then the current time
				 */
				static bool CmpFirstAfterCurrTime(const TextData* td1, const TextData* td2 = NULL)
				{
					return td1->time < TextData::settings->getCurrentTime();
				}
		};
	}
}
