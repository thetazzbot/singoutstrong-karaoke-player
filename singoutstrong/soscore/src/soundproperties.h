/** @file SoundProperties.h
 * Header file with defines and typedefs that help set up the sound properties for the AudioInput and AudioAnalyzer
*/
#ifndef SOUND_PROPERTIES_H__
#define SOUND_PROPERTIES_H__

/** @def AUDIO_SAMPLERATE
 * @brief Audio samplerate */
/** @def AUDIO_SAMPLES
 * @brief Number of audio inpput samples */
/** @def BUFFER_SIZE
 * @brief Analyzer buffer size */

/** @def AUDIOFORMAT_SINT8
 * @brief Signed char audio format */
/** @def AUDIOFORMAT_SINT16
 * @brief Signed short audio format */
/** @def AUDIOFORMAT_SINT32
 * @brief Signed int audio format */
/** @def AUDIOFORMAT_FLOAT32
 * @brief Float audio format */
/** @def AUDIOFORMAT_FLOAT64
 * @brief Double audio format */

#define AUDIO_SAMPLERATE		44100	/**< The audio sample rate that will be used by the AudioInput and AudioAnalyzer classes */
#define AUDIO_SAMPLES			256		/**< The number of samples that should be captured by AudioInput on every callback */
#define BUFFER_SIZE				8192	/**< The size of the audio buffer for the analyzer */

#define AUDIOFORMAT_SINT8		0 /**< Set this to 1, if you want the AudioInput and the AudioAnalyzer to sotre the audio samples as a signed char \n WARNING: Only one of the AUDIOFORMAT defines should be set at a time */
#define AUDIOFORMAT_SINT16		0 /**< Set this to 1, if you want the AudioInput and the AudioAnalyzer to sotre the audio samples as a signed short \n WARNING: Only one of the AUDIOFORMAT defines should be set at a time */
#define AUDIOFORMAT_SINT32		0 /**< Set this to 1, if you want the AudioInput and the AudioAnalyzer to sotre the audio samples as a signed int \n WARNING: Only one of the AUDIOFORMAT defines should be set at a time */
#define AUDIOFORMAT_FLOAT32		1 /**< Set this to 1, if you want the AudioInput and the AudioAnalyzer to sotre the audio samples as a float \n WARNING: Only one of the AUDIOFORMAT defines should be set at a time */
#define AUDIOFORMAT_FLOAT64		0 /**< Set this to 1, if you want the AudioInput and the AudioAnalyzer to sotre the audio samples as a double \n WARNING: Only one of the AUDIOFORMAT defines should be set at a time */

#if AUDIOFORMAT_SINT8
		typedef char  AUDIO_DATA_TYPE; /**< Typedef for the audio samples data type, used by AudioInput and AudioAnalyzer */
#endif
#if AUDIOFORMAT_SINT16
		typedef signed short  AUDIO_DATA_TYPE; /**< Typedef for the audio samples data type, used by AudioInput and AudioAnalyzer */
#endif
#if AUDIOFORMAT_SINT32
		typedef signed int  AUDIO_DATA_TYPE; /**< Typedef for the audio samples data type, used by AudioInput and AudioAnalyzer */
#endif
#if AUDIOFORMAT_FLOAT32
		typedef float  AUDIO_DATA_TYPE; /**< Typedef for the audio samples data type, used by AudioInput and AudioAnalyzer */
#endif
#if AUDIOFORMAT_FLOAT64
		typedef double  AUDIO_DATA_TYPE; /**< Typedef for the audio samples data type, used by AudioInput and AudioAnalyzer */
#endif

#endif
