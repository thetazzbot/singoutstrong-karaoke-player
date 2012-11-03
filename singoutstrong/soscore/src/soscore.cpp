#include "..\include\soscore.h"
#include "sosdevice.h"

namespace SoS
{
	namespace Core
	{

		DLLIMPORT ISoSDevice* createSoSDevice()
		{
			return new SoSDevice();
		}
	}
}
