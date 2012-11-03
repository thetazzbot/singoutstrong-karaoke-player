#include "sosdevice.h"

namespace SoS
{
	namespace Core
	{

		SoSDevice::SoSDevice() :
			_audioAnalyzer(new AudioAnalyzer()),
			_audioInput(new AudioInput(_audioAnalyzer)),
			_songControl(new SongControl(_audioAnalyzer))
		{
			Output2FILE::Stream() = fopen("sos.log", "w");
		}

		SoSDevice::~SoSDevice()
		{
			delete _audioInput;
			delete _audioAnalyzer;
			delete _songControl;
		}

		IAudioAnalyzer* SoSDevice::getAudioAnalyzer()
		{
			return _audioAnalyzer;
		}

		IAudioInput* SoSDevice::getAudioInput()
		{
			return _audioInput;
		}
		ISongControl* SoSDevice::getSongControl()
		{
			return _songControl;
		}

		const IAudioAnalyzer* SoSDevice::getAudioAnalyzer() const
		{
			return _audioAnalyzer;
		}

		const IAudioInput* SoSDevice::getAudioInput() const
		{
			return _audioInput;
		}

		const ISongControl* SoSDevice::getSongControl() const
		{
			return _songControl;
		}

		void SoSDevice::release()
		{
			delete this;
		}
	}
}
