#include "bassstreamaudiohandler.h"

namespace SoS
{
	namespace Core
	{

		BassStreamAudioHandler::BassStreamAudioHandler(Song* song, ISongSettings* settings) :
			song(song),
			settings(settings)
		{
			BASS_Init(-1,44100,0,0,NULL);
		}

		BassStreamAudioHandler::~BassStreamAudioHandler()
		{
			BASS_Free();
		}

		void BassStreamAudioHandler::rewind()
		{
			moveTo(settings->getCurrentTime() * settings->getTempo());
		}

		void BassStreamAudioHandler::moveTo(long time)
		{
			BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, ((double)(time+ settings->getOutputLatency()))/1000), BASS_POS_BYTE);
		}

		void BassStreamAudioHandler::startPlaying()
		{
			rewind();
			BASS_ChannelPlay(stream,FALSE);
		}

		void BassStreamAudioHandler::stopPlaying()
		{
			BASS_ChannelStop(stream);
		}

		bool BassStreamAudioHandler::isPlaying() const
		{
			return BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING;
		}

		long BassStreamAudioHandler::getCurrTime() const
		{
			return BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetPosition(stream, BASS_POS_BYTE)) * 1000 / settings->getTempo() - settings->getOutputLatency();
		}

		void BassStreamAudioHandler::setSolo(bool solo, int track)
		{
		}

		void BassStreamAudioHandler::setMute(bool mute, int track)
		{
		}

		void BassStreamAudioHandler::changeVolume()
		{
			BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, (float)settings->getVolume() / 255);
		}

		void BassStreamAudioHandler::changeKey()
		{
			BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO_PITCH, (float)settings->getKeyShift());
		}

		void BassStreamAudioHandler::changeTempo()
		{
			BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO, (settings->getTempo() - 1.0) *100.0);
		}

		void BassStreamAudioHandler::updateTrackPlayedTime()
		{
		}

		void BassStreamAudioHandler::free()
		{
			if(stream > 0)
			{
				BASS_StreamFree(stream);
				stream = 0;
			}
		}

		bool BassStreamAudioHandler::loadMusic()
		{
			free();

			UltraStarParser parser(settings, song);
            stream = BASS_StreamCreateFile(FALSE,(song->properties[SOS_SONG_PROP_PATH] + song->properties[SOS_SONG_PROP_MP3BACKGROUND]).c_str(),0,0,BASS_STREAM_DECODE);
			stream = BASS_FX_TempoCreate(stream, BASS_SAMPLE_LOOP|BASS_FX_FREESOURCE);
			BASS_ChannelFlags(stream, 0, BASS_SAMPLE_LOOP);

			song->songDuration = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)) * 1000;

            if(!song->properties[SOS_SONG_PROP_ARTIST].empty())
                song->properties[SOS_SONG_PROP_DESCRIPTION] = song->properties[SOS_SONG_PROP_ARTIST];
            if(!song->properties[SOS_SONG_PROP_TITLE].empty())
			{
                if(!song->properties[SOS_SONG_PROP_ARTIST].empty())
                    song->properties[SOS_SONG_PROP_DESCRIPTION] += " - ";
                song->properties[SOS_SONG_PROP_DESCRIPTION] += song->properties[SOS_SONG_PROP_TITLE];
			}

			return stream > 0;
		}

	}
}
