#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QString>
#include <QFile>

/*!
 *  \addtogroup SoS
 *  @{
 */

//! Main SingOutStrong namespace
namespace SoS
{
	/*!
	 *  \addtogroup QtGui
	 *  @{
	 */

	//! User Interface
	namespace QtGui
	{

		class SkinManager
		{
			private:
				QString skinName;
				QString styleSheet;

			public:
				SkinManager();

				QString getSkinName() const;
				QString getFileFromSkin(QString file) const;
				QString getStyleSheet() const;

				void setSkin(QString name);
		};

	}  /*! @} End of Doxygen Group SoS*/
} /*! @} End of Doxygen Group QtGui*/

#endif // SKINMANAGER_H
