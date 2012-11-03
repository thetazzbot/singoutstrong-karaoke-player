/** @file sosdevice.h
 * Header file with the SoSDevice class
*/

#pragma once

#include "../include/isosdevice.h"
#include <fstream>
#include "audio/audioanalyzer/audioanalyzer.h"
#include "audio/audioio/audioinput.h"
#include "song/songcontrol.h"
#include "log.h"

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
		 * @brief Class implementing the ISoSDevice
		 *
		 */
		class SoSDevice : public ISoSDevice
		{
			private:
				IAudioAnalyzer* _audioAnalyzer; /**< @brief Audio analyzer interface */
				IAudioInput* _audioInput; /**< @brief Audio input interface */
				ISongControl* _songControl; /**< @brief Song control interface */

			public:
				SoSDevice();
				~SoSDevice();

				/**
				 * @brief Returns the audio analyzer interface
				 *
				 * @return IAudioAnalyzer The audio analyzer interface
				 */
				virtual IAudioAnalyzer* getAudioAnalyzer();

				/**
				 * @brief Returns the audio input interface
				 *
				 * @return IAudioInput The audio input interface
				 */
				virtual IAudioInput* getAudioInput();

				/**
				 * @brief Returns the song control interface
				 *
				 * @return ISongControl The song control interface
				 */
				virtual ISongControl* getSongControl();

				/**
				 * @brief Releases the device. Must be called before closing the program
				 *
				 */
				virtual void release();

				/**
				 * @brief Returns a readonly audio analyzer interface
				 *
				 * @return IAudioAnalyzer The audio analyzer interface
				 */
				virtual const IAudioAnalyzer* getAudioAnalyzer() const;

				/**
				 * @brief Returns a readonly audio input interface
				 *
				 * @return IAudioInput The audio input interface
				 */
				virtual const IAudioInput* getAudioInput() const;

				/**
				 * @brief Returns a readonly song control interface
				 *
				 * @return ISongControl The song control interface
				 */
				virtual const ISongControl* getSongControl() const;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
