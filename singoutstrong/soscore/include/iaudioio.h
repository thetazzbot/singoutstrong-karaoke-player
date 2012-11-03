/** @file iaudioio.h
 * Header file with the IAudioInput interface
*/

#pragma once

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
		 * @brief A struct for holding the information about audio devices
		 *
		 */
		struct AudioDeviceInfo
		{
				const char* DeviceName; /**< @brief Device Name */
				int Id; /**< @brief Device Id used for device selection*/
		};

		/**
		 * @brief Interface for controlling the Audio Input
		 *
		 */
		class IAudioInput
		{
			public:
				virtual ~IAudioInput(){}

				/**
				 * @brief Starts capturing audio from the selected device
				 *
				 */
				virtual void startRecording() = 0;

				/**
				 * @brief Stops capturing audio from the selected device
				 *
				 */
				virtual void stopRecording() = 0;

				/**
				 * @brief Gets the couunt of available input devices
				 *
				 * @returns The count of available input devices
				 */
				virtual int getAvailableInDevicesCount() = 0;

				/**
				 * @brief Gets the information about an available input device
				 *
				 * @param index The index of the device (from 0 to getAvailableInDevicesCount)
				 * @returns The information about the input device
				 */
				virtual AudioDeviceInfo getAvailableInDevice(int index) = 0;

				/**
				 * @brief Gets the information about the currently selected device
				 *
				 * @returns The information about the currently selected input device
				 */
				virtual AudioDeviceInfo getCurrentDevice() = 0;

				/**
				 * @brief Selets the device with the given Id
				 *
				 * @param deviceId The Id of the device
				 * @returns True if the device selection was successful, otherwise false
				 */
				virtual bool setDevice(int deviceId) = 0;
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/
