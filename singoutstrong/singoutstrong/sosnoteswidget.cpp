#include "sosnoteswidget.h"

namespace SoS
{
	namespace QtGui
	{

		SoSNotesWidget::SoSNotesWidget(QWidget *parent) :
			QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
			sosContext(NULL),
			pitchMultiplier(0.5),
			lineHeight(0)
		{
			setAutoFillBackground(false);
		}

		void SoSNotesWidget::mousePressEvent(QMouseEvent *event)
		{
			if (event->button() == Qt::LeftButton)
			{
				sosContext->SongControl->getSettings()->setSelectionEnd(-1);
				sosContext->SongControl->getSettings()->setSelectionStart(xToTime(event->pos().x()));
			}
			event->ignore();
		}

		void SoSNotesWidget::mouseMoveEvent(QMouseEvent *event)
		{
			if (event->buttons() & Qt::LeftButton)
			{
				long xTime = xToTime(event->pos().x());
				if(xTime < sosContext->SongControl->getSettings()->getSelectionStart())
					sosContext->SongControl->getSettings()->setSelectionStart(xTime);
				else
					sosContext->SongControl->getSettings()->setSelectionEnd(xTime);
				event->accept();
			}
		}

		void SoSNotesWidget::mouseReleaseEvent(QMouseEvent *event)
		{
			if (event->button() == Qt::LeftButton &&
					(sosContext->SongControl->getSettings()->getSelectionEnd() < 0 ||
					 sosContext->SongControl->getSettings()->getSelectionEnd() -
					 sosContext->SongControl->getSettings()->getSelectionStart() < 100))
			{
				sosContext->SongControl->getSettings()->setSelectionEnd(-1);
				sosContext->SongControl->getSettings()->setSelectionStart(-1);
				sosContext->SongControl->getSettings()->setCurrentTime(xToTime(event->pos().x()));
				event->accept();
			}
		}

		long SoSNotesWidget::xToTime(float x)
		{
			return (x + timeOffset) / widthMultiplier;
		}

		float SoSNotesWidget::timeToX(long time)
		{
			return time * widthMultiplier - timeOffset;
		}

		void SoSNotesWidget::paintEvent(QPaintEvent *event)
		{
			QPainter painter(this);
			painter.fillRect(event->rect(), painter.background());

			if(!song)
				return;

			track = song->getSelectedTrack();
			notesRange = track ? track->getTopNote() - track->getBottomNote() + TOTAL_MARIGINS + 1 : 16;
			drawNoteLines(event, &painter);

			if(!track)
				return;

			pitchMultiplier = height() / notesRange;
			widthMultiplier = (float)(width()) / settings->getViewTimeRange();
			timeOffset = settings->getViewedTime() * widthMultiplier;

			painter.setRenderHint(QPainter::Antialiasing);
			drawTrack(event, &painter);
			painter.setRenderHint(QPainter::Antialiasing, false);
			drawTimeLine(event, &painter);
			drawRecord(event, &painter);
			drawSelection(event, &painter);

			painter.end();
		}

		void SoSNotesWidget::drawSelection(QPaintEvent *event, QPainter *painter)
		{
			if(sosContext->SongControl->getSettings()->getSelectionEnd() > 0)
			{
				QRect selection = event->rect();
				selection.setX(timeToX(sosContext->SongControl->getSettings()->getSelectionStart()));
				selection.setRight(timeToX(sosContext->SongControl->getSettings()->getSelectionEnd()));

				painter->fillRect(selection, selectionColorVar);
			}
		}

		void SoSNotesWidget::drawNoteLines(QPaintEvent *event, QPainter *painter)
		{
			if(!sosContext->SongControl)
				return;

			if (notesRange != lineYs.size())
				lineYs.clear();

			for(int i = 0; i <= notesRange; i++)
			{
				if(lineYs.size() <= i)
				{
					lineYs.push_back(((float)(height() - 1) / notesRange) * i);

					if(lineYs.size() > 1)
						lineHeight = (lineYs[1] - lineYs[0]);
				}

				painter->drawLine(0, lineYs[i], event->rect().width(), lineYs[i]);
			}
		}

		void SoSNotesWidget::drawTrack(QPaintEvent *event, QPainter *painter)
		{
			long endview = sosContext->SongControl->getSettings()->getViewedTime() + sosContext->SongControl->getSettings()->getViewTimeRange();
			for(int i = track->getNoteIndexForViewTime(); i < track->getNoteCount(); i++)
			{
				const INote* note = track->getNote(i);

				if(note->getStartTime() > endview)
					continue;

				float noteStartPos = timeToX(note->getStartTime());
				float noteEndPos = timeToX(note->getStopTime());
				int currNoteLine = track->getTopNote() + NOTE_MARIGIN - note->getNotePitch();

				if(noteStartPos < width() && noteEndPos > 0 && currNoteLine < lineYs.size())
				{
					QRectF noteRect(noteStartPos, lineYs[currNoteLine],
									noteEndPos-noteStartPos, lineYs[currNoteLine+1] - lineYs[currNoteLine]);

					painter->setBrush(noteColorVar);
					painter->drawRoundedRect(noteRect, 10, noteRect.height());
				}
				else if(noteStartPos > width())
				{
					return;
				}
			}
		}

		void SoSNotesWidget::drawTimeLine(QPaintEvent *event, QPainter *painter)
		{
			float lineLocation = timeToX(settings->getCurrentTime());

			if(lineLocation >= 0 && lineLocation < width())
			{
				painter->drawLine(lineLocation, 0, lineLocation, height());
				int so = sosContext->SongControl->getRecord()->getCurrentSampleIndex();
				float currPitch = 0;
				float pitchDiff = 0;

				if(sosContext->SongControl->isPlaying() && so > 0 &&
						sosContext->SongControl->getRecord()->getSample(so-1)->getState() != IPitchSample::SAMPLE_END)
				{
					currPitch = sosContext->SongControl->getRecord()->getSample(so-1)->getPitch();
				}
				else
				{
					currPitch = sosContext->AudioAnalyzer->getPitch();

					if(currPitch > 0)
						currPitch += sosContext->SongControl->getLastSamplePitchShift();
				}

				if(currPitch > 0)
					currPitchY = (track->getTopNote() + NOTE_MARIGIN - currPitch) * pitchMultiplier - (indicatorVar.height() - lineHeight) / 2;

				if(currPitchY <= 0)
				{
					pitchDiff =  currPitch - track->getTopNote() - NOTE_MARIGIN;
					painter->drawImage(lineLocation, 0, currPitch > 0 ? indicatorHighVar : indicatorHighInactiveVar);
					//painter->drawText(t, QString().setNum(pitchDiff, 'g', 2));
				}
				else if (currPitchY >= height())
				{
					pitchDiff = currPitch - track->getBottomNote() + NOTE_MARIGIN;
					painter->drawImage(lineLocation, height() - indicatorLowVar.height(),
									   currPitch > 0 ? indicatorLowVar : indicatorLowInactiveVar);
				}
				else
				{
					painter->drawImage(lineLocation, currPitchY, currPitch > 0 ? indicatorVar : indicatorInactiveVar);
				}
			}
		}

		void SoSNotesWidget::drawRecord(QPaintEvent *event, QPainter *painter)
		{
			const IPitchRecord* pitchSamples = sosContext->SongControl->getRecord();
			int currSample = pitchSamples->getCurrentSampleIndex();
			long viewTime = sosContext->SongControl->getSettings()->getViewedTime();
			long endViewTime = viewTime + sosContext->SongControl->getSettings()->getViewTimeRange();

			if(currSample <= 0)
				return;

			for(int i = pitchSamples->getStartIndex(viewTime); i < currSample - 1 && pitchSamples->getSample(i)->getTimestamp() < endViewTime; i++)
			{
				if(sosContext->SongControl->isRecordSampleVisible(i, NOTE_MARIGIN))
				{
					float currSampleX = timeToX(pitchSamples->getSample(i)->getTimestamp()) - 1;
					float nextSampleX = timeToX(pitchSamples->getSample(i+1)->getTimestamp());
					float sampleY = (track->getTopNote() + NOTE_MARIGIN - pitchSamples->getSample(i)->getPitch()) * pitchMultiplier;
					float accuracy = pitchSamples->getSample(i)->getAccuracy();

					QBrush brush = recBadColorVar;
					if(accuracy > 0.50)
						brush = recPoorColorVar;
					if(accuracy > 0.65)
						brush = recOkColorVar;
					if(accuracy > 0.75)
						brush = recGoodColorVar;
					if(accuracy > 0.85)
						brush = recPerfectColorVar;

					painter->fillRect(QRect(currSampleX, sampleY, nextSampleX - currSampleX, lineYs[1] - lineYs[0]), brush);
				}
			}
		}

		void SoSNotesWidget::setSoSContext(SoSContext *context)
		{
			sosContext = context;
			settings = sosContext->SongControl->getSettings();
			song = sosContext->SongControl->getSong();
		}

		void SoSNotesWidget::setNoteColor(QBrush c)
		{
			noteColorVar = c;
		}

		void SoSNotesWidget::setSelectionColor(QBrush c)
		{
			selectionColorVar = c;
		}

		void SoSNotesWidget::setRecPerfectColor(QBrush c)
		{
			recPerfectColorVar = c;
		}

		void SoSNotesWidget::setRecGoodColor(QBrush c)
		{
			recGoodColorVar = c;
		}

		void SoSNotesWidget::setRecOkColor(QBrush c)
		{
			recOkColorVar = c;
		}

		void SoSNotesWidget::setRecPoorColor(QBrush c)
		{
			recPoorColorVar = c;
		}

		void SoSNotesWidget::setRecBadColor(QBrush c)
		{
			recBadColorVar = c;
		}

		void SoSNotesWidget::setIndicator(QImage i)
		{
			indicatorVar = i;
		}

		void SoSNotesWidget::setIndicatorInactive(QImage i)
		{
			indicatorInactiveVar = i;
		}

		void SoSNotesWidget::setIndicatorHigh(QImage i)
		{
			indicatorHighVar = i;
		}

		void SoSNotesWidget::setIndicatorHighInactive(QImage i)
		{
			indicatorHighInactiveVar = i;
		}

		void SoSNotesWidget::setIndicatorLow(QImage i)
		{
			indicatorLowVar = i;
		}

		void SoSNotesWidget::setIndicatorLowInactive(QImage i)
		{
			indicatorLowInactiveVar = i;
		}

		QBrush SoSNotesWidget::getNoteColor()
		{
			return noteColorVar;
		}

		QBrush SoSNotesWidget::getSelectionColor()
		{
			return selectionColorVar;
		}

		QBrush SoSNotesWidget::getRecPerfectColor()
		{
			return recPerfectColorVar;
		}

		QBrush SoSNotesWidget::getRecGoodColor()
		{
			return recGoodColorVar;
		}

		QBrush SoSNotesWidget::getRecOkColor()
		{
			return recOkColorVar;
		}

		QBrush SoSNotesWidget::getRecPoorColor()
		{
			return recPoorColorVar;
		}

		QBrush SoSNotesWidget::getRecBadColor()
		{
			return recBadColorVar;
		}

		QImage SoSNotesWidget::getIndicator()
		{
			return indicatorVar;
		}

		QImage SoSNotesWidget::getIndicatorInactive()
		{
			return indicatorInactiveVar;
		}

		QImage SoSNotesWidget::getIndicatorHigh()
		{
			return indicatorHighVar;
		}

		QImage SoSNotesWidget::getIndicatorHighInactive()
		{
			return indicatorHighInactiveVar;
		}

		QImage SoSNotesWidget::getIndicatorLow()
		{
			return indicatorLowVar;
		}

		QImage SoSNotesWidget::getIndicatorLowInactive()
		{
			return indicatorLowInactiveVar;
		}

	}
}
