#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace SoS
{
	namespace QtGui
	{

		void MainWindow::toggleSongPlay()
		{
			if(sosContext->SongControl->isPlaying())
				sosContext->SongControl->stop();
			else
			{
#ifdef DEBUG
				lowestFPS = 100;
#endif
				sosContext->SongControl->start();
			}
		}

		bool MainWindow::eventFilter(QObject *target, QEvent *event)
		{
			switch(event->type())
			{
			case QEvent::Wheel:
				if(target == &songWindow)
				{
					QWheelEvent* wEvent = (QWheelEvent*)event;

					long timeRange = settings->getViewTimeRange() - wEvent->delta();
					timeRange = timeRange < 1000 ? 1000 : timeRange > 10000 ? 10000 : timeRange;
					settings->setViewTimeRange(timeRange);
					generalSettings.refresh();
					return true;
				}
				break;
			case QEvent::KeyPress:
				keyPressEvent((QKeyEvent*)event);
				break;
			case QEvent::ApplicationActivate:
				bringToTop();
				return true;
			case QEvent::Hide:
				if(target == &songWindow) ui->songCheckbox->setChecked(false);
				else if(target == & playlist) ui->playlistCheckbox->setChecked(false);
				else if(target == & outputSettings) ui->outputCheckbox->setChecked(false);
				else if(target == & generalSettings) ui->settingsCheckbox->setChecked(false);
				else if(target == & tutorial) ui->tutorialCheckbox->setChecked(false);
				else if(target == & songSearch) ui->songSearchCheckbox->setChecked(false);
				break;
			case QEvent::Show:
				if(target == &songWindow) ui->songCheckbox->setChecked(true);
				else if(target == &playlist) ui->playlistCheckbox->setChecked(true);
				else if(target == &outputSettings) ui->outputCheckbox->setChecked(true);
				else if(target == &generalSettings) ui->settingsCheckbox->setChecked(true);
				else if(target == & tutorial) ui->tutorialCheckbox->setChecked(true);
				else if(target == & songSearch) ui->songSearchCheckbox->setChecked(true);

				if(target == &songWindow || target == &playlist || target == &outputSettings ||
						target == &songSearch || target == &generalSettings)
					((QWidget*)target)->setFocus();

				break;
			default:
				return false;
			}

			return false;
		}

		void MainWindow::timerEvent(QTimerEvent *event)
		{
			if(event->timerId() == timer.timerId())
			{
				sosContext->SongControl->update();

				long currTime = settings->getCurrentTime();
				long totalTime = sosContext->SongControl->getSong()->getTotalTime();
				ui->currTimeLabel->setText(QString("%1:%2")
										   .arg(currTime/60000)
										   .arg(currTime/1000%60, 2, 10, QChar('0')));

				ui->totalTimeLabel->setText(QString("%1:%2")
											.arg(totalTime/60000)
											.arg(totalTime/1000%60, 2, 10, QChar('0')));


				int pageLength = settings->getViewTimeRange();
				int viewTime = currTime - pageLength / 2;
				viewTime = viewTime < 0 ?
							0 : viewTime > totalTime - pageLength ?
								totalTime - pageLength : viewTime;

				if(!detachViewTime && !ui->viewTimeSlider->isSliderDown())
				{
					ui->viewTimeSlider->setSliderPosition(viewTime*100/(totalTime-pageLength));
					settings->setViewedTime(viewTime);
				}

				songWindow.update();
				outputSettings.updateVolumes();

#ifdef DEBUG
				QString debugText = "";
				long ct = clock();

				if(ct - elapsed > 0)
				{
					fps.push_back(1000 / ((float)(ct-elapsed)));

					if(fps.size() > 50)
						fps.erase(fps.begin());

					float av = 0;
					for(int i = 0; i < fps.size(); i++)
						av += fps[i];

					av /= fps.size();
					lowestFPS = av < lowestFPS ? av : lowestFPS;

					debugText.append(QString("FPS: %1\n").arg(av));
				}

				elapsed = ct;
				ui->label->setText(debugText);
#endif
			}
			else
			{
				QWidget::timerEvent(event);
			}
		}

		void MainWindow::closeEvent(QCloseEvent *event)
		{
			saveSettings();
			QMainWindow::closeEvent(event);
		}

		void MainWindow::changeEvent(QEvent *e)
		{
			if(e->type() == QEvent::ActivationChange && isActiveWindow())
			{
				bringToTop();
			}
			if(e->type() == QEvent::WindowStateChange)
			{
				if(isMinimized())
				{
					playlist.hide();
					songWindow.hide();
					songSearch.hide();
					outputSettings.hide();
					generalSettings.hide();
				}
				else
				{
					playlist.show();
					songWindow.show();
					outputSettings.show();
					generalSettings.show();
					songSearch.show();
				}
			}

			QMainWindow::changeEvent(e);
		}

		void MainWindow::keyPressEvent(QKeyEvent *event)
		{
			switch(event->key())
			{
			case Qt::Key_Control:
				detachViewTime = true;
				break;
			case Qt::Key_Space:
				toggleSongPlay();
				break;
			case Qt::Key_Escape:
				songWindow.showNormal();
				break;
			}
			event->accept();
		}

		void MainWindow::keyReleaseEvent(QKeyEvent *event)
		{
			if(event->key() == Qt::Key_Control)
			{
				detachViewTime = false;
			}
		}

		void MainWindow::bringToTop()
		{
			raise();
			outputSettings.raise();
			playlist.raise();
			generalSettings.raise();
			songWindow.raise();
			songSearch.raise();
			tutorial.raise();
		}
	}
}
