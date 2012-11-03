#include "aubioanalyzer.h"

namespace SoS
{
	namespace Core
	{

		AubioAnalyzer::AubioAnalyzer() :
			hInstLibrary(NULL),
			NewAubioPitchdetection(NULL),
			AubioPitchdetection(NULL),
			NewFvec(NULL),
			DelAubioPitchdetection(NULL),
			DelFvec(NULL),
			AubioCleanup(NULL),
			dllLoaded(false),

			//aubio stuff
			vector_size(1024),				/* window size */
			hop_s(vector_size),							/* hop size */
			samplerate(AUDIO_SAMPLERATE),		/* samplerate */
			channels(1),						/* number of channel */
			input_vec(NULL),
			pitch_output(NULL),

			currentChunk(0),
			chunkCount(BUFFER_SIZE / AUDIO_SAMPLES),

			detectionMode(aubio_pitchm_cent),				//change to aubio_pitchm_midi to get frequency as midi notes
			detectionType(aubio_pitch_yinfft),
			volumeThreshold(0.6),
			newVectorSize(vector_size),
			typeChanged(false),

			pitchRecord(new PitchRecord()),
			pitch(0),
			amplitude(0)
		{
			for(int i = 0; i < BUFFER_SIZE; i++)
				samplesBuffer[i] = 0;

			InitAubioDll();
		}

		void AubioAnalyzer::InitAubioDll()
		{
			hInstLibrary = LoadLibrary(L"libaubio-2.dll");

			if (hInstLibrary)
			{
				NewAubioPitchdetection = (NewAubioPitchdetectionFunc)GetProcAddress(hInstLibrary, "new_aubio_pitchdetection");
				AubioPitchdetection = (AubioPitchdetectionFunc)GetProcAddress(hInstLibrary, "aubio_pitchdetection");
				NewFvec = (NewFvecFunc)GetProcAddress(hInstLibrary, "new_fvec");
				DelAubioPitchdetection = (DelAubioPitchdetectionFunc)GetProcAddress(hInstLibrary, "del_aubio_pitchdetection");
				DelFvec = (DelFvecFunc)GetProcAddress(hInstLibrary, "del_fvec");
				AubioCleanup = (AubioCleanupFunc)GetProcAddress(hInstLibrary, "aubio_cleanup");
			}

			dllLoaded = hInstLibrary && NewAubioPitchdetection && AubioPitchdetection && NewFvec &&
					DelAubioPitchdetection && DelFvec && AubioCleanup;
		}

		//--------------------------------------------------------------

		void AubioAnalyzer::setup()
		{
			if(dllLoaded)
			{
				if(vector_size != newVectorSize || typeChanged)
				{
					vector_size = newVectorSize;
					hop_s = vector_size;

					if(input_vec)
						DelFvec(input_vec);

					if(pitch_output)
						DelAubioPitchdetection(pitch_output);
					input_vec = NULL;
					pitch_output = NULL;
					typeChanged = false;
				}

				//setup aubio buffer and pitch detection
				if(input_vec == NULL)
					input_vec  = NewFvec (vector_size, channels);

				if(pitch_output == NULL)
					pitch_output = NewAubioPitchdetection(vector_size, hop_s, channels, samplerate, detectionType, detectionMode);
			}
		}

		//--------------------------------------------------------------
		AubioAnalyzer::~AubioAnalyzer()
		{
			if(dllLoaded)
			{
				FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Cleaning up aibio";
				if(pitch_output)
				{
					DelAubioPitchdetection(pitch_output);
					FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Delete pitch detection success";
				}
				if(input_vec)
				{
					DelFvec(input_vec);
					FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Delete fvec success";
				}

				AubioCleanup();
				FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Aubio cleanup success";
			}

			if(hInstLibrary)
			{
				FreeLibrary(hInstLibrary);
				FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Free aubio libreary success";
			}

			if(pitchRecord)
			{
				delete pitchRecord;
				FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Delete pitch record success";
			}

			FILE_LOG(logDEBUG) << "[AubioAnalyzer]: Analyzer release success";
		}

		//--------------------------------------------------------------
		void AubioAnalyzer::processAudio(AUDIO_DATA_TYPE* buffer, int bufferSize)
		{
			if(!dllLoaded)
				return;

			setup();

			float rmsAmplitude  = 0;
			int chunkIndex = currentChunk * AUDIO_SAMPLES;

			for (int i = 0; i < bufferSize; i++)
			{
				//calculate the root mean square amplitude
				rmsAmplitude += sqrt(buffer[i]*buffer[i]);
				samplesBuffer[chunkIndex + i] = buffer[i];
			}

			currentChunk++;
			if(currentChunk >= chunkCount)
				currentChunk = 0;

			copyToFVec(input_vec, vector_size);

			//now we need to get the average
			rmsAmplitude /= bufferSize;
			amplitude = rmsAmplitude;

			//don't update the pitch if the sound is very quiet
			if( amplitude > volumeThreshold && input_vec != NULL && pitch_output != NULL)
			{
				//finally get the pitch of the sound
				pitch = AubioPitchdetection(pitch_output, input_vec);// - octaveShift * 12;

				if(pitch == pitch && pitch > 0 && pitch < FLT_MAX && pitch > FLT_MIN)
				{
					pitchRecord->addSample(pitch);
				}
				else
				{
					pitchRecord->markAsEnd();
				}
			}
			else
			{
				pitch = 0;
				pitchRecord->markAsEnd();
			}
		}

		void AubioAnalyzer::copyToFVec(fvec_t * fvec, int size)
		{
			int endIndex = currentChunk * AUDIO_SAMPLES;
			int currentIndex = endIndex - size;

			if(currentIndex < 0)
				currentIndex += BUFFER_SIZE;

			for(int vecIndex = 0; vecIndex < size; vecIndex++)
			{
				if(currentIndex >= BUFFER_SIZE)
					currentIndex = 0;

				fvec->data[0][vecIndex] = samplesBuffer[currentIndex];
				currentIndex++;
			}
		}

		float AubioAnalyzer::getPitch() const
		{
			return pitch;
		}

		float AubioAnalyzer::getAmplitude() const
		{
			return amplitude;
		}

		float AubioAnalyzer::getVolumeThreshold() const
		{
			return volumeThreshold;
		}

		void AubioAnalyzer::setVolumeThreshold(float threshold)
		{
			volumeThreshold = threshold;
		}

		int AubioAnalyzer::getSamplesArraySize() const
		{
			return vector_size;
		}

		void AubioAnalyzer::setSamplesArraySize(int size)
		{
			newVectorSize = size;
		}

		IPitchRecord* AubioAnalyzer::getPitchRecord()
		{
			return pitchRecord;
		}

		const IPitchRecord* AubioAnalyzer::getPitchRecord() const
		{
			return pitchRecord;
		}

	}
}
