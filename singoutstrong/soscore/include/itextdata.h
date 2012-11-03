/** @file itextdata.h
 * Header file with the ITextData interface
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

/** @def TEXT_DATA_TYPES_COUNT
 * @brief The amount of text data types in the TextDataType enum */

#define TEXT_DATA_TYPES_COUNT 16 /**< Used for the size of the textData array in the Track class */

		/**
		 * @brief Interface for accessing the information about the track's text data
		 *
		 */
		class ITextData
		{
			public:

				/**
				 * @brief Enum for describing the type of the text data
				 *
				 */
				enum TextDataType
				{
						GENERIC_TEXT   = 0x01,
						COPYRIGHT      = 0x02,
						TRACK_NAME     = 0x03, // Sequence/Track Name // was 0x04
						INSTRUMENT_NAME = 0x04, // was 0x03
						LYRIC_TEXT     = 0x05,
						MARKER_TEXT    = 0x06,
						CUE_POINT      = 0x07,
						PROGRAM_NAME   = 0x08,
						DEVICE_NAME    = 0x09,
						GENERIC_TEXT_A = 0x0A,
						GENERIC_TEXT_B = 0x0B,
						GENERIC_TEXT_C = 0x0C,
						GENERIC_TEXT_D = 0x0D,
						GENERIC_TEXT_E = 0x0E,
						GENERIC_TEXT_F = 0x0F
				};

				virtual ~ITextData(){}

				/**
				 * @brief Gets the time in miliseconds that the text should be displayed
				 *
				 * @return long The display time
				 */
				virtual long getTime() const = 0;

				/**
				 * @brief Gets the text
				 *
				 * @return const char The text
				 */
				virtual const char* getText() const = 0;

				/**
				 * @brief Gets the number of the text's line
				 *
				 * @return int The line number
				 */
				virtual int getLineNo() const = 0;

				/**
				 * @brief Gets the text's type
				 *
				 * @return TextDataType
				 */
				virtual TextDataType getType() const = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
