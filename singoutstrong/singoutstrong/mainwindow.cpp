#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace SoS
{
	namespace QtGui
	{

		MainWindow::MainWindow(QWidget *parent) :
			QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
			ui(new Ui::MainWindow),
			sosContext(new SoSContext()),
			lowestFPS(100),
			elapsed(0),
			detachViewTime(false),
			showTutorial(false),
			timesLaunched(0),
			promoShown(false)
		{

			setFocusPolicy(Qt::StrongFocus);
			Output2FILE::Stream() = fopen("sos_main.log", "w");
			QCoreApplication::setApplicationName("SoS");
			ui->setupUi(this);
			ui->windowBar->showMinimize();

			sosContext->SingDevice = createSoSDevice();
			sosContext->AudioAnalyzer = sosContext->SingDevice->getAudioAnalyzer();
			sosContext->AudioInput = sosContext->SingDevice->getAudioInput();
			sosContext->AudioAnalyzer->setVolumeThreshold(0.05f);
			sosContext->AudioAnalyzer->setSamplesArraySize(1024);
			sosContext->SongControl = sosContext->SingDevice->getSongControl();
			settings = sosContext->SongControl->getSettings();
			settings->setSelectedTrackIndex(0);
			settings->setOutputLatency(150);
			settings->setViewedTime(0);

			audioInSettingsWindow.init(sosContext);
			outputSettings.init(sosContext);
			playlist.init(sosContext);
			songWindow.init(sosContext);
			generalSettings.init(sosContext);

			connect(&generalSettings, SIGNAL(skinSet(QString)), this, SLOT (setSkin(QString)));
			connect(&generalSettings, SIGNAL(textLinesSet(int)), &songWindow, SLOT (setTextLines(int)));
			connect(&playlist, SIGNAL(songLoaded()), this, SLOT (updateSong()));
			connect(ui->windowBar, SIGNAL(exitPushed()), this, SLOT(close()));
			connect(&tutorial, SIGNAL(pageChanged(QString, int)), this, SLOT(tutorialPageChange(QString, int)));

			audioInSettingsWindow.installEventFilter(this);
			outputSettings.installEventFilter(this);
			playlist.installEventFilter(this);
			songWindow.installEventFilter(this);
			generalSettings.installEventFilter(this);
			tutorial.installEventFilter(this);
			installEventFilter(&playlist);

			ui->songCheckbox->installEventFilter(this);

			move(50, 20);
			playlist.move(x(), frameGeometry().bottom()+1);
			outputSettings.move(frameGeometry().right()+1, frameGeometry().top());
			audioInSettingsWindow.move(outputSettings.frameGeometry().right()+1, frameGeometry().top());
			generalSettings.move(audioInSettingsWindow.frameGeometry().right()+1, frameGeometry().top());
			songWindow.move(frameGeometry().right()+1, frameGeometry().bottom()+1);

			setAcceptDrops(true);
			setSkin("");

			playlist.loadPlaylist(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "\\playlist." + LIST_EXT);
			loadSettings();
			outputSettings.updateSettings();

			audioInSettingsWindow.refreshSettings();

			processPromo();
			timer.start(15, this);
		}

		MainWindow::~MainWindow()
		{
#ifdef DEBUG
			FILE_LOG(logDEBUG) << "[MainWindow]: Lowest FPS: " << lowestFPS;
#endif
			removeEventFilter(&playlist);
			audioInSettingsWindow.removeEventFilter(this);
			outputSettings.removeEventFilter(this);
			playlist.removeEventFilter(this);
			songWindow.removeEventFilter(this);
			generalSettings.removeEventFilter(this);
			tutorial.removeEventFilter(this);
			tutorial.close();

			sosContext->SingDevice->release();
			delete sosContext;
			delete ui;
		}

		void MainWindow::show()
		{
			QMainWindow::show();
			audioInSettingsWindow.show();
			outputSettings.show();
			playlist.show();
			songWindow.show();
			generalSettings.show();
			if(showTutorial)
			{
				tutorial.setDocumentName("tutorial");
				tutorial.setPage(0);
				tutorial.show();
			}
			//#ifndef DEBUG
						ui->label->hide();
			//#endif
		}

		void MainWindow::loadSettings()
		{
			QString location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
			QFile file(location + "\\settings.xml");

			if(file.open(QIODevice::ReadOnly))
			{
				QDomDocument doc("settings");
				doc.setContent(&file);
				file.close();

				QDomElement docElement = doc.documentElement();

				QDomNode node = docElement.firstChildElement("InputDevice");
				if(!node.isNull())
				{
					sosContext->AudioInput->setDevice(node.attributes().namedItem("Id").nodeValue().toInt());
				}
				node = docElement.firstChildElement("InputSamples");
				if(!node.isNull())
				{
					sosContext->AudioAnalyzer->setSamplesArraySize(node.attributes().namedItem("Samples").nodeValue().toInt());
				}
				node = docElement.firstChildElement("Volume");
				if(!node.isNull())
				{
					sosContext->SongControl->getSettings()->setVolume(
								node.attributes().namedItem("Volume").nodeValue().toInt());
				}
				node = docElement.firstChildElement("VolumeTreshold");
				if(!node.isNull())
				{
					sosContext->AudioAnalyzer->setVolumeThreshold(
								node.attributes().namedItem("Treshold").nodeValue().toFloat());
				}
				node = docElement.firstChildElement("TextGroupBy");
				if(!node.isNull())
				{
					settings->setTextGroupBy(
								node.attributes().namedItem("GroupBy").nodeValue().toInt());
				}
				node = docElement.firstChildElement("TextLineCount");
				if(!node.isNull())
				{
					settings->setTextLineCount(
								node.attributes().namedItem("LineCount").nodeValue().toInt());
				}
				node = docElement.firstChildElement("TimeShift");
				if(!node.isNull())
				{
					settings->setOutputLatency(
								node.attributes().namedItem("Shift").nodeValue().toInt());
				}
				node = docElement.firstChildElement("TimeRange");
				if(!node.isNull())
				{
					settings->setViewTimeRange(
								node.attributes().namedItem("Range").nodeValue().toInt());
				}
				node = docElement.firstChildElement("LastOpenedDir");
				if(!node.isNull())
				{
					playlist.lastOpenedDir = QDir(node.attributes().namedItem("Path").nodeValue());
				}

				node = docElement.firstChildElement("Promo");
				if(!node.isNull())
				{
					timesLaunched = node.attributes().namedItem("TimesLaunched").nodeValue().toInt();
					promoShown = node.attributes().namedItem("PromoShown").nodeValue().toInt();
				}

				QDomElement guiSection = docElement.firstChildElement("gui");
				loadWinProperties(this, &guiSection);
				loadWinProperties(&audioInSettingsWindow, &guiSection);
				loadWinProperties(&generalSettings, &guiSection);
				loadWinProperties(&outputSettings, &guiSection);
				loadWinProperties(&playlist, &guiSection);
				loadWinProperties(&songWindow, &guiSection);

				node = guiSection.firstChildElement("Skin");
				setSkin(node.isNull() ? "default" : node.attributes().namedItem("Name").nodeValue());
			}
			else
			{
				//if there was no settings file, then assume this is the first run and open the tutorial
				showTutorial = true;
			}
		}

		void MainWindow::saveSettings()
		{
			QString location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
			if(!QDir(location).exists())
				QDir().mkdir(location);

			playlist.savePlaylist(location + "\\Playlist." + LIST_EXT);

			QFile file(location + "\\settings.xml");

			QDomDocument doc("settings");
			if(file.open(QIODevice::ReadOnly))
			{
				doc.setContent(&file);
				file.close();
			}

			QDomElement root = getNode("settings", &doc, &doc);
			QDomElement node = getNode("InputDevice", &doc, &root);
			node.setAttribute("Id", sosContext->AudioInput->getCurrentDevice().Id);

			node = getNode("InputSamples", &doc, &root);
			node.setAttribute("Samples", sosContext->AudioAnalyzer->getSamplesArraySize());

			node = getNode("Volume", &doc, &root);
			node.setAttribute("Volume", sosContext->SongControl->getSettings()->getVolume());

			node = getNode("VolumeTreshold", &doc, &root);
			node.setAttribute("Treshold", sosContext->AudioAnalyzer->getVolumeThreshold());

			node = getNode("TextGroupBy", &doc, &root);
			node.setAttribute("GroupBy", settings->getTextGroupBy());

			node = getNode("TextLineCount", &doc, &root);
			node.setAttribute("LineCount", settings->getTextLineCount());

			node = getNode("TimeShift", &doc, &root);
			node.setAttribute("Shift", (qlonglong)settings->getOutputLatency());

			node = getNode("TimeRange", &doc, &root);
			node.setAttribute("Range", (qlonglong)settings->getViewTimeRange());

			node = getNode("LastOpenedDir", &doc, &root);
			node.setAttribute("Path", playlist.lastOpenedDir.absolutePath());

			node = getNode("Promo", &doc, &root);
			node.setAttribute("TimesLaunched", timesLaunched);
			node.setAttribute("PromoShown", promoShown);

			QDomElement guiNode = getNode("gui", &doc, &root);
			saveWinProperties(this, &doc, &guiNode);
			saveWinProperties(&audioInSettingsWindow, &doc, &guiNode);
			saveWinProperties(&generalSettings, &doc, &guiNode);
			saveWinProperties(&outputSettings, &doc, &guiNode);
			saveWinProperties(&playlist, &doc, &guiNode);
			saveWinProperties(&songWindow, &doc, &guiNode);

			node = getNode("Skin", &doc, &guiNode);
			node.setAttribute("Name", generalSettings.getCurrentSkin());

			if(file.open(QIODevice::WriteOnly))
			{
				QTextStream stream(&file);
				stream << doc.toString();
				file.close();
			}
		}

		void MainWindow::saveWinProperties(QWidget *window, QDomDocument *doc, QDomNode *parent)
		{
			QDomElement node = getNode(window->objectName(), doc, parent);
			node.setAttribute("x", window->geometry().x());
			node.setAttribute("y", window->geometry().y());
			node.setAttribute("w", window->geometry().width());
			node.setAttribute("h", window->geometry().height());
			node.setAttribute("visible", window->isVisible());
		}

		void MainWindow::loadWinProperties(QWidget *window, QDomElement *docElement)
		{
			QDomElement node = docElement->firstChildElement(window->objectName());
			if(!node.isNull())
			{
				window->setGeometry(node.attributes().namedItem("x").nodeValue().toInt(),
									node.attributes().namedItem("y").nodeValue().toInt(),
									node.attributes().namedItem("w").nodeValue().toInt(),
									node.attributes().namedItem("h").nodeValue().toInt());

				if(window != this)
					((SoSSubWindow*)window)->setAllowShow(node.attributes().namedItem("visible").nodeValue().toInt());
			}
		}

		QDomElement MainWindow::getNode(QString name, QDomDocument *doc, QDomNode *parent)
		{
			QDomElement node = parent->firstChildElement(name);
			if(node.isNull())
			{
				node = doc->createElement(name);
				parent->appendChild(node);
			}
			return node;
		}

		void MainWindow::processPromo()
		{
			if(!promoShown)
			{
				timesLaunched++;
				if(timesLaunched >= SOS_LAUNCHES_TO_PROMO)
				{
					sosContext->SongControl->stop();
					promoShown = true;
					tutorial.setDocumentName("promo");
					tutorial.setPage(0);
					tutorial.show();
				}
			}
		}

	}
}
