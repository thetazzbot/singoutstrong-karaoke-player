#include "bassaudioinput.h"

namespace SoS
{
	namespace Core
	{

		BassAudioInput::BassAudioInput(IAudioAnalyzer* analyzer) :
			audioAnalyzer(analyzer)
		{
			currDevice = -1;
			deviceHandle = 0;
		}

		BassAudioInput::~BassAudioInput()
		{
			BASS_RecordFree();
		}

		void BassAudioInput::startRecording()
		{
			deviceHandle = BASS_RecordStart(AUDIO_SAMPLERATE, 1, BASS_SAMPLE_FLOAT, SoundInCallback, audioAnalyzer);
		}

		void BassAudioInput::stopRecording()
		{
			BASS_ChannelStop(deviceHandle);
		}

		int BassAudioInput::getAvailableInDevicesCount()
		{
			int inDeviceCount = 0;
			BASS_DEVICEINFO info;
			for (int i=0; BASS_RecordGetDeviceInfo(i, &info); i++)
				if (info.flags&BASS_DEVICE_ENABLED)
					inDeviceCount++; // count it

			return inDeviceCount;
		}

		AudioDeviceInfo BassAudioInput::getAvailableInDevice(int index)
		{
			AudioDeviceInfo info;

			BASS_DEVICEINFO bassInfo;
			if(BASS_RecordGetDeviceInfo(index, &bassInfo))
			{
				info.DeviceName = bassInfo.name;
				info.Id = index;
				return info;
			}

			info.DeviceName = "No device";
			info.Id = -1;
			return info;
		}

		bool BassAudioInput::setDevice(int deviceId)
		{
			BASS_RecordFree();
			deviceHandle = 0;
			FILE_LOG(logDEBUG) << "[RtAudioIO]: Closing stream succesful";

			if(BASS_RecordInit(deviceId))
			{
				if(BASS_RecordSetDevice(deviceId))
					startRecording();
				else
				{
					FILE_LOG(logDEBUG) << "[RtAudioIO]: Error setting recording device, code: " << BASS_ErrorGetCode();
				}
			}
			else
			{
				FILE_LOG(logDEBUG) << "[RtAudioIO]: Error initializing recording device, code: " << BASS_ErrorGetCode();
			}
		}

		AudioDeviceInfo BassAudioInput::getCurrentDevice()
		{
			AudioDeviceInfo info;

			if (currDevice >= 0)
			{
				BASS_DEVICEINFO bassInfo;
				BASS_RecordGetDeviceInfo(currDevice, &bassInfo);
				info.DeviceName = bassInfo.name;
				info.Id = currDevice;
			}
			else
			{
				info.DeviceName = "No device";
				info.Id = -1;
			}

			return info;
		}

		BOOL CALLBACK SoundInCallback( HRECORD handle, const void *buffer, DWORD length, void *user )
		{
			IAudioAnalyzer* analyzer = (IAudioAnalyzer*)user;

			if(analyzer != NULL)
			{
				AUDIO_DATA_TYPE* iData = (AUDIO_DATA_TYPE*)buffer;
				analyzer->processAudio(iData, length);
			}

			return TRUE;
		}
	}
}
