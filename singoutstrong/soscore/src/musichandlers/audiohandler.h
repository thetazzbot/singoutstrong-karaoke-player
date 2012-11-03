/** @file audiohandler.h
 * Header file that switches the between the StreamAudioHandler and MidiHandler classes to be used depending on the values in the implementations.h file
*/

#ifndef STREAMAUDIOHANDLER_H
#define STREAMAUDIOHANDLER_H

#include "../implementations.h"

#ifdef SOS_BASS_STREAM_AUDIO_HANDLER
#include "bassstreamaudiohandler/bassstreamaudiohandler.h"
typedef SoS::Core::BassStreamAudioHandler StreamAudioHandler; /**< @brief Use BassStreamAudioHandler for stream audio */
#endif

#ifdef SOS_JDK_MIDI_HANDLER
#include "jdkmidihandler/jdkmidihandler.h"
typedef SoS::Core::JdkMidiHandler MidiHandler;  /**< @brief Use JdkMidiHandler for midi audio */
#endif


#endif // STREAMAUDIOHANDLER_H
