#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace SoS
{
	namespace QtGui
	{

		void MainWindow::updateSong()
		{
			QString description = "";
			QString title = "";
			const ISong* song = sosContext->SongControl->getSong();
			if(sosContext->SongControl->isLoaded())
			{
                title = QString::fromLocal8Bit(song->getProperty(SOS_SONG_PROP_MP3BACKGROUND));
                if(title.isEmpty()) title = QString::fromLocal8Bit(song->getProperty(SOS_SONG_PROP_MIDIFILENAME));

				if(song->getEncoding() == ISong::ANSI)
                    description = QString::fromLocal8Bit(song->getProperty(SOS_SONG_PROP_DESCRIPTION)).replace("\n", "<br />");
				else
                    description = QString::fromUtf8(song->getProperty(SOS_SONG_PROP_DESCRIPTION));
			}

			ui->descriptioneLabel->setText(description.length() > 55 ? description.left(52) + "..." : description);
			ui->descriptioneLabel->setToolTip(description);
			ui->songTitleLabel->setText(title);
			ui->viewTimeSlider->setSliderPosition(0);
			outputSettings.updateSettings();
		}

		void MainWindow::on_playButton_clicked()
		{
#ifdef DEBUG
			lowestFPS = 100;
#endif
			sosContext->SongControl->start();
		}

		void MainWindow::on_stopButton_clicked()
		{
			sosContext->SongControl->stop();
			sosContext->SongControl->rewind();
			settings->setViewedTime(settings->getCurrentTime() < settings->getViewTimeRange() / 2 ? 0 :
																									   settings->getCurrentTime() - settings->getViewTimeRange() / 2);
		}

		void MainWindow::on_pauseButton_clicked()
		{
			sosContext->SongControl->stop();
		}

		void MainWindow::on_rewindButton_clicked()
		{
			playlist.loadPrevSong();
		}

		void MainWindow::on_fforwardButton_clicked()
		{
			playlist.loadNextSong();
		}

		void MainWindow::on_viewTimeSlider_sliderMoved(int position)
		{
			settings->setViewedTime((sosContext->SongControl->getSong()->getTotalTime() - settings->getViewTimeRange()) * position / 100);
		}


		void MainWindow::on_viewTimeSlider_valueChanged(int value)
		{
			settings->setViewedTime((sosContext->SongControl->getSong()->getTotalTime() - settings->getViewTimeRange()) * value / 100);

			if(!detachViewTime)
			{
				settings->setCurrentTime(settings->getViewedTime() + settings->getViewTimeRange() / 2);
			}
		}

		void MainWindow::setSkin(const SkinManager *smgr)
		{
			skinMgr = smgr;
			this->setStyleSheet(smgr->getStyleSheet());
			playlist.setStyleSheet(smgr->getStyleSheet());
			songWindow.setStyleSheet(smgr->getStyleSheet());
			outputSettings.setStyleSheet(smgr->getStyleSheet());
			generalSettings.setStyleSheet(smgr->getStyleSheet());
			tutorial.setStyleSheet(smgr->getStyleSheet());
			songSearch.setStyleSheet(smgr->getStyleSheet());
		}

		void MainWindow::handleSubwinVisibilisty(SoSSubWindow *window, bool show)
		{
			window->setAllowShow(show);
			if(show) window->show();
			else if (!window->isFullScreen())
				window->hide();
		}

		void MainWindow::on_songCheckbox_clicked(bool checked)
		{
			handleSubwinVisibilisty(&songWindow, checked);
		}

		void MainWindow::on_playlistCheckbox_clicked(bool checked)
		{
			handleSubwinVisibilisty(&playlist, checked);
		}

		void MainWindow::on_outputCheckbox_clicked(bool checked)
		{
			handleSubwinVisibilisty(&outputSettings, checked);
		}

		void MainWindow::on_songSearchCheckbox_clicked(bool checked)
		{
			handleSubwinVisibilisty(&songSearch, checked);
		}

		void MainWindow::on_settingsCheckbox_clicked(bool checked)
		{
			handleSubwinVisibilisty(&generalSettings, checked);
		}

		void MainWindow::on_ejectButton_clicked()
		{
            playlist.addFile(QFileDialog::getOpenFileName(this, tr("Open File"), playlist.lastOpenedDir.absolutePath(), "Audio Files, UltraStar Txt, SoS Playlist (" + FILE_FORMATS.join(" ") + ")"));
		}

		void MainWindow::tutorialPageChange(QString docName, int pageId)
		{
			generalSettings.setTutorialHighlight(0);
			outputSettings.setTutorialHighlight(false);

			if(docName != "tutorial")
				return;

			switch(pageId)
			{
			case 0:
				break;
			case 1:
				generalSettings.setAllowShow(true);
				generalSettings.show();
				songWindow.setAllowShow(true);
				songWindow.show();
				tutorial.raise();
				generalSettings.setTutorialHighlight(1);
				break;
			case 2:
				generalSettings.setTutorialHighlight(2);
				break;
			case 3:
				outputSettings.setAllowShow(true);
				outputSettings.show();
				tutorial.raise();
				break;
			case 4:
				playlist.clearPlaylist();
				playlist.addFile("samples/jingle_bells.kar");
				playlist.loadNextSong();
				outputSettings.setTutorialHighlight(true);
				break;
			case 5:
				songSearch.setAllowShow(true);
				songSearch.show();
				tutorial.raise();
			}
		}

		void MainWindow::tutorialClose()
		{
			generalSettings.setTutorialHighlight(false);
			outputSettings.setTutorialHighlight(false);
			tutorial.close();
		}

		void MainWindow::on_tutorialCheckbox_clicked(bool checked)
		{
			tutorial.setDocumentName("help");
			tutorial.setPage(0);
			handleSubwinVisibilisty(&tutorial, checked);
			tutorial.raise();
		}
	}
}
