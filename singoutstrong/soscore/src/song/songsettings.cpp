#include "songcontrol.h"

namespace SoS
{
	namespace Core
	{
		long SongControl::getOutputLatency() const
		{
			return settings.outputLatency;
		}

		long SongControl::getCurrentTime() const
		{
			return settings.currTime;
		}

		long SongControl::getViewedTime() const
		{
			return settings.viewedTime;
		}

		long SongControl::getViewTimeRange() const
		{
			return settings.viewTimeRange;
		}

		char SongControl::getSelectedTrackIndex() const
		{
			return settings.selectedTrackIndex;
		}

		char SongControl::getKeyShift() const
		{
			return settings.keyShift;
		}

		void SongControl::setOutputLatency(long timeShift)
		{
			settings.outputLatency = timeShift;
		}

		void SongControl::setCurrentTime(long currTime)
		{
			if(timeBeyondSelection(currTime))
				currTime = settings.selectionStart;

			settings.currTime = currTime < 0 ? 0 :
								currTime > song->getTotalTime() ? song->getTotalTime() : currTime;
			pitchRecord->clear();

			if(playing)
				currentHandler->stopPlaying();

			currentHandler->moveTo(settings.currTime);

			if(playing && !timeBeyondSelection(settings.currTime))
				currentHandler->startPlaying();
		}

		void SongControl::setViewedTime(long viewedTime)
		{
			settings.viewedTime = viewedTime < song->getTotalTime() - settings.viewTimeRange ? viewedTime :
									song->getTotalTime() - settings.viewTimeRange;
		}

		void SongControl::setViewTimeRange(long timePageLength)
		{
			settings.viewTimeRange = timePageLength;
		}

		void SongControl::setSelectedTrackIndex(char index)
		{
			if(index < -1 || index >= song->tracks.size() || song->tracks[index]->notes.size() == 0)
			{
				for(int i = 0; i < song->tracks.size(); i++)
				{
					if(song->tracks[i]->notes.size() > 0)
					{
						settings.selectedTrackIndex = i;
						return;
					}
				}
				settings.selectedTrackIndex = -1;
			}
			else
				settings.selectedTrackIndex = index;
		}

		void SongControl::setKeyShift(char keyShift)
		{
			settings.keyShift = keyShift;
			pitchRecord->clear();
			currentHandler->changeKey();
		}

		unsigned char SongControl::getVolume()
		{
			return settings.volume;
		}

		void SongControl::setVolume(unsigned char volume)
		{
			settings.volume = volume;
			currentHandler->changeVolume();
		}

		unsigned char SongControl::getTextGroupBy() const
		{
			return settings.textGroupBy;
		}

		void SongControl::setTextGroupBy(unsigned char groupBy)
		{
			settings.textGroupBy = groupBy;
		}

		unsigned char SongControl::getTextLineCount() const
		{
			return settings.textLineCount;
		}

		void SongControl::setTextLineCount(unsigned char lineCount)
		{
			settings.textLineCount = lineCount;
		}

		long SongControl::getSelectionStart() const
		{
			return settings.selectionStart;
		}

		void SongControl::setSelectionStart(long time)
		{
			settings.selectionStart = time;
		}

		long SongControl::getSelectionEnd() const
		{
			return settings.selectionEnd;
		}

		void SongControl::setSelectionEnd(long time)
		{
			settings.selectionEnd = time;
		}

		bool SongControl::timeBeyondSelection(long time)
		{
			return settings.selectionEnd > 0 &&
					(time < settings.selectionStart || time > settings.selectionEnd);
		}
	}
}
