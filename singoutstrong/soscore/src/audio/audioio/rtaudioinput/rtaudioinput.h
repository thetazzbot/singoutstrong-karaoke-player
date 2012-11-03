/** @file rtaudioinput.h
 * Header file with the RtAudioInput class
*/

#pragma once

#include "../../audioanalyzer/audioanalyzer.h"
#include "../../../../include/iaudioio.h"
#include "rtaudio\rtaudio.h"
#include "rtaudio\rtmidi.h"
#include "log.h"

#if AUDIOFORMAT_SINT8
#define RT_AUDIO_FORMAT RTAUDIO_SINT8
#endif
#if AUDIOFORMAT_SINT16
#define RT_AUDIO_FORMAT RTAUDIO_SINT16
#endif
#if AUDIOFORMAT_SINT32
#define RT_AUDIO_FORMAT RTAUDIO_SINT32
#endif
#if AUDIOFORMAT_FLOAT32
#define RT_AUDIO_FORMAT RTAUDIO_FLOAT32
#endif
#if AUDIOFORMAT_FLOAT64
#define RT_AUDIO_FORMAT RTAUDIO_FLOAT64
#endif

namespace SoS
{
	namespace Core
	{

		/**
		 * @brief IAudioInput implementation using the RtAudio library
		 *
		 */
		class RtAudioInput : public IAudioInput
		{
			private:
				IAudioAnalyzer* audioAnalyzer; /**< @brief The analyzer that will process the audio on capture */
				RtAudio rtAudio; /**< @brief The RtAudio object */
				RtAudio::StreamParameters parameters; /**< @brief RtAudio stream parameters */

			public:
				RtAudioInput(IAudioAnalyzer* analyzer);
				~RtAudioInput();

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
				 * @brief Selets the device with the given Id
				 *
				 * @param deviceId The Id of the device
				 * @returns True if the device selection was successful, otherwise false
				 */
				virtual bool setDevice(int deviceId);
		};

		/**
		 * @brief The callback function for RtAudio library, when audio is captured
		 *
		 * @param outputBuffer The output audio samples buffer
		 * @param inputBuffer The input audio samples buffer
		 * @param nBufferFrames The size of the buffer
		 * @param streamTime Number of seconds that passed since the stream was started
		 * @param status Indicated overflow or underflow of the stream
		 * @param data Custom data that can be passed to the function
		 * @return int Should return 0 if normal operations are to continue
		 *
		 * More detailed information can be found in the RtAudio documentation, and the RtAudio.h file
		 */
		int SoundInCallback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
							 double streamTime, RtAudioStreamStatus status, void *data );

	}
}
