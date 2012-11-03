#include "sossubwindow.h"

namespace SoS
{
	namespace QtGui
	{

		SoSSubWindow::SoSSubWindow(QWidget *parent, Qt::WindowFlags flags) : QFrame(parent, flags),
			context(NULL),
			content(NULL),
			windowBar(NULL),
			sizeGrip(new QSizeGrip(this)),
			allowShow(false)
		{
			setWindowFlags(Qt::SplashScreen);
			sizeGrip->resize(15,15);
		}

		void SoSSubWindow::resizeEvent(QResizeEvent *)
		{
			sizeGrip->move(width() - sizeGrip->width(), height() - sizeGrip->height());

			if(windowBar)
			{
				windowBar->resize(width(), windowBar->height());
				if(content) content->resize(width(), height() - windowBar->height() + 1);
			}
		}

		void SoSSubWindow::setSubWidgets(QWidget *bar, QWidget *winContent)
		{
			windowBar = bar;
			content = winContent;
			sizeGrip->raise();
		}

		void SoSSubWindow::init(SoSContext* sosContext)
		{
			context = sosContext;
		}

		bool SoSSubWindow::getAllowShow()
		{
			return allowShow;
		}

		void SoSSubWindow::setAllowShow(bool v)
		{
			allowShow = v;
		}

		void SoSSubWindow::show()
		{
			if(allowShow)
			{
				QFrame::show();
				//Workaround for the problem with layouts and locations of widgets
				resize(size() + QSize(10, 10));
				resize(size() - QSize(10, 10));

				if(content) content->show();
				if(windowBar) windowBar->show();
			}
		}

	}
}
