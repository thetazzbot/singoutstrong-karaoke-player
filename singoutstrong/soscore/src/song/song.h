/** @file song.h
 * Header file with the Song class
*/

#pragma once

#include "..\..\include\isong.h"
#include "..\essentials.h"
#include "track.h"
#include <map>

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
		 * @brief Class implementing the ISong interface
		 *
		 */
		class Song : public ISong
		{
			public:
				Song();
				~Song();

				static const ISongSettings* settings;	/**< @brief the settings from the SongControl class */
				std::vector<Track*> tracks; /**< @brief The song's tracks */
				long songDuration; /**< @brief The song's time length */
				std::map<std::string, std::string> properties; /**< @brief music files (background, guitar, rhythm/bass, drums, vocals) */
				ISong::TextEncoding encoding;

				/**
				 * @brief Clears all song information
				 *
				 */
				void clear();

				/**
				 * @brief Clears the empty tracks
				 *
				 */
				void clearEmptyTracks();

				/**
				 * @brief Gets the value of the specified property
				 *
				 * @return const char The name of the property
				 */
				virtual const char* getProperty(const char* property) const;

				/**
				 * @brief Gets the number of tracks in the song
				 *
				 * @return int The number of tracks
				 */
				virtual int getTracksCount() const;

				/**
				 * @brief Gets the total time length of the song in miliseconds
				 *
				 * @return long The time length of the song
				 */
				virtual long getTotalTime() const;

				/**
				 * @brief Gets the track at the specified index
				 *
				 * @param track The index of the track
				 * @return ITrack Pointer to an ITrack interface
				 */
				virtual ITrack* getTrack(int track);

				/**
				 * @brief Gets the track at the specified index
				 *
				 * @param track The index of the track
				 * @return ITrack Readonly pointer to an ITrack interface
				 */
				virtual const ITrack* getTrack(int track) const;

				/**
				 * @brief
				 *
				 * @return const ITrack
				 */
				virtual const ITrack* getSelectedTrack() const;

				/**
				 * @brief
				 *
				 * @return TextEncoding
				 */
				virtual ISong::TextEncoding getEncoding() const;
		};

	}  /*! @} End of Doxygen Group Core */
} /*! @} End of Doxygen Group SoS */
