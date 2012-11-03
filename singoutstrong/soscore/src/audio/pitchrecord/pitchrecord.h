/** @file pitchrecord.h
 * Header file with the PitchRecord class
*/

#pragma once

#include "../../../include/ipitchrecord.h"
#include "../../essentials.h"
#include "pitchsample.h"

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
		 * @brief Class implementing the IPitchRecord interface
		 *
		 */
		class PitchRecord : public IPitchRecord
		{
			private:
				std::vector<PitchSample> pitchSamples; /**< @brief The collection of samples */

			public:
				PitchRecord();

				/**
				 * @brief Adds a sample at the end of the record
				 *	This method doesn't have a timestamp or accuracy parametor, so it automatically assigns
				 *	the current time to the sample, and an invalid accuracy
				 *
				 * @param pitch The pitch of the sample
				 */
				virtual void addSample(float pitch);

				/**
				 * @brief Adds a sample at the end of the record
				 *
				 * @param pitch The pitch of the sample
				 * @param time The timestamp of the sample
				 * @param accuracy The accuracy of the sample relative to notes from the song within the same time. The default value is invalid
				 */
				virtual void addSample(float pitch, long time, float accuracy = 2);

				/**
				 * @brief Marks the last sample as an end of a sample section
				 *
				 */
				virtual void markAsEnd();

				/**
				 * @brief Gets the sample from the record
				 *
				 * @param index The index of the sample in the collection
				 * @return const IPitchSample The sample
				 */
				virtual const IPitchSample* getSample(int index) const;

				/**
				 * @brief Gets the index of the last sample in the collection
				 *
				 * @return int Index of the last sample in the collection
				 */
				virtual int getCurrentSampleIndex() const;

				/**
				 * @brief Clears the record
				 *
				 */
				virtual void clear();

				/**
				 * @brief Gets the index of the sample closest to the time parameter, but after it
				 *
				 * @param time The time of the sample who's index is to be retrieved
				 * @return int The index of the sample
				 */
				virtual int getStartIndex(long viewTime) const;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
