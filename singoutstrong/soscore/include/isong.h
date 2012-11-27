/** @file isong.h
 * Header file with the ISong interface
*/

#pragma once

#include "itrack.h"

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
		 * @brief Interface for accessing information about the song
		 *
		 */
		class ISong
		{
			public:
				enum TextEncoding
				{
					ANSI = 0,
					UTF8
				};

				virtual ~ISong(){}

				/**
				 * @brief Gets the song name
				 *
				 * @return const char The song name
				 */
				virtual const char* getProperty(const char* property) const = 0;

				/**
				 * @brief Gets the number of tracks in the song
				 *
				 * @return int The number of tracks
				 */
				virtual int getTracksCount() const = 0;

				/**
				 * @brief Gets the total time length of the song in miliseconds
				 *
				 * @return long The time length of the song
				 */
				virtual long getTotalTime() const = 0;

				/**
				 * @brief Gets the track at the specified index
				 *
				 * @param track The index of the track
				 * @return ITrack Pointer to an ITrack interface
				 */
				virtual ITrack* getTrack(int track) = 0;

				/**
				 * @brief Gets the track at the specified index
				 *
				 * @param track The index of the track
				 * @return ITrack Readonly pointer to an ITrack interface
				 */
				virtual const ITrack* getTrack(int track) const = 0;

				/**
				 * @brief Gets the track selected in the SongSettings
				 *
				 * @return const ITrack Readonly pointer to an ITrack interface
				 */
				virtual const ITrack* getSelectedTrack() const = 0;

				/**
				 * @brief Gets the song's encoding
				 *
				 * @return TextEncoding The song encoding
				 */
				virtual TextEncoding getEncoding() const = 0;
		};

	}  /*! @} End of Doxygen Group Core */
} /*! @} End of Doxygen Group SoS */
