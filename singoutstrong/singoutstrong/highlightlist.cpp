#include "highlightlist.h"

namespace SoS
{
	namespace QtGui
	{

		HighlightList::HighlightList(QWidget *parent) :
			QListWidget(parent),
			highlightedItemColorVar(QColor(0, 0, 255)),
			lastHighlightedItem(-1)
		{
		}

		QColor HighlightList::getHighlightedItemColor()
		{
			return highlightedItemColorVar;
		}

		void HighlightList::setHighlightedItemColor(QColor color)
		{
			highlightedItemColorVar = color;
			setHighlightedItem(lastHighlightedItem);
		}

		QString HighlightList::getHighlightedItemFont()
		{
			return highlightedItemFontVar.toString();
		}

		void HighlightList::setHighlightedItemFont(QString f)
		{
			highlightedItemFontVar.fromString(f);
			setHighlightedItem(lastHighlightedItem);
		}

		int HighlightList::getLastHighlightedItem()
		{
			return lastHighlightedItem;
		}

		void HighlightList::setLastHighlightedItem(int index)
		{
			lastHighlightedItem = index < 0 ? 0 : index >= count() ? count()-1 : index;
		}

		int HighlightList::getHighlightedItem()
		{
			for(int i = 0; i < count(); i++)
				if(item(i)->textColor() == highlightedItemColorVar)
					return i;

			return -1;
		}

		void HighlightList::setHighlightedItem(int index)
		{
			if(index >= count() || index < 0)
				return;

			QListWidgetItem* it = NULL;
			for(int i = 0; i < count(); i++)
			{
				it = item(i);
				item(i)->setTextColor(palette().text().color());
				item(i)->setFont(font());
			}

			it = item(index);
			QColor c = it->textColor();
			item(index)->setTextColor(highlightedItemColorVar);
			item(index)->setFont(highlightedItemFontVar);
			c = it->textColor();
			lastHighlightedItem = index;
			//this->refresh();
		}

	}
}
