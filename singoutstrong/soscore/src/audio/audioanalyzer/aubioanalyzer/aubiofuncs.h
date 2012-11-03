/** @file aubiofuncs.h
 * Header file with functions from the Aubio library
*/

#ifndef _AUBIO_FUNCTIONS_DLL__
#define _AUBIO_FUNCTIONS_DLL__

#include "aubio.h"

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
		 * @brief The Aubio pitch detector creation function
		 *
		 */
		typedef aubio_pitchdetection_t* (*NewAubioPitchdetectionFunc)(ba_uint_t bufsize,
																	  ba_uint_t hopsize,
																	  ba_uint_t channels,
																	  ba_uint_t samplerate,
																	  aubio_pitchdetection_type type,
																	  aubio_pitchdetection_mode mode);

		/**
		 * @brief The Aubio pitch detection fucntion
		 *
		 */
		typedef smpl_t (*AubioPitchdetectionFunc)(aubio_pitchdetection_t * p, fvec_t * ibuf);

		/**
		 * @brief The Aubio sample vector creation function
		 *
		 */
		typedef fvec_t* (*NewFvecFunc)(unsigned int, unsigned int);

		/**
		 * @brief The Aubio pitch detector release function
		 *
		 */
		typedef void (*DelAubioPitchdetectionFunc)(aubio_pitchdetection_t * p);

		/**
		 * @brief The aubio sample vector release function
		 *
		 */
		typedef void (*DelFvecFunc)(fvec_t *s);

		/**
		 * @brief The Aubio library clean up function
		 *
		 */
		typedef void (*AubioCleanupFunc)(void);

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group SoS*/

#endif
