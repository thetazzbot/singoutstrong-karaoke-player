#include "pitchsample.h"

namespace SoS
{
	namespace Core
	{
		PitchSample::PitchSample() :
			pitch(0),
			accuracy(0),
			timestamp(0),
			state(IPitchSample::SAMPLE_END)
		{
		}

		float PitchSample::getPitch() const
		{
			return pitch;
		}

		float PitchSample::getAccuracy() const
		{
			return accuracy;
		}

		long PitchSample::getTimestamp() const
		{
			return timestamp;
		}

		IPitchSample::SampleState PitchSample::getState() const
		{
			return state;
		}
	}
}
