/** @file ipitchsample.h
 * Header file with the IPitchSample interface
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
		 * @brief Interface for accessing the properties of a IPitchRecord sample
		 *
		 */
		class IPitchSample
		{
			public:
				/**
				 * @brief Enum for describing the place of a sample within a broader section. Used for rendering
				 *
				 */
				enum SampleState
				{
					SAMPLE_START,	/**< @brief This sample is the start of a section */
					SAMPLE_MIDDLE,	/**< @brief This sample is the middle of a section */
					SAMPLE_END		/**< @brief This sample is the end of a section */
				};

				virtual ~IPitchSample(){}

				/**
				 * @brief Gets the pitch of the sample
				 *
				 * @return float The pitch of the sample
				 */
				virtual float getPitch() const = 0;

				/**
				 * @brief Gets the accuracy of the sample, relative to song's notes.
				 *	Valid accuracy values range from -infinity to 1. \n
				 *	A value of 1 means 100% accuracy. A value of 0 means the pitch missed by a whole note, a value of -1
				 *	means the pitch missed by 2 notes, etc. \n
				 *	Any value above 1 is invalid, which usually means the accuracy was not yet calculated.
				 *
				 * @return float The accuracy of the sample
				 */
				virtual float getAccuracy() const = 0;

				/**
				 * @brief Gets the timestamp of the sample
				 *
				 * @return long Timestamp of the sample in miliseconds
				 */
				virtual long getTimestamp() const = 0;

				/**
				 * @brief Gets the state of the sample, signifying it's place in a samples section
				 *
				 * @return SampleState The sample state
				 */
				virtual SampleState getState() const = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
