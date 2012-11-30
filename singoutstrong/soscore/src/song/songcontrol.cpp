#include "songcontrol.h"

namespace SoS
{
	namespace Core
	{

		SongControl::SongControl(IAudioAnalyzer* audioAnalyzer) :
			pitchRecord(new PitchRecord()),
			song(new Song()),
			midiHandler(NULL),
			streamHandler(NULL),
			currentHandler(NULL),
			averageAccuracy(0),
			analyzed(false),
			loaded(false),
			playing(false),
			audioAnalyzer(audioAnalyzer)
		{
			midiHandler = new MidiHandler(song, this);
			streamHandler = new StreamAudioHandler(song, this);
			currentHandler = midiHandler;

			settings.selectionStart = -1;
			settings.selectionEnd = -1;
			settings.outputLatency = 350;
			settings.currTime = 0;
			settings.viewedTime = 0;
			settings.selectedTrackIndex = 0;
			settings.keyShift = 0;
			settings.tempo = 1.0;
			settings.viewTimeRange = 5000;
			settings.volume = 255;
			settings.textLineCount = 4;
			settings.textGroupBy = 2;

			TextData::settings = this;
			Note::settings = this;
			Track::settings = this;
			Song::settings = this;
		}

		SongControl::~SongControl()
		{
			delete midiHandler;
			delete streamHandler;
			delete pitchRecord;
			delete song;
		}

		bool SongControl::isRecordSampleVisible(int sampleIndex, int marigin) const
		{
			const IPitchSample* currSample = pitchRecord->getSample(sampleIndex);
			const IPitchSample* nextSample = pitchRecord->getSample(sampleIndex+1);
			const ITrack* currTrack = song->getSelectedTrack();

			if(!currSample || !nextSample)
				return false;

			return  currSample->getState() != IPitchSample::SAMPLE_END &&
					nextSample->getState() != IPitchSample::SAMPLE_START &&
					currTrack->isWithinNoteRange(currSample->getPitch(), marigin) &&
					currTrack->isWithinNoteRange(nextSample->getPitch(), marigin) &&
					currSample->getTimestamp() >= settings.viewedTime &&
					nextSample->getTimestamp() <= settings.viewedTime + settings.viewTimeRange;
		}

		bool SongControl::load(const char* filename)
		{
			loaded = false;
			rewind();
			song->clear();

			std::string filenameNoExt = filename;
			std::string ext = "";
			std::string path = "";

			size_t sep = filenameNoExt.find_last_of("\\/");
			if (sep != std::string::npos)
			{
				path = filenameNoExt.substr(0, sep + 1);
				filenameNoExt = filenameNoExt.substr(sep + 1, filenameNoExt.size() - sep - 1);
			}

			sep = filenameNoExt.find_last_of(".");
			if (sep != std::string::npos)
			{
				ext = filenameNoExt.substr(sep + 1, filenameNoExt.size() - sep - 1);
				filenameNoExt = filenameNoExt.substr(0, sep+1);
			}

            song->properties[SOS_SONG_PROP_PATH] = path;
			currentHandler->free();

			if(ext == "mid" || ext == "kar")
			{
				currentHandler = midiHandler;
                song->encoding = ISong::ANSI;
                song->properties[SOS_SONG_PROP_MIDIFILENAME] = filenameNoExt + ext;
                loaded = midiHandler->loadMusic();
			}
			else if(ext == "txt")
			{
				currentHandler = streamHandler;
                song->encoding = ISong::UTF8;
                song->properties[SOS_SONG_PROP_ULTRASTARTXTFILE] = filenameNoExt + ext;
                loaded = streamHandler->loadMusic();
			}
			else
			{
				currentHandler = streamHandler;
                song->encoding = ISong::UTF8;
                song->properties[SOS_SONG_PROP_MP3BACKGROUND] = filenameNoExt + ext;
                song->properties[SOS_SONG_PROP_ULTRASTARTXTFILE] = filenameNoExt + "txt";
                loaded = streamHandler->loadMusic();

                if(song->tracks.size() == 0)
                {
                    //if the file was loaded, but there's no track info, maybe there's a .kar or .mid file that we can use
                    if(song->tracks.size() == 0)
                    {
                        song->properties[SOS_SONG_PROP_MIDIFILENAME] = filenameNoExt + "kar";
                        midiHandler->loadMusic();
                    }
                    if(song->tracks.size() == 0)
                    {
                        song->properties[SOS_SONG_PROP_MIDIFILENAME] = filenameNoExt + "mid";
                        midiHandler->loadMusic();
                    }
                }
			}

			if(loaded)
            {
				setSelectedTrackIndex(settings.selectedTrackIndex);
				setKeyShift(0);
				setTempo(1.0);
                currentHandler->changeVolume();
			}

            return loaded;
		}

		void SongControl::start()
		{
			if(!playing && loaded)
			{
				if (settings.currTime >= song->getTotalTime() - settings.outputLatency ||
						timeBeyondSelection(settings.currTime))
					rewind();

				currentHandler->startPlaying();
				playing = true;
				lastClock = clock();
			}
		}

		void SongControl::stop()
		{
			currentHandler->stopPlaying();
			playing = false;
		}

		void SongControl::update ()
		{
			if(playing)
			{
				if(currentHandler->isPlaying())
					settings.currTime = currentHandler->getCurrTime();
				else
					settings.currTime += clock() - lastClock;

				currentHandler->updateTrackPlayedTime();

				copyRecord(audioAnalyzer->getPitchRecord(), settings.currTime);
				audioAnalyzer->getPitchRecord()->clear();

				if (settings.currTime >= song->getTotalTime() + settings.outputLatency ||
						(settings.selectionEnd > 0 && settings.currTime >= settings.selectionEnd))
				{
					stop();
					checkExcercise();
				}

				lastClock = clock();
			}
		}

		void SongControl::rewind()
		{
			pitchRecord->clear();
			sumAccuracy = 0;
			analyzed = false;

			if(settings.selectionEnd > 0)
			{
				settings.currTime = settings.selectionStart;
				currentHandler->rewind();
			}
			else
			{
				settings.currTime = 0;
				currentHandler->rewind();
			}
		}

		void SongControl::checkExcercise()
		{
			if(!loaded)
				return;

			averageAccuracy = sumAccuracy / pitchRecord->getCurrentSampleIndex();
			FILE_LOG(logDEBUG) << "Total Accuracy: " << averageAccuracy << ", Time Shift: %d" << settings.outputLatency;
		}

		bool SongControl::isLoaded() const
		{
			return loaded;
		}

		void SongControl::copyRecord(const IPitchRecord* record, long time)
		{
			if(!loaded || song->tracks.size() == 0)
				return;

			int currSample = record->getCurrentSampleIndex()-1;

			if(audioAnalyzer->getAmplitude() < audioAnalyzer->getVolumeThreshold())
				pitchRecord->markAsEnd();

			if(currSample < 0)
				return;

			Track* currentTrack = song->tracks[settings.selectedTrackIndex];
			float pitch = record->getSample(currSample)->getPitch();

			const Note* closestNote = NULL;
			float moddedClosest = 0;
			float accuracy = -1;

			for(int i = 0; i < currentTrack->getNoteCount(); i++)
			{
				const Note* currNote = currentTrack->notes[i];

				if(time < currNote->getStopTime())
				{
					if(settings.currTime < currNote->getStartTime())
					{
						if(!closestNote)
							pitchRecord->markAsEnd();
						break;
					}

					float moddedCurrent = fmod(pitch - currNote->getNotePitch(), 12);
					if(moddedCurrent > 6)
						moddedCurrent -= 12;
					else if(moddedCurrent < -6)
						moddedCurrent += 12;

					if(!closestNote ||	abs(moddedCurrent) < abs(moddedClosest) )
					{
						closestNote = currNote;
						moddedClosest = moddedCurrent;
					}
				}
			}

			if(closestNote)
			{
				pitch = closestNote->getNotePitch() + moddedClosest;
				accuracy = std::max(1.0f - std::abs(moddedClosest), 0.0f);
				lastSamplePitchShift = pitch - record->getSample(currSample)->getPitch();
				sumAccuracy += accuracy;
				pitchRecord->addSample(pitch, time, accuracy);
			}
		}

		int SongControl::getLastSamplePitchShift() const
		{
			return lastSamplePitchShift;
		}

		const IPitchRecord* SongControl::getRecord() const
		{
			return pitchRecord;
		}

		const ISong* SongControl::getSong() const
		{
			return song;
		}

		ISongSettings* SongControl::getSettings()
		{
			return this;
		}

		const ISongSettings* SongControl::getSettings() const
		{
			return this;
		}

		bool SongControl::isPlaying() const
		{
			return playing;
		}

		void SongControl::setMute(bool mute, int track)
		{
			currentHandler->setMute(mute, track);
		}

		void SongControl::setSolo(bool solo, int track)
		{
			currentHandler->setSolo(solo, track);
		}
	}
}
