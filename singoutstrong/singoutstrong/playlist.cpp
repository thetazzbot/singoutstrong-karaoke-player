#include "playlist.h"
#include "ui_Playlist.h"

namespace SoS
{
	namespace QtGui
	{

		Playlist::Playlist(QWidget *parent) :
			SoSSubWindow(parent),
			ui(new Ui::Playlist)
		{
			ui->setupUi(this);
			setSubWidgets(ui->windowBar, ui->content);
		}

		Playlist::~Playlist()
		{
			delete ui;
		}

		bool Playlist::eventFilter(QObject *target, QEvent *event)
		{
			switch(event->type())
			{
			case QEvent::DragEnter:
				dragEnterEvent((QDragEnterEvent*)event);
				break;
			case QEvent::Drop:
				dropEvent((QDropEvent*)event);
				break;
			default:
				return false;
			}

			return false;
		}

		void Playlist::dragEnterEvent(QDragEnterEvent *event)
		{
			if(event->mimeData()->hasUrls())
			{
				QList<QUrl> urlList = event->mimeData()->urls();
				QFileInfo fInfo(urlList[0].toString());

				if(urlList.count() > 1 || FILE_FORMATS.contains("*." + fInfo.completeSuffix()))
					event->acceptProposedAction();
			}
		}

		void Playlist::dropEvent(QDropEvent *event)
		{
			QList<QUrl> urlList;


			if (event->mimeData()->hasUrls())
			{
				urlList = event->mimeData()->urls();

				for(int i = 0; i < urlList.size(); i++)
				{
					addFile(urlList[i].toLocalFile());
				}

				if(ui->PlaylistBox->count() == 1 && !context->SongControl->isLoaded())
				{
					loadSongFromList(0);
				}
			}
		}

		void Playlist::keyPressEvent(QKeyEvent *event)
		{
			if(event->key() == Qt::Key_Delete)
			{
				for(int i = 0; i < ui->PlaylistBox->selectedItems().count(); i++)
				{
					delete ui->PlaylistBox->selectedItems().at(i);

					if(ui->PlaylistBox->currentRow() < ui->PlaylistBox->getLastHighlightedItem())
						ui->PlaylistBox->setLastHighlightedItem(ui->PlaylistBox->getLastHighlightedItem()-1);
					else if(ui->PlaylistBox->currentRow() == ui->PlaylistBox->getLastHighlightedItem())
						ui->PlaylistBox->setLastHighlightedItem(ui->PlaylistBox->currentRow()-1);
				}
			}
		}

		void Playlist::addFile(QString filename)
		{
			if(filename.isEmpty() || filename.isNull())
				return;

			QFileInfo fInfo;
			fInfo.setFile(filename);
			lastOpenedDir = fInfo.absoluteDir();

			if(fInfo.isFile() && FILE_FORMATS.contains("*." + fInfo.completeSuffix()))
			{
				if(fInfo.completeSuffix() == LIST_EXT)
					loadPlaylist(filename);
				else
				{
					ui->PlaylistBox->addItem(fInfo.fileName());
					ui->PlaylistBox->item(ui->PlaylistBox->count()-1)->
							setData(Qt::UserRole, fInfo.absoluteFilePath());
				}
			}
		}

		void Playlist::clearPlaylist()
		{
			ui->PlaylistBox->clear();
		}

		void Playlist::loadPlaylist(QString filename)
		{
			QFile file(filename);

			if(file.open(QIODevice::ReadOnly))
			{
				QDomDocument doc("Playlist");
				doc.setContent(&file);
				file.close();;

				QDomElement docElement = doc.documentElement();
				QDomNode node = docElement.firstChildElement("song");

				while(!node.isNull())
				{
					addFile(node.attributes().namedItem("path").nodeValue());
					node = node.nextSiblingElement("song");
				}
				lastOpenedDir = filename;
				lastOpenedDir.cdUp();
			}

			if(ui->PlaylistBox->count() > 0)
			{
				ui->PlaylistBox->setCurrentRow(0);
				loadSongFromList(0);
			}
		}

		void Playlist::savePlaylist(QString filename)
		{
			QDomDocument doc("Playlist");
			QDomElement Playlist = doc.createElement("Playlist");
			doc.appendChild(Playlist);

			for(int i = 0; i < ui->PlaylistBox->count(); i++)
			{
				QDomElement song = doc.createElement("song");
				song.setAttribute("path", ui->PlaylistBox->item(i)->data(Qt::UserRole).toString());
				Playlist.appendChild(song);
			}

			QFile file(filename);
			if(file.open(QIODevice::WriteOnly))
			{
				QTextStream stream(&file);
				stream.setCodec("UTF-8");
				stream << doc.toString();
				file.close();
			}
		}

		void Playlist::loadSongFromList(int songIndex)
		{
			if(ui->PlaylistBox->count() <= 0)
				return;

			songIndex = songIndex < 0 ? 0 : songIndex >= ui->PlaylistBox->count() ? ui->PlaylistBox->count()-1 : songIndex;

			QString fileName = ui->PlaylistBox->item(songIndex)->data(Qt::UserRole).toString();
			context->SongControl->stop();

			if(	context->SongControl->load(fileName.toLocal8Bit().data()))
			{
				context->SongControl->rewind();
				context->SongControl->getSettings()->setViewedTime(0);
				ui->PlaylistBox->setHighlightedItem(songIndex);
			}
			else
			{
				QMessageBox::critical(this, tr("SoS"),
									  tr("Sorry, the file could not be opened"),
									  QMessageBox::Ok);
				delete ui->PlaylistBox->item(songIndex);
			}
			emit songLoaded();
		}

		void Playlist::loadNextSong()
		{
			loadSongFromList(ui->PlaylistBox->getLastHighlightedItem()+1);
		}

		void Playlist::loadPrevSong()
		{
			loadSongFromList(ui->PlaylistBox->getLastHighlightedItem()-1);
		}

		void Playlist::on_PlaylistBox_itemDoubleClicked(QListWidgetItem *item)
		{
			loadSongFromList(item->listWidget()->currentRow());
			context->SongControl->start();
		}

		void Playlist::on_newListButton_clicked()
		{
			clearPlaylist();
		}

		void Playlist::on_saveListButton_clicked()
		{
			lastOpenedDir = QDir(QFileDialog::getSaveFileName(this, tr("Save playlist"), lastOpenedDir.absolutePath(), "SoS Playlist (*." + LIST_EXT + ")"));
			savePlaylist(lastOpenedDir.absolutePath());
			lastOpenedDir.cdUp();
		}

	}
}
