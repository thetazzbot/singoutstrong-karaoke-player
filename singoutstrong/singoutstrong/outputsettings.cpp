#include "outputsettings.h"
#include "ui_outputsettings.h"

namespace SoS
{
	namespace QtGui
	{

		OutputSettings::OutputSettings(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::OutputSettings),
			lastSolo(-1)
		{
			ui->setupUi(this);
			setSubWidgets(ui->windowBar, ui->content);
		}

		OutputSettings::~OutputSettings()
		{
			delete ui;
		}

		void OutputSettings::show()
		{
			SoSSubWindow::show();
			resizeEvent(0);
		}

		void OutputSettings::setTutorialHighlight(bool active)
		{
			ui->outputTracks->setProperty("tutorialHighlight", active);
			ui->outputTracks->setStyleSheet(ui->outputTracks->styleSheet());

			for(int i = 0; i < vocalTracks.size(); i++)
			{
				trackNames[i]->setProperty("tutorialHighlight", active);
				vocalTracks[i]->setProperty("tutorialHighlight", active);
				mutes[i]->setProperty("tutorialHighlight", active);
				solos[i]->setProperty("tutorialHighlight", active);

				trackNames[i]->setStyleSheet(trackNames[i]->styleSheet());
				vocalTracks[i]->setStyleSheet(vocalTracks[i]->styleSheet());
				mutes[i]->setStyleSheet(mutes[i]->styleSheet());
				solos[i]->setStyleSheet(solos[i]->styleSheet());
			}


		}

		void OutputSettings::clearLists()
		{
			for(int x = 0; x < vocalTracks.size(); x++)
			{
				delete vocalTracks[x];
				delete mutes[x];
				delete solos[x];
				delete volumes[x];
				delete trackNames[x];
			}

			vocalTracks.clear();
			mutes.clear();
			solos.clear();
			volumes.clear();
			trackNames.clear();
			trackIndeces.clear();
		}

		void OutputSettings::resizeEvent(QResizeEvent *e)
		{
			int scrollBarWidth = ui->outputTracks->verticalScrollBar() ? ui->outputTracks->verticalScrollBar()->width() : 0;
			ui->outputTrackContents->resize(ui->outputTracks->width() - scrollBarWidth, 30*vocalTracks.size()+15);
			SoSSubWindow::resizeEvent(e);
		}

		void OutputSettings::updateSettings()
		{
			updateTracks();
			ui->keyShiftSlider->setValue(context->SongControl->getSettings()->getKeyShift());
			ui->volumeSlider->setValue(context->SongControl->getSettings()->getVolume());
			ui->tempoSlider->setValue(context->SongControl->getSettings()->getTempo()*100);
		}

		void OutputSettings::updateTracks()
		{
			clearLists();

			if(context && context->SongControl && context->SongControl->isLoaded())
			{
				const ISong* song = context->SongControl->getSong();

				int linesAdded = 0;
				for(int x = 0; x < song->getTracksCount(); x++)
				{
					if(song->getTrack(x)->getNoteCount() == 0)
						continue;

					trackNames.push_back(new QLabel(this));
					trackNames[linesAdded]->setObjectName(QString("trackNameLabel_%1").arg(linesAdded));
					trackNames[linesAdded]->setText(QString::fromUtf8(song->getTrack(x)->getName()));
					ui->gridLayout_3->addWidget(trackNames[linesAdded], linesAdded, 0, 1, 1);

					vocalTracks.push_back(new QCheckBox(this));
					vocalTracks[linesAdded]->setProperty("vocalsButton", true);
					vocalTracks[linesAdded]->setObjectName(QString("vocalsButton_%1").arg(linesAdded));
					ui->gridLayout_3->addWidget(vocalTracks[linesAdded], linesAdded, 1, 1, 1);
					QObject::connect(vocalTracks[linesAdded], SIGNAL(clicked(bool)), this, SLOT(setVocalTrack(bool)));

					mutes.push_back(new QCheckBox(this));
					mutes[linesAdded]->setProperty("muteButton", true);
					mutes[linesAdded]->setObjectName(QString("muteButton_%1").arg(linesAdded));
					ui->gridLayout_3->addWidget(mutes[linesAdded], linesAdded, 2, 1, 1);
					QObject::connect(mutes[linesAdded], SIGNAL(clicked(bool)), this, SLOT(setMute()));

					solos.push_back(new QCheckBox(this));
					solos[linesAdded]->setProperty("soloButton", true);
					solos[linesAdded]->setObjectName(QString("soloButton_%1").arg(linesAdded));
					ui->gridLayout_3->addWidget(solos[linesAdded], linesAdded, 3, 1, 1);
					QObject::connect(solos[linesAdded], SIGNAL(clicked(bool)), this, SLOT(setSolo(bool)));

					volumes.push_back(new QProgressBar(this));
					volumes[linesAdded]->setObjectName(QString("volumeBar_%1").arg(linesAdded));
					ui->gridLayout_3->addWidget(volumes[linesAdded], linesAdded, 4, 1, 1);

					volumes[linesAdded]->setTextVisible(false);
					volumes[linesAdded]->setMaximum(16);

					trackIndeces.push_back(x);
					linesAdded++;
				}
				resizeEvent(NULL);
			}

			setVocalTrack(0);
			repaint();
		}

		void OutputSettings::updateVolumes()
		{
			if(!context->SongControl->isLoaded() || context->SongControl->getSong()->getTracksCount() == 0)
				return;

			for(int x = 0; x < volumes.size(); x++)
			{
				volumes[x]->setValue(context->SongControl->getSong()->getTrack(trackIndeces[x])->getCurrVolume());
			}
		}

		void OutputSettings::on_keyShiftSlider_valueChanged(int value)
		{
			context->SongControl->getSettings()->setKeyShift(value);
			ui->currKeyShiftLabel->setText(QString("%1").arg(value));
		}

		void OutputSettings::on_volumeSlider_valueChanged(int value)
		{
			context->SongControl->getSettings()->setVolume(value);
			ui->currVolumeLabel->setText(QString("%1%").arg((int)(100*value/255)));
		}

		void OutputSettings::on_tempoSlider_valueChanged(int value)
		{
			ui->currTempoLabel->setText(QString("%1%").arg(value));
			context->SongControl->getSettings()->setTempo(value/100.0);
		}


		void OutputSettings::setMute()
		{
			if(!context || !context->SongControl)
				return;

			for(int i = 0; i < trackIndeces.size(); i++)
			{
				context->SongControl->setMute(mutes[i]->isChecked(), trackIndeces[i]);
			}
		}

		void OutputSettings::setVocalTrack(bool buttonChecked)
		{
			int setBox = handleGroupedCheckboxes(vocalTracks, buttonChecked, context->SongControl->getSettings()->getSelectedTrackIndex(), false);
			if(setBox > -1)
				context->SongControl->getSettings()->setSelectedTrackIndex(trackIndeces[setBox]);
		}

		void OutputSettings::setSolo(bool buttonChecked)
		{
			int setBox = handleGroupedCheckboxes(solos, buttonChecked, lastSolo, true);
			if(setBox > -1)
			{
				lastSolo = buttonChecked ? trackIndeces[setBox] : -1;
				context->SongControl->setSolo(buttonChecked, trackIndeces[setBox]);
			}
		}

		int OutputSettings::handleGroupedCheckboxes(QList<QCheckBox *> &list, bool buttonChecked, int lastChecked, bool allowUncheck)
		{
			if(!context || !context->SongControl)
				return -1;

			int setBox = -1;
			if(buttonChecked)
			{
				for(int i = 0; i < trackIndeces.size(); i++)
				{
					if(setBox < 0 && list[i]->isChecked() && trackIndeces[i] != lastChecked)
					{
						setBox = i;
					}
					else
					{
						list[i]->setChecked(false);
					}
				}
				return setBox;
			}
			else
			{
				for(int i = 0; i < trackIndeces.size(); i++)
				{
					if(trackIndeces[i] == lastChecked)
					{
						setBox = i;
						list[i]->setChecked(!allowUncheck);
					}
					else
						list[i]->setChecked(false);
				}
				return setBox;
			}

		}

	}
}
