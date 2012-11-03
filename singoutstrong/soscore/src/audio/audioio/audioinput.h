/** @file audioinput.h
 * Header file that switches the between the AudioInput classes to be used depending on the values in the implementations.h file
*/

#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include "../../implementations.h"

#if SOS_RT_AUDIO_INPUT
#include "rtaudioinput/rtaudioinput.h"
typedef SoS::Core::RtAudioInput AudioInput; /**< @brief Use RtAudioInput */
#endif

#if SOS_BASS_AUDIO_INPUT
#include "bassaudioinput/bassaudioinput.h"
typedef SoS::Core::BassAudioInput AudioInput; /**< @brief Use BassAudioInput */

#if AUDIOFORMAT_SINT16 || AUDIOFORMAT_SINT32 || AUDIOFORMAT_FLOAT64
#error BASS supports only the AUDIOFORMAT_SINT8 and AUDIOFORMAT_FLOAT32 audio formats
#endif

#endif

#endif // AUDIOINPUT_H
