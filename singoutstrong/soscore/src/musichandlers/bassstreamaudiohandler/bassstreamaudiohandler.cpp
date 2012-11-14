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
			moveTo(0);
		}

		void BassStreamAudioHandler::moveTo(long time)
		{
			BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, ((double)(time+ settings->getOutputLatency()))/1000), BASS_POS_BYTE);
		}

		void BassStreamAudioHandler::startPlaying()
		{
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
			float tempo = settings->getTempo() - 1.0;
			BOOL result = BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO, tempo*100.0);
			int err = BASS_ErrorGetCode();
			int t = 0;
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

		bool BassStreamAudioHandler::loadFile(const char *filename)
		{
			free();
			song->clear();

			UltraStarParser parser(settings, song, filename, properties);
			stream = BASS_StreamCreateFile(FALSE,properties["background"].c_str(),0,0,BASS_STREAM_DECODE);
			stream = BASS_FX_TempoCreate(stream, BASS_SAMPLE_LOOP|BASS_FX_FREESOURCE);
			BASS_ChannelFlags(stream, 0, BASS_SAMPLE_LOOP);

			song->songDuration = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE)) * 1000;
			song->name = properties["filename"];

			if(!properties["artist"].empty())
				song->description = properties["artist"];
			if(!properties["title"].empty())
			{
				if(!properties["artist"].empty())
					song->description += " - ";
				song->description += properties["title"];
			}

			return stream > 0;
		}

	}
}
