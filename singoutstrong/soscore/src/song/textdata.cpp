#include "textdata.h"

namespace SoS
{
	namespace Core
	{
		TextData::TextData() :
			time(0),
			lineNo(0),
			type(ITextData::GENERIC_TEXT)
		{
		}

		long TextData::getTime() const
		{
			return time;
		}

		const char* TextData::getText() const
		{
			return text.c_str();
		}

		int TextData::getLineNo() const
		{
			return lineNo;
		}

		ITextData::TextDataType TextData::getType() const
		{
			return type;
		}

		const ISongSettings* TextData::settings = NULL;
	}
}
