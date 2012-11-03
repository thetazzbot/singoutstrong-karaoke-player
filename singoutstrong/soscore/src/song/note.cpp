#include "note.h"

namespace SoS
{
	namespace Core
	{

		Note::Note() :
			startTime(0),
			stopTime(0),
			notePitch(0)
		{
		}

		long Note::getTimeLength() const
		{
			return (getStopTime() - getStartTime());
		}

		int Note::getNotePitch() const
		{
			return settings ? notePitch + settings->getKeyShift() : notePitch;
		}

		long Note::getStartTime() const
		{
			return startTime;
		}

		long Note::getStopTime() const
		{
			return stopTime;
		}

		const ISongSettings* Note::settings = NULL;
	}
}
