/** @file bassaudioinput.h
 * Header file with the BassAudioInput class
*/

#pragma once

#include "../../../../include/iaudioanalyzer.h"
#include "../../../../include/iaudioio.h"
#include "log.h"
#include <bass.h>

#if AUDIOFORMAT_SINT8
#define BASS_AUDIO_FORMAT BASS_SAMPLE_8BITS
#endif
#if AUDIOFORMAT_FLOAT32
#define BASS_AUDIO_FORMAT BASS_SAMPLE_FLOAT
#endif

namespace SoS
{
	namespace Core
	{

		/**
		 * @brief IAudioInput implementation using the BASS library
		 *
		 * While this implementations works, it cannot set the size of the input buffer (which seems to be around half
		 * of the samplerate). It's response time is too long to be very useful.
		 */
		class BassAudioInput : public IAudioInput
		{
			private:
				IAudioAnalyzer* audioAnalyzer; /**< @brief The analyzer that will process the audio on capture */

				int currDevice; /**< @brief The current device index */
				DWORD deviceHandle; /**< @brief The current device handle */

			public:
				BassAudioInput(IAudioAnalyzer* analyzer);
				~BassAudioInput();

				/**
				 * @brief Starts capturing audio from the selected device
				 *
				 */
				virtual void startRecording();

				/**
				 * @brief Stops capturing audio from the selected device
				 *
				 */
				virtual void stopRecording();

				/**
				 * @brief Gets the couunt of available input devices
				 *
				 * @returns The count of available input devices
				 */
				virtual int getAvailableInDevicesCount();

				/**
				 * @brief Gets the information about an available input device
				 *
				 * @param index The index of the device (from 0 to getAvailableInDevicesCount)
				 * @returns The information about the input device
				 */
				virtual AudioDeviceInfo getAvailableInDevice(int index);

				/**
				 * @brief Gets the information about the currently selected device
				 *
				 * @returns The information about the currently selected input device
				 */
				virtual AudioDeviceInfo getCurrentDevice();

				/**
				 * @brief Selects the device with the given Id
				 *
				 * @param deviceId The Id of the device
				 * @returns True if the device selection was successful, otherwise false
				 */
				virtual bool setDevice(int deviceId);
		};

		/**
		 * @brief The callback function for BASS library, when audio is captured
		 *
		 * @param handle The handle of the input device that cought the audio
		 * @param buffer The audio samples buffer
		 * @param length The size of the buffer
		 * @param user Custom data that can be passed to the function
		 * @return BOOL return TRUE if audio capture is to be continued, and FALSE if you want to stop it
		 *
		 * More detailed information can be found in the BASS documentation
		 */
		BOOL CALLBACK SoundInCallback( HRECORD handle, const void *buffer, DWORD length, void *user );
	}
}
