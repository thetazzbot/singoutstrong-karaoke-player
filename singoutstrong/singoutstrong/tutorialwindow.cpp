#include "tutorialwindow.h"
#include "ui_tutorialwindow.h"

namespace SoS
{
	namespace QtGui
	{

		TutorialWindow::TutorialWindow(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::TutorialWindow),
			pageNumber(0),
			documentName("tutorial")
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
			reload();
			SoSSubWindow::show();
		}

		void TutorialWindow::setDocumentName(QString name)
		{
			documentName = name;
		}

		void TutorialWindow::setPage(int page)
		{
			pageNumber = page >= 0 ? page : 0;
		}

		bool TutorialWindow::reload()
		{
			QFile file(QString("./docs/%1/%2.htm").arg(documentName).arg(pageNumber));
			ui->prevButton->show();

			if(file.open(QIODevice::ReadOnly))
			{
				ui->label->setText(file.readAll());
				file.close();
			}
			else
				return false;

			if(QFile::exists(QString("./docs/%1/%2.htm").arg(documentName).arg(pageNumber+1)))
				ui->nextButton->setText("Next");
			else
			{
				ui->nextButton->setText("Close");
				if(pageNumber == 0)
					ui->prevButton->hide();
			}

			if(pageNumber > 0)
				ui->prevButton->setText("Back");
			else
				ui->prevButton->setText("Cancel");

			return true;
		}

		void TutorialWindow::on_nextButton_clicked()
		{
			pageNumber++;
			if(! reload())
				close();
			else
				emit pageChanged(documentName, pageNumber);
		}

		void TutorialWindow::on_prevButton_clicked()
		{
			pageNumber--;
			if(! reload())
				close();
			else
				emit pageChanged(documentName, pageNumber);
		}

		void TutorialWindow::on_label_linkActivated(const QString &link)
		{
			if(link.startsWith("doc:"))
			{
				QStringList docInfo = link.split('/');
				bool success = false;
				int page = docInfo.back().toInt(&success);

				if(success)
				{
					pageNumber = page;
					docInfo.pop_back();
					if(docInfo.size() > 0)
						documentName = docInfo.back();

					reload();
				}
			}
			else
				QDesktopServices::openUrl(QUrl(link));
		}
	}
}
