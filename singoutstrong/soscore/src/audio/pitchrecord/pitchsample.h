/** @file pitchsample.h
 * Header file with the PitchSample class
*/

#pragma once

#include "..\..\..\include\ipitchsample.h"

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
		 * @brief Class implementing the IPitchSample interface
		 *
		 */
		class PitchSample : public IPitchSample
		{
			public:
				float pitch; /**< @brief The pitch of the sample */
				float accuracy; /**< @brief The accuracy of the sample */
				long timestamp; /**< @brief The timestamp of the sample */
				SampleState state; /**< @brief The state of the sample */

				PitchSample();
				/**
				 * @brief Gets the pitch of the sample
				 *
				 * @return float The pitch of the sample
				 */
				virtual float getPitch() const;

				/**
				 * @brief Gets the accuracy of the sample, relative to song's notes.
				 *	Valid accuracy values range from -infinity to 1. \n
				 *	A value of 1 means 100% accuracy. A value of 0 means the pitch missed by a whole note, a value of -1
				 *	means the pitch missed by 2 notes, etc. \n
				 *	Any value above 1 is invalid, which usually means the accuracy was not yet calculated.
				 *
				 * @return float The accuracy of the sample
				 */
				virtual float getAccuracy() const;

				/**
				 * @brief Gets the timestamp of the sample
				 *
				 * @return long Timestamp of the sample in miliseconds
				 */
				virtual long getTimestamp() const;

				/**
				 * @brief Gets the state of the sample, signifying it's place in a samples section
				 *
				 * @return SampleState The sample state
				 */
				virtual SampleState getState() const;

				/**
				 * @brief A function for comparing the timestamp of two samples, used to quickly find a sample near a given timestamp
				 *
				 * @return bool true if first sample timestamp is lower the the second's
				 */
				static bool CompareTimestamp(PitchSample ps1, PitchSample ps2)
				{
					return ps1.timestamp < ps2.timestamp;
				}
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
