#include "skinmanager.h"

namespace SoS
{
	namespace QtGui
	{
		SkinManager::SkinManager() :
			skinName("default"),
			styleSheet("")
		{
		}

		void SkinManager::setSkin(QString name)
		{
			skinName = name.isEmpty() ? "default" : name;

			QFile file(QString("skins/%1/style.css").arg(skinName));

			if(!file.exists())
				return;

			file.open(QIODevice::ReadOnly);
			styleSheet = file.readAll();
			file.close();
		}

		QString SkinManager::getFileFromSkin(QString file) const
		{
			return QString("./skins/%1/%2").arg(skinName).arg(file);
		}

		QString SkinManager::getStyleSheet() const
		{
			return styleSheet;
		}

		QString SkinManager::getSkinName() const
		{
			return skinName;
		}
	}
}
