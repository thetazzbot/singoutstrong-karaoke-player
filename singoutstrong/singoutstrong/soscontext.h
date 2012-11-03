/** @file soscontext.h
 * Header file with the SoSContext class
*/

#ifndef SOSCONTEXT_H
#define SOSCONTEXT_H

#include <soscore.h>
#include <stddef.h>

/// \cond 0

using namespace SoS;
using namespace Core;

/// \endcond

/*!
 *  \addtogroup SoS
 *  @{
 */

//! Main SingOutStrong namespace
namespace SoS
{
	/*!
	 *  \addtogroup QtGui
	 *  @{
	 */

	//! User Interface
	namespace QtGui
	{

		/**
		 * @brief Class holding interfaces from the Core library
		 *
		 */
		class SoSContext
		{
			public:
				SoSContext();

				ISoSDevice* SingDevice;	/**< @brief The main device */
				IAudioInput* AudioInput;		/**< @brief The audio input */
				IAudioAnalyzer* AudioAnalyzer;	/**< @brief The audio analyzer */
				ISongControl* SongControl;		/**< @brief The song controller */
		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SOSCONTEXT_H
