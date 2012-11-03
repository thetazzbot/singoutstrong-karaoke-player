#include "pitchrecord.h"

namespace SoS
{
	namespace Core
	{

		PitchRecord::PitchRecord()
		{
			clear();
		}

		void PitchRecord::addSample(float pitch)
		{
			addSample(pitch, clock());
		}

		void PitchRecord::addSample(float pitch, long time, float accuracy)
		{
			PitchSample sample;
			sample.pitch = pitch;
			sample.accuracy = accuracy;
			sample.timestamp = time;

			if(pitchSamples.size() == 0 || pitchSamples.back().state == IPitchSample::SAMPLE_END)
				sample.state = IPitchSample::SAMPLE_START;
			else
				sample.state = IPitchSample::SAMPLE_MIDDLE;

			pitchSamples.push_back(sample);
		}

		void PitchRecord::markAsEnd()
		{
			if(pitchSamples.size() > 0)
				pitchSamples.back().state = IPitchSample::SAMPLE_END;
		}

		const IPitchSample* PitchRecord::getSample(int index) const
		{
			if(index < 0 || index >= pitchSamples.size())
				return NULL;

			return &pitchSamples[index];
		}

		int PitchRecord::getCurrentSampleIndex() const
		{
			return pitchSamples.size();
		}

		void PitchRecord::clear()
		{
			pitchSamples.clear();
		}

		int PitchRecord::getStartIndex(long viewTime) const
		{
			PitchSample cmp;
			cmp.timestamp = viewTime;
			int index = lower_bound(pitchSamples.begin(), pitchSamples.end(), cmp, PitchSample::CompareTimestamp) - pitchSamples.begin();

			return index;
		}
	}
}
