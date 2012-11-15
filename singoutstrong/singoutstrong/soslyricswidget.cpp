#include "soslyricswidget.h"

namespace SoS
{
	namespace QtGui
	{

		SoSLyricsWidget::SoSLyricsWidget(QWidget *parent) :
			QWidget(parent),
			oldStart(0),
			oldEnd(0),
			sungText(QColor(255, 0, 0))
		{
			while(lines.size() < 4)
				lines.push_back(QStringList());
		}

		QColor SoSLyricsWidget::getSungTextColor()
		{
			return sungText.color();
		}

		void SoSLyricsWidget::setSungTextColor(QColor value)
		{
			sungText = value;
		}

		void SoSLyricsWidget::setSoSContext(const SoSContext *context)
		{
			songControl = context->SongControl;
			song = songControl->getSong();
			settings = songControl->getSettings();
		}

		void SoSLyricsWidget::resizeEvent(QResizeEvent *event)
		{
			setupFont();
		}

		void SoSLyricsWidget::paintEvent(QPaintEvent *event)
		{
			QStylePainter painter(this);

			drawBackground(event, &painter);
			drawLyrics(event, &painter);

			painter.end();
		}

		void SoSLyricsWidget::drawBackground(QPaintEvent *event, QPainter *painter)
		{
			painter->fillRect(event->rect(), painter->background());
		}

		void SoSLyricsWidget::drawLyrics(QPaintEvent *event, QPainter *painter)
		{
			for (int x = 0; x < song->getTracksCount(); x++)
			{
				const ITrack* track = song->getTrack(x);

				if(track->hasLyrics())
				{
					int start, end;
					track->getLineIndicesForTime(start, end);

					if(oldStart != start || oldEnd != end)
					{
						clearLines();
						int lowestLine = lines.size();
						for(int i = start; i < end; i++)
						{
							const ITextData* text = track->getTextData(i);
							QString lyric = song->getEncoding() == ISong::ANSI ?
										QString::fromLocal8Bit(text->getText()) :
										QString::fromUtf8(text->getText());
							lyric = lyric.remove('\\').remove('/').remove('\r').remove('\n');
							int currLine = text->getLineNo() % lines.size();
							lines[currLine].append(lyric);

							if(currLine < lowestLine)
							{
								lowestLine = currLine;
								if(lines[currLine].size() == 1)
									linesTextIndex = i;
							}
						}

						oldStart = start;
						oldEnd = end;
					}

					QFontMetrics fMetrics = painter->fontMetrics();
					int currLineYPos = fMetrics.height();
					int textIndex = linesTextIndex;

					for(int i = 0; i < lines.size(); i++)
					{
						int currLineXPos = (width() - fMetrics.width(lines[i].join(""))) / 2;
						for(int j = 0; j < lines[i].size(); j++)
						{
							if(track->getTextData(textIndex)->getTime() < settings->getCurrentTime())
								painter->setPen(sungText);
							else
								painter->setPen(palette().text().color());

							painter->drawText(QPoint(currLineXPos, currLineYPos), lines[i][j]);
							currLineXPos += fMetrics.width(lines[i][j]);

							textIndex = ++textIndex < end ? textIndex : start;
						}
						currLineYPos += fMetrics.height();
					}

					break;
				}
			}
		}

		void SoSLyricsWidget::setLineCount(int count)
		{
			lines.clear();
			while(lines.size() < count)
				lines.push_back(QStringList());

			setupFont();
		}

		void SoSLyricsWidget::setupFont()
		{
			int longestLine = 0;
			for(int i = 0; i < lines.size(); i++)
				longestLine = lines[i].join("").size() > lines[longestLine].join("").size() ? i : longestLine;

			QFont font = this->font();
			font.setPointSize(5);
			QFontMetrics fMetrics(font);
			while (//fMetrics.width(lines[longestLine].join("")) < width() - 40 &&
				   fMetrics.lineSpacing() < (height()-10) / lines.size())
			{
				font.setPointSize(font.pointSize() + 1);
				fMetrics = QFontMetrics(font);
			}

			setFont(font);
		}

		void SoSLyricsWidget::clearLines()
		{
			for(int i = 0; i < lines.size(); i++)
			{
				lines[i].clear();
			}
		}

	}
}
