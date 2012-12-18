#include "generalsettings.h"
#include "ui_generalsettings.h"

namespace SoS
{
	namespace QtGui
	{
		void GeneralSettings::setTutorialHighlight(int stage)
		{
			if(stage == 1 || stage == 2)
				ui->content->setCurrentIndex(0);
			ui->deviceBox->setProperty("tutorialHighlight", stage == 1);
			ui->deviceLabel->setProperty("tutorialHighlight", stage == 1);
			ui->applyButton->setProperty("tutorialHighlight", stage == 1);
			ui->samplesLabel->setProperty("tutorialHighlight", stage == 2);
			ui->volumeTresholdLabel->setProperty("tutorialHighlight", stage == 2);

			ui->deviceBox->setStyleSheet(ui->deviceBox->styleSheet());
			ui->deviceLabel->setStyleSheet(ui->deviceLabel->styleSheet());
			ui->applyButton->setStyleSheet(ui->applyButton->styleSheet());
			ui->samplesLabel->setStyleSheet(ui->deviceLabel->styleSheet());
			ui->volumeTresholdLabel->setStyleSheet(ui->applyButton->styleSheet());
		}

		void GeneralSettings::refreshSettings()
		{
			if(!context)
				return;

			ui->deviceBox->clear();
			int devCount = context->AudioInput->getAvailableInDevicesCount();
			for (int i = 0; i < devCount; i++)
			{
				AudioDeviceInfo info = context->AudioInput->getAvailableInDevice(i);
				ui->deviceBox->addItem(QString::fromUtf8(info.DeviceName), info.Id);

				if(context->AudioInput->getCurrentDevice().Id == info.Id)
					ui->deviceBox->setCurrentIndex(i);
			}

			ui->samplesSlider->setValue(log2(context->AudioAnalyzer->getSamplesArraySize()));
			ui->samplesLabel->setText(QString("Input Sample: %1").arg(context->AudioAnalyzer->getSamplesArraySize()));
			ui->volumeTresholdSlider->setValue(context->AudioAnalyzer->getVolumeThreshold()*100);
			ui->volumeTresholdLabel->setText(QString("Volume Treshold: %1%").arg(context->AudioAnalyzer->getVolumeThreshold()*100));
		}

		void GeneralSettings::on_applyButton_clicked()
		{
			if(context->AudioInput->setDevice(ui->deviceBox->itemData(ui->deviceBox->currentIndex()).toInt()))
				ui->applyButton->setEnabled(false);
			else
				QMessageBox::critical(this, tr("SoS"),
									  tr("Sorry, the device could not be opened"),
									  QMessageBox::Ok);
		}

		void GeneralSettings::on_deviceBox_currentIndexChanged(int index)
		{
			ui->applyButton->setEnabled(
						context->AudioInput->getCurrentDevice().Id != ui->deviceBox->itemData(index)
					);
		}

		void GeneralSettings::on_samplesSlider_valueChanged(int value)
		{
			int samples = pow(2, value);
			context->AudioAnalyzer->setSamplesArraySize(samples);
			ui->samplesLabel->setText(QString("Input Sample: %1").arg(samples));
		}

		void GeneralSettings::on_volumeTresholdSlider_valueChanged(int value)
		{
			context->AudioAnalyzer->setVolumeThreshold((float)value / 100.0);
			ui->volumeTresholdLabel->setText(QString("Volume Treshold: %1%").arg(value));
		}

	}
}
