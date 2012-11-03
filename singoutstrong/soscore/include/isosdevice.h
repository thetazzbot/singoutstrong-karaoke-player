/** @file isosdevice.h
 * Header file with the ISoSDevice interface
*/

#pragma once

#include "iaudioanalyzer.h"
#include "iaudioio.h"
#include "isongcontrol.h"

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
		 * @brief Interface for the main device, that controlls all the core functions
		 *
		 */
		class ISoSDevice
		{
			public:
				virtual ~ISoSDevice(){}

				/**
				 * @brief Returns the audio analyzer interface
				 *
				 * @return IAudioAnalyzer The audio analyzer interface
				 */
				virtual IAudioAnalyzer* getAudioAnalyzer() = 0;

				/**
				 * @brief Returns the audio input interface
				 *
				 * @return IAudioInput The audio input interface
				 */
				virtual IAudioInput* getAudioInput() = 0;

				/**
				 * @brief Returns the song control interface
				 *
				 * @return ISongControl The song control interface
				 */
				virtual ISongControl* getSongControl() = 0;

				/**
				 * @brief Releases the device. Must be called before closing the program
				 *
				 */
				virtual void release() = 0;

				/**
				 * @brief Returns a readonly audio analyzer interface
				 *
				 * @return IAudioAnalyzer The audio analyzer interface
				 */
				virtual const IAudioAnalyzer* getAudioAnalyzer() const = 0;

				/**
				 * @brief Returns a readonly audio input interface
				 *
				 * @return IAudioInput The audio input interface
				 */
				virtual const IAudioInput* getAudioInput() const = 0;

				/**
				 * @brief Returns a readonly song control interface
				 *
				 * @return ISongControl The song control interface
				 */
				virtual const ISongControl* getSongControl() const = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
