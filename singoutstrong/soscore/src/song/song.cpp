#include "song.h"

namespace SoS
{
	namespace Core
	{
		const ISongSettings* Song::settings = NULL;

		Song::Song() :
			songDuration(0)
		{
		}

		Song::~Song()
		{
			clear();
		}

		void Song::clear()
		{
			name.clear();
			description.clear();
			songDuration = 0;

			for(int i = 0; i < tracks.size(); i++)
				delete tracks[i];

			tracks.clear();
		}

		void Song::clearEmptyTracks()
		{
			int i = tracks.size()-1;
			while(i >= 0 && tracks[i]->getAllTextDataCount() == 0 && tracks[i]->notes.size() == 0)
			{
				delete tracks[i];
				tracks.pop_back();
				i--;
			}
		}

		int Song::getTracksCount() const
		{
			return tracks.size();
		}

		long Song::getTotalTime() const
		{
			return songDuration / settings->getTempo();
		}

		ITrack* Song::getTrack(int track)
		{
			return track >= 0 && track < tracks.size() ? tracks[track] : NULL;
		}

		const ITrack* Song::getTrack(int track) const
		{
			return track >= 0 && track < tracks.size() ? tracks[track] : NULL;
		}

		const char* Song::getName() const
		{
			return name.c_str();
		}

		const char* Song::getDescription() const
		{
			return description.c_str();
		}

		const ITrack* Song::getSelectedTrack() const
		{
			return getTrack(settings->getSelectedTrackIndex());
		}

		ISong::TextEncoding Song::getEncoding() const
		{
			return encoding;
		}
	}
}
