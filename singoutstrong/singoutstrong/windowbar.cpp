#include "windowbar.h"
#include "ui_windowbar.h"

namespace SoS
{
	namespace QtGui
	{

		WindowBar::WindowBar(QWidget *parent) :
			QFrame(parent),
			ui(new Ui::WindowBar)
		{
			ui->setupUi(this);
			topWidget = parent;

			while(topWidget && topWidget->parentWidget())
				topWidget = topWidget->parentWidget();

			ui->minimizeButton->hide();
		}

		WindowBar::~WindowBar()
		{
			delete ui;
		}

		void WindowBar::showMinimize()
		{
			ui->minimizeButton->show();
		}

		void WindowBar::hideMinimize()
		{
			ui->minimizeButton->hide();
		}

		void WindowBar::resizeEvent(QResizeEvent *e)
		{
			ui->titleLabel->setGeometry(5, 0, e->size().width() - 5 - (e->size().height()-2)*2, e->size().height());
			ui->minimizeButton->setGeometry(ui->titleLabel->geometry().right(), 1, e->size().height()-2, e->size().height()-2);
			ui->exitButton->setGeometry(ui->minimizeButton->geometry().right(), 1, e->size().height()-2, e->size().height()-2);

			ui->titleLabel->setText(topWidget ? topWidget->windowTitle() : "");
		}

		void WindowBar::mousePressEvent(QMouseEvent *event)
		{
			if (event->button() == Qt::LeftButton)
			{
				dragPosition = event->globalPos() - topWidget->frameGeometry().topLeft();
				event->accept();
			}
		}

		void WindowBar::mouseMoveEvent(QMouseEvent *event)
		{
			if (event->buttons() & Qt::LeftButton)
			{
				topWidget->move(event->globalPos() - dragPosition);
				event->accept();
			}
		}

		void WindowBar::on_exitButton_clicked()
		{
			topWidget->hide();
			emit exitPushed();
		}

		void WindowBar::on_minimizeButton_clicked()
		{
			topWidget->setWindowState(Qt::WindowMinimized);
		}

	}
}
