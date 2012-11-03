/** @file aubioanalyzer.h
 * Header file with the AubioAnalyzer class
*/

#ifndef _AUBIO_SOUND_PROCESSOR
#define _AUBIO_SOUND_PROCESSOR

#define PITCH_SAMPLES_COUNT 5

#include "../../../../include/iaudioanalyzer.h"
#include "../../pitchrecord/pitchrecord.h"
#include "../../../../include/isongsettings.h"
#include "aubiofuncs.h"
#include "log.h"

#include <math.h>
#include <float.h>

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
		 * @brief IAudioAnalyzer implementation using the Aubio library
		 *
		 */
		class AubioAnalyzer : public IAudioAnalyzer
		{
			private:
				HINSTANCE hInstLibrary; /**< @brief Handle to the Aubio library */
				NewAubioPitchdetectionFunc NewAubioPitchdetection; /**< @brief Handle to the Aubio pitch detector creation function */
				AubioPitchdetectionFunc AubioPitchdetection; /**< @brief Handle to the Aubio pitch detection fucntion */
				NewFvecFunc NewFvec; /**< @brief Handle to the Aubio sample vector creation function */
				DelAubioPitchdetectionFunc DelAubioPitchdetection; /**< @brief Handle to the Aubio pitch detector release function */
				DelFvecFunc DelFvec; /**< @brief Handle to the aubio sample vector release function */
				AubioCleanupFunc AubioCleanup; /**< @brief Handle to the Aubio library clean up function */
				bool dllLoaded; /**< @brief The variable notifying about whether the Aubio library was loaded */

				// ------------------------------------------------------------------
				// internal aubio variables

				unsigned int vector_size;					/**< @brief Samples vector size */
				unsigned int hop_s;							/**< @brief Hop size */
				unsigned int samplerate;					/**< @brief Samplerate */
				unsigned int channels;						/**< @brief Number of channels */

				fvec_t * input_vec; /**< @brief Vector with the audio samples to be analyzed  */
				aubio_pitchdetection_t* pitch_output ; /**< @brief The pitch detector */

				// ------------------------------------------------------------------

				float samplesBuffer[BUFFER_SIZE]; /**< @brief The buffer with audio samples */
				int currentChunk; /**< @brief The current subsection of the buffer, that will be copies to the Aubio vector */
				int chunkCount; /**< @brief The count of the sections the buffer was divided into */

				aubio_pitchdetection_mode detectionMode; /**< @brief Aubio pitch detection mode */
				aubio_pitchdetection_type detectionType; /**< @brief Aubio pitch detection type */
				float volumeThreshold; /**< @brief The volume threshold below which the samples won't be further analyzed */
				unsigned int newVectorSize; /**< @brief The new size of the samples vector that was requested */
				bool typeChanged; /**< @brief Pitch detection type was changed */

				PitchRecord* pitchRecord; /**< @brief The record of the processed samples */
				float pitch; /**< @brief The current pitch */
				float amplitude; /**< @brief The current amplitude */

				/**
				 * @brief Copies samples from the buffer to the Aubio vector
				 *
				 * @param[out] fvec The vector to copy to
				 * @param size The size of the vector
				 */
				void copyToFVec(fvec_t * fvec, int size);

				/**
				 * @brief Loads the Aubio library and all the needed functions
				 *
				 */
				void InitAubioDll();

			public:
				/**
				 * @brief Default constructor for the Aubio Analyzer
				 *
				 */
				AubioAnalyzer();
				/**
				 * @brief Destructor for the Aubio Analyzer
				 *
				 */
				~AubioAnalyzer();

				/**
				 * @brief Sets up the pitch detector and samples vector
				 *
				 */
				void setup();

				/**
				 * @brief Processes the captured audio samples, and stores the information in the PitchRecord
				 *
				 * @param buffer The array of audio samples
				 * @param bufferSize The size of the array
				 */
				virtual void processAudio(AUDIO_DATA_TYPE* buffer, int bufferSize);

				/**
				 * @brief Gets the pitch of the most recently captured audio samples
				 *
				 * @return float The pitch of the captured audio samples
				 */
				virtual float getPitch() const;

				/**
				 * @brief Gets the amplitude of the most recently captured audio samples
				 *
				 * @return float The amplitude of the captured audio samples
				 */
				virtual float getAmplitude() const;

				/**
				 * @brief Gets the volume threshold, below which the sample will not be further analyzed
				 *
				 * @return float The volume threshold
				 */
				virtual float getVolumeThreshold() const;

				/**
				 * @brief Sets the volume threshold, below which the sample will not be further analyzed
				 *
				 * @param threshold The volume threshold
				 */
				virtual void setVolumeThreshold(float threshold);

				/**
				 * @brief Gets the size of the array of samples to analyze
				 *
				 * @return int The size of the array
				 */
				virtual int getSamplesArraySize() const;

				/**
				 * @brief Sets the size of the array of samples to analyze
				 *
				 * @param int The size of the array
				 */
				virtual void setSamplesArraySize(int hopSize);

				/**
				 * @brief Gets the record of processed samples
				 *
				 * @return IPitchRecord The record of processed samples
				 */
				virtual IPitchRecord* getPitchRecord();

				/**
				 * @brief Gets the record of processed samples
				 *
				 * @return const IPitchRecord The record of processed samples
				 */
				virtual const IPitchRecord* getPitchRecord() const;
		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/

#endif	

