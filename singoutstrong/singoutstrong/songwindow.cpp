#include "songwindow.h"
#include "ui_songwindow.h"

namespace SoS
{
	namespace QtGui
	{

		SongWindow::SongWindow(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::SongWindow)
		{
			ui->setupUi(this);
			ui->fullScreenInfo->hide();
			setSubWidgets(ui->windowBar, NULL);
		}

		SongWindow::~SongWindow()
		{
			delete ui;
		}

		void SongWindow::showNormal()
		{
			windowBar->show();
			ui->fullScreenInfo->hide();
			SoSSubWindow::showNormal();
		}

		void SongWindow::mouseDoubleClickEvent(QMouseEvent *event)
		{
			windowBar->hide();
			this->showFullScreen();
			ui->fullScreenInfo->setGeometry(ui->lyrics->geometry());
			ui->fullScreenInfo->show();
			ui->fullScreenInfo->raise();
		}

		void SongWindow::resizeEvent(QResizeEvent *event)
		{
			float ratio = 0.7;
			int barHeight = windowBar->isVisible() ? ui->windowBar->height() : 0;
			int contentHeight = event->size().height() - barHeight;
			ui->notes->setGeometry(1, barHeight, event->size().width()-2, contentHeight * ratio);
			ui->lyrics->setGeometry(1, ui->notes->height() + barHeight, event->size().width()-2, contentHeight * (1-ratio));
			SoSSubWindow::resizeEvent(event);
		}

		void SongWindow::update()
		{
			ui->notes->update();
			ui->lyrics->update();
		}

		void SongWindow::init(SoSContext *context)
		{
			SoSSubWindow::init(context);

			ui->notes->setSoSContext(context);
			ui->lyrics->setSoSContext(context);
		}

		void SongWindow::setTextLines(int number)
		{
			ui->lyrics->setLineCount(number);
		}
	}
}
