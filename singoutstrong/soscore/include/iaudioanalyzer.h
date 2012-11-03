/** @file iaudioanalyzer.h
 * Header file with the IAudioAnalyzer interface
*/

#pragma once

#include "ipitchrecord.h"
#include "../src/soundproperties.h"

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
		 * @brief Interface for analyzing the captured audio
		 *
		 */
		class IAudioAnalyzer
		{
			public:
				virtual ~IAudioAnalyzer(){}

				/**
				 * @brief Processes the captured audio samples, and stores the information in the PitchRecord
				 *
				 * @param buffer The array of audio samples
				 * @param bufferSize The size of the array
				 */
				virtual void processAudio(AUDIO_DATA_TYPE* buffer, int bufferSize) = 0;

				/**
				 * @brief Gets the pitch of the most recently captured audio samples
				 *
				 * @return float The pitch of the captured audio samples
				 */
				virtual float getPitch() const = 0;

				/**
				 * @brief Gets the amplitude of the most recently captured audio samples
				 *
				 * @return float The amplitude of the captured audio samples
				 */
				virtual float getAmplitude() const = 0;

				/**
				 * @brief Gets the volume threshold, below which the sample will not be further analyzed
				 *
				 * @return float The volume threshold
				 */
				virtual float getVolumeThreshold() const = 0;

				/**
				 * @brief Sets the volume threshold, below which the sample will not be further analyzed
				 *
				 * @param threshold The volume threshold
				 */
				virtual void setVolumeThreshold(float threshold) = 0;

				/**
				 * @brief Gets the size of the array of samples to analyze
				 *
				 * @return int The size of the array
				 */
				virtual int getSamplesArraySize() const = 0;

				/**
				 * @brief Sets the size of the array of samples to analyze
				 *
				 * @param int The size of the array
				 */
				virtual void setSamplesArraySize(int arraySize) = 0;

				/**
				 * @brief Gets the record of processed samples
				 *
				 * @return IPitchRecord The record of processed samples
				 */
				virtual IPitchRecord* getPitchRecord() = 0;

				/**
				 * @brief Gets the record of processed samples
				 *
				 * @return const IPitchRecord The record of processed samples
				 */
				virtual const IPitchRecord* getPitchRecord() const = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
