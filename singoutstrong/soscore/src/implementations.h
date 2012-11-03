/** @file implementations.h
 * Header file that allows to quickly configure which classes are going to be used to implement given interfaces
*/

#ifndef IMPLEMENTATIONS_H
#define IMPLEMENTATIONS_H

/** @def SOS_RT_AUDIO_INPUT
 * @brief Use RtAudio Implementation of IAudioInput */
/** @def SOS_BASS_AUDIO_INPUT
 * @brief Use BASS Implementation of IAudioInput */

/** @def SOS_AUBIO_ANALYZER
 * @brief Use Aubio Implementation of IAudioAnalyzer */

/** @def SOS_BASS_STREAM_AUDIO_HANDLER
 * @brief Use BASS to handle audio streams */

/** @def SOS_JDK_MIDI_HANDLER
 * @brief Use JdksMidi to handle midi music */

#define SOS_RT_AUDIO_INPUT				1
#define SOS_BASS_AUDIO_INPUT			0

#define SOS_AUBIO_ANALYZER				1

#define SOS_BASS_STREAM_AUDIO_HANDLER	1

#define SOS_JDK_MIDI_HANDLER			1

#endif // IMPLEMENTATIONS_H
