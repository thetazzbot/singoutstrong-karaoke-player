/** @file inote.h
 * Header file with the INote interface
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
		 * @brief Interface for accessing information about song's notes
		 *
		 */
		class INote
		{
			public:
				virtual ~INote(){}

				/**
				 * @brief Gets the length of the note in miliseconds
				 *
				 * @return long
				 */
				virtual long getTimeLength() const = 0;

				/**
				 * @brief Gets the pitch of the note
				 *
				 * @return int
				 */
				virtual int getNotePitch() const = 0;

				/**
				 * @brief Gets the time of the note's start in miliseconds
				 *
				 * @return long
				 */
				virtual long getStartTime() const = 0;

				/**
				 * @brief Gets the time of the note's end in miliseconds
				 *
				 * @return long
				 */
				virtual long getStopTime() const = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
