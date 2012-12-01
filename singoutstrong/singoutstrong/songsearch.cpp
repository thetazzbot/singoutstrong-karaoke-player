#include "songsearch.h"
#include "ui_songsearch.h"

namespace SoS
{
	namespace QtGui
	{

		SongSearch::SongSearch(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::SongSearch)
		{
			ui->setupUi(this);

			allowShow = true;
			setSubWidgets(ui->windowBar, ui->content);
			connect(&httpHandler, SIGNAL(receivedResponse(QString)),
					this, SLOT(gotResponse(QString)));
		}

		SongSearch::~SongSearch()
		{
			delete ui;
		}

		void SongSearch::gotResponse(QString response)
		{
			QFile file("response.htm");
			if(file.open(QIODevice::WriteOnly))
			{
				QTextStream stream(&file);
				stream.setCodec("UTF-8");
				stream << response;
				file.close();
			}
			ui->label->setText("got request");
		}

		void SongSearch::on_pushButton_clicked()
		{
			httpHandler.postRequest("http://ultrastar-base.com/index.php?section=search_result");
		}
	}
}
