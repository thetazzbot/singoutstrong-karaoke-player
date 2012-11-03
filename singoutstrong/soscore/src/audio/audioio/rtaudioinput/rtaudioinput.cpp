#include "rtaudioinput.h"

namespace SoS
{
	namespace Core
	{

		RtAudioInput::RtAudioInput(IAudioAnalyzer *analyzer) :
			audioAnalyzer(analyzer)
		{
			parameters.deviceId = 0;
			parameters.nChannels = 0;
			parameters.firstChannel = 0;
		}

		RtAudioInput::~RtAudioInput()
		{
			if (rtAudio.isStreamOpen())
			{
				rtAudio.closeStream();
				FILE_LOG(logDEBUG) << "[RtAudioIO]: Closing stream succesful";
			}
		}

		void RtAudioInput::startRecording()
		{
			rtAudio.startStream();
		}

		void RtAudioInput::stopRecording()
		{
			rtAudio.stopStream();
		}

		int RtAudioInput::getAvailableInDevicesCount()
		{
			int inDeviceCount = 0;
			for(int i = 0; i < rtAudio.getDeviceCount(); i++)
			{
				if(rtAudio.getDeviceInfo(i).inputChannels > 0)
					inDeviceCount++;
			}

			return inDeviceCount;
		}

		AudioDeviceInfo RtAudioInput::getAvailableInDevice(int index)
		{
			unsigned int inDeviceInd = 0;
			AudioDeviceInfo info;

			for(unsigned int i = 0; i < rtAudio.getDeviceCount(); i++)
			{
				RtAudio::DeviceInfo rtInfo = rtAudio.getDeviceInfo(i);
				if(rtInfo.inputChannels > 0 && index == inDeviceInd++)
				{
					info.DeviceName = rtInfo.name.c_str();
					info.Id = i;
					return info;
				}
			}

			info.DeviceName = "No device";
			info.Id = -1;
			return info;
		}

		bool RtAudioInput::setDevice(int deviceId)
		{
			if (rtAudio.isStreamOpen())
			{
				rtAudio.closeStream();
				FILE_LOG(logDEBUG) << "[RtAudioIO]: Closing stream succesful";
			}
			if(deviceId < 0)
				return false;

			parameters.deviceId = deviceId;
			parameters.nChannels = 1;
			parameters.firstChannel = 0;
			unsigned int sampleRate = AUDIO_SAMPLERATE;
			unsigned int bufferFrames = AUDIO_SAMPLES; // 256 sample frames
			try
			{
				FILE_LOG(logDEBUG) << L"[RtAudioIO]: Opening device: " << parameters.deviceId;
				rtAudio.openStream( NULL, &parameters, RT_AUDIO_FORMAT, sampleRate, &bufferFrames, &SoundInCallback, audioAnalyzer );
				rtAudio.startStream();
			}
			catch ( RtError &error )
			{
				error.printMessage();
				return false;
			}

			return true;
		}

		AudioDeviceInfo RtAudioInput::getCurrentDevice()
		{
			AudioDeviceInfo info;

			if (rtAudio.isStreamOpen())
			{
				info.DeviceName = rtAudio.getDeviceInfo(parameters.deviceId).name.c_str();
				info.Id = parameters.deviceId;
			}
			else
			{
				info.DeviceName = "No device";
				info.Id = -1;
			}

			return info;
		}

		int SoundInCallback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
							 double streamTime, RtAudioStreamStatus status, void *data )
		{
			if(status)
				FILE_LOG(logWARNING) << "[RtAudioIO]: Stream overflow detected!";

			IAudioAnalyzer* analyzer = (IAudioAnalyzer*)data;

			if(analyzer != NULL)
			{
				AUDIO_DATA_TYPE* iData = (AUDIO_DATA_TYPE*)inputBuffer;
				analyzer->processAudio(iData, nBufferFrames);
			}

			return 0;
		}
	}
}
