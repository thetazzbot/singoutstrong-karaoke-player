#include "track.h"

namespace SoS
{
	namespace Core
	{
		const ISongSettings* Track::settings = NULL;

		Track::Track() :
			bottomNote(255),
			topNote(0),
			volume(0)
		{
		}
		
		Track::~Track()
		{
			clear();
		}

		void Track::clear()
		{
			for(int i = 0; i < notes.size(); i++)
				delete notes[i];

			for(int i = 0; i < TEXT_DATA_TYPES_COUNT; i++)
			{
				for(int j = 0; j < textData[i].size(); j++)
					delete textData[i][j];

				textData[i].clear();
			}

			notes.clear();
		}

		INote* Track::getNote(int index)
		{
			if(index >= 0 && index < notes.size())
				return notes[index];

			return NULL;
		}

		const INote* Track::getNote(int index) const
		{
			if(index >= 0 && index < notes.size())
				return notes[index];

			return NULL;
		}

		int Track::getNoteIndexForViewTime() const
		{
			//int index = notes.rend() - lower_bound(notes.rbegin(), notes.rend(), (Note*)NULL, Note::CmpFirstAfterViewTime);
			return 0;
		}

		int Track::getAllTextDataCount() const
		{
			int count = 0;
			for (int i = 0; i < TEXT_DATA_TYPES_COUNT; i++)
			{
				i += textData[i].size();
			}

			return count;
		}

		int Track::getTopNote() const
		{
			return settings ? topNote + settings->getKeyShift() : topNote;
		}

		int Track::getBottomNote() const
		{
			return settings ? bottomNote + settings->getKeyShift() : bottomNote;
		}

		const char* Track::getName() const
		{
			return name.c_str();
		}

		int Track::getNoteCount() const
		{
			return notes.size();
		}

		unsigned char Track::getCurrVolume() const
		{
			return volume;
		}

		ITextData* Track::getTextData(int index, ITextData::TextDataType type)
		{
			if(index >= 0 && index < textData[type].size())
				return textData[type][index];

			return NULL;
		}

		const ITextData* Track::getTextData(int index, ITextData::TextDataType type) const
		{
			if(index >= 0 && index < textData[type].size())
				return textData[type][index];

			return NULL;
		}

		int Track::getTextDataCount(ITextData::TextDataType type) const
		{
			return textData[type].size();
		}

		bool Track::hasLyrics() const
		{
			return textData[ITextData::LYRIC_TEXT].size() > 0;
		}

		bool Track::isWithinNoteRange(float pitch, int marigin) const
		{
			return getBottomNote() - marigin <= pitch && getTopNote() + marigin >= pitch;
		}

		void Track::getLineIndicesForTime(int& start, int& end) const
		{
			if (settings->getTextGroupBy() <= 0)
				return;

			unsigned long time_length = 5000;
			start = 0;
			end = textData[ITextData::LYRIC_TEXT].size() - 1;

			//Fast search to an index reasonably close to current time, but before it
			start = lower_bound(textData[ITextData::LYRIC_TEXT].begin(),
								textData[ITextData::LYRIC_TEXT].end(),
								(TextData*)NULL,
								TextData::CmpFirstAfterCurrTime) - textData[ITextData::LYRIC_TEXT].begin() -1;

			if(start < 0)
				start = 0;

			//If we reached the end of text data, exit
			if(start >= textData[ITextData::LYRIC_TEXT].size() -1 &&
					textData[ITextData::LYRIC_TEXT][start]->getTime() < settings->getCurrentTime() - time_length)
			{
				end = start;
				return;
			}

			//Rewind to the beginning of the line group
			while(start > 0 &&
				  !(textData[ITextData::LYRIC_TEXT][start-1]->lineNo % settings->getTextGroupBy() == settings->getTextGroupBy()-1 &&
					textData[ITextData::LYRIC_TEXT][start]->lineNo % settings->getTextGroupBy() == 0 &&
					textData[ITextData::LYRIC_TEXT][start-1]->lineNo != textData[ITextData::LYRIC_TEXT][start]->lineNo))
				start--;

			int startLine = textData[ITextData::LYRIC_TEXT][start]->lineNo;
			//pretend to start from the previous line, so the first line gets processed
			int currLine = startLine-1;
			end = start;

			//Move the end index forward, until the end of text data is reached
			//or until the amount of lines, given in lineCount is retrieved
			while(end < textData[ITextData::LYRIC_TEXT].size() &&
				  textData[ITextData::LYRIC_TEXT][end]->lineNo < startLine + settings->getTextLineCount())
			{
				//If we reached a new line
				if(textData[ITextData::LYRIC_TEXT][end]->lineNo > currLine)
				{
					//If the time distance between the end of the last line,
					//and the beginning of this line is greater then time_length
					if(end == 0 || textData[ITextData::LYRIC_TEXT][end]->getTime() - textData[ITextData::LYRIC_TEXT][end-1]->getTime() > time_length)
					{
						//if the last line is further from current time then time_length
						if(end > 0 && textData[ITextData::LYRIC_TEXT][end-1]->getTime() < settings->getCurrentTime() - time_length)
						{
							//disregard the last line
							start = end;
						}
						//and if this line is further from current time then the time_length
						if(textData[ITextData::LYRIC_TEXT][end]->getTime() > settings->getCurrentTime() + time_length)
						{
							//exit, and disregard what follows as well
							return;
						}
					}
					currLine++;
				}
				end++;
			}
		}
	}
}
