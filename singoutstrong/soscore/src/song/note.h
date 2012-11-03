/** @file note.h
 * Header file with the Note class
*/

#pragma once

#include "../essentials.h"
#include "../../include/inote.h"
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
		 * @brief Class implementing the INote interface
		 *
		 */
		class Note : public INote
		{
			public:
				/** @brief Enum for support of note types from the Ultrastar format */
				enum Type { FREESTYLE = 'F', NORMAL = ':', GOLDEN = '*', SLIDE = '+', SLEEP = '-',
				  TAP = '1', HOLDBEGIN = '2', HOLDEND = '3', ROLL = '4', MINE = 'M', LIFT = 'L'} type;

				Note();

				long startTime;							/**< @brief The start time of the note */
				long stopTime;							/**< @brief The end time of the note */
				int notePitch;							/**< @brief The pitch of the note */
				static const ISongSettings* settings;	/**< @brief The song settings */

				/**
				 * @brief Gets the length of the note in miliseconds
				 *
				 * @return long
				 */
				virtual long getTimeLength() const;

				/**
				 * @brief Gets the pitch of the note
				 *
				 * @return int
				 */
				virtual int getNotePitch() const;

				/**
				 * @brief Gets the time of the note's start in miliseconds
				 *
				 * @return long
				 */
				virtual long getStartTime() const;

				/**
				 * @brief Gets the time of the note's end in miliseconds
				 *
				 * @return long
				 */
				virtual long getStopTime() const;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
