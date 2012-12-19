#include "settings.h"
#include "ui_settings.h"

namespace SoS
{
	namespace QtGui
	{

		Settings::Settings(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::Settings)
		{
			ui->setupUi(this);
			setSubWidgets(ui->windowBar, ui->content);
		}

		Settings::~Settings()
		{
			delete ui;
		}

		void Settings::show()
		{
			refresh();
			SoSSubWindow::show();
		}

		void Settings::refresh()
		{
			ui->skinsList->clear();
			QDir dir("skins");
			if(dir.exists())
			{
				ui->skinsList->addItems(dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot));
			}

			for(int i = 0; i < ui->skinsList->count(); i++)
			{
				if(ui->skinsList->item(i)->text() == skinManager.getSkinName())
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

		void Settings::setCurrentSkin(QString name)
		{
			skinManager.setSkin(name);
			emit skinSet(&skinManager);
		}

		void Settings::on_latencySlider_valueChanged(int value)
		{
			context->SongControl->getSettings()->setOutputLatency(value*10);
			ui->latencyValueLabel->setText(QString("%1 ms").arg(value*10));
		}

		void Settings::on_timeRangeSlider_valueChanged(int value)
		{
			context->SongControl->getSettings()->setViewTimeRange(value*100);
			ui->timeRangeValueLabel->setText(QString("%1 ms").arg(value*100));
		}

		void Settings::on_skinsList_itemDoubleClicked(QListWidgetItem *item)
		{
			ui->skinsList->setHighlightedItem(item->listWidget()->currentRow());
			setCurrentSkin(item->text());
		}

		void Settings::on_textLinesBox_valueChanged(int arg1)
		{
			context->SongControl->getSettings()->setTextLineCount(arg1);
			ui->groupedByBox->setMaximum(arg1);
			emit textLinesSet(arg1);
		}

		void Settings::on_groupedByBox_valueChanged(int arg1)
		{
			context->SongControl->getSettings()->setTextGroupBy(arg1);
		}

	}
}
