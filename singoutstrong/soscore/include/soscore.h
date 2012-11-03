/** @file soscore.h
 * Header file with the createSoSDevice function
*/

#ifndef SOS_CORE_H__
#define SOS_CORE_H__

#if SOSCORE_LIBRARY || BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

#include "isosdevice.h"

namespace SoS
{
	namespace Core
	{
		/**
		 * @brief Creates the main SoS device
		 *
		 * @return ISingDevice
		 */
		DLLIMPORT ISoSDevice* createSoSDevice();
	}
}


#endif

