#include <QtGui>
#include "generalsettings.h"
#include "ui_generalsettings.h"

namespace SoS
{
	namespace QtGui
	{

		GeneralSettings::GeneralSettings(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::GeneralSettings)
		{
			ui->setupUi(this);
			setSubWidgets(ui->windowBar, ui->content);
		}

		GeneralSettings::~GeneralSettings()
		{
			delete ui;
		}

		void GeneralSettings::show()
		{
			refresh();
			SoSSubWindow::show();
		}

		void GeneralSettings::refresh()
		{
			ui->skinsList->clear();
			QDir dir("skins");
			if(dir.exists())
			{
				ui->skinsList->addItems(dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot));
			}

			for(int i = 0; i < ui->skinsList->count(); i++)
			{
				if(ui->skinsList->item(i)->text() == currentSkin)
				{
					ui->skinsList->setHighlightedItem(i);
					break;
				}
			}

			ui->latencySlider->setValue(context->SongControl->getSettings()->getOutputLatency() / 10);
			ui->timeRangeSlider->setValue(context->SongControl->getSettings()->getViewTimeRange() / 100);
			ui->textLinesBox->setValue(context->SongControl->getSettings()->getTextLineCount());
			ui->groupedByBox->setValue(context->SongControl->getSettings()->getTextGroupBy());
		}

		QString GeneralSettings::getCurrentSkin()
		{
			return currentSkin;
		}

		void GeneralSettings::setCurrentSkin(QString name)
		{
			currentSkin = name;
		}

		void GeneralSettings::on_latencySlider_valueChanged(int value)
		{
			context->SongControl->getSettings()->setOutputLatency(value*10);
			ui->latencyValueLabel->setText(QString("%1 ms").arg(value*10));
		}

		void GeneralSettings::on_timeRangeSlider_valueChanged(int value)
		{
			context->SongControl->getSettings()->setViewTimeRange(value*100);
			ui->timeRangeValueLabel->setText(QString("%1 ms").arg(value*100));
		}

		void GeneralSettings::on_skinsList_itemDoubleClicked(QListWidgetItem *item)
		{
			ui->skinsList->setHighlightedItem(item->listWidget()->currentRow());
			setCurrentSkin(item->text());

			emit skinSet(item->text());
		}

		void GeneralSettings::on_textLinesBox_valueChanged(int arg1)
		{
			context->SongControl->getSettings()->setTextLineCount(arg1);
			ui->groupedByBox->setMaximum(arg1);
			emit textLinesSet(arg1);
		}

		void GeneralSettings::on_groupedByBox_valueChanged(int arg1)
		{
			context->SongControl->getSettings()->setTextGroupBy(arg1);
		}

	}
}
