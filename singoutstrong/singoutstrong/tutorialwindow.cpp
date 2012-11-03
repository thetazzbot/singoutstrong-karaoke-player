#include "tutorialwindow.h"
#include "ui_tutorialwindow.h"

namespace SoS
{
	namespace QtGui
	{

		TutorialWindow::TutorialWindow(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::TutorialWindow),
			page(0)
		{
			allowShow = true;
			ui->setupUi(this);
			setSubWidgets(ui->windowBar, ui->content);
			sizeGrip->hide();
		}

		TutorialWindow::~TutorialWindow()
		{
			delete ui;
		}

		void TutorialWindow::show()
		{
			page = 0;
			loadPage();
			SoSSubWindow::show();
		}

		bool TutorialWindow::loadPage()
		{
			QFile file(QString("./docs/tutorial/%1.htm").arg(page));

			if(file.open(QIODevice::ReadOnly))
			{
				ui->label->setText(file.readAll());
				file.close();
			}
			else
				return false;

			if(QFile::exists(QString("./docs/tutorial/%1.htm").arg(page+1)))
				ui->nextButton->setText("Next");
			else
				ui->nextButton->setText("Finish");

			if(page > 0)
				ui->prevButton->setText("Back");
			else
				ui->prevButton->setText("Cancel");

			return true;
		}

		void TutorialWindow::on_nextButton_clicked()
		{
			page++;
			if(! loadPage())
				close();
			else
				emit pageChanged(page);
		}

		void TutorialWindow::on_prevButton_clicked()
		{
			page--;
			if(! loadPage())
				close();
			else
				emit pageChanged(page);
		}
	}
}
