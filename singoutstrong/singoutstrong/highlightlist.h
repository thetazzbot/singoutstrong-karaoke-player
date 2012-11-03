/** @file highlightlist.h
 * Header file with the HighlightList class
*/

#ifndef PlaylistWIDGET_H
#define PlaylistWIDGET_H

#include <QListWidget>
#include <QtGui>

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
		/**
		 * @brief A list widget that allows for highlighting an item independently of QListWidget's currentItem, currentRow, etc.
		 *
		 * This is used to show which item is actually used by the application. \n
		 * For instance the user can click on another song, and the item will be marked the way QListWidget does this
		 * normally. \n
		 * But since a new song is not loaded until an item is doubleclicked, the currently loaded is highlighted, using
		 * additional properties stored by the HighlightList
		 *
		 */
		class HighlightList : public QListWidget
		{
				Q_OBJECT

				Q_PROPERTY(QColor highlightedItemColor READ getHighlightedItemColor WRITE setHighlightedItemColor)
				Q_PROPERTY(QString highlightedItemFont READ getHighlightedItemFont WRITE setHighlightedItemFont)

			public:
				explicit HighlightList(QWidget *parent = 0);

				/**
				 * @brief Gets the color of the highlighted item
				 *
				 * @return QColor Highlighted item color
				 */
				QColor getHighlightedItemColor();

				/**
				 * @brief Sets the color of the highlighted item
				 *
				 * @param color New highlighted item color
				 */
				void setHighlightedItemColor(QColor color);

				/**
				 * @brief Gets the font of the highlighted item
				 *
				 * @return QString Highlighted item font
				 */
				QString getHighlightedItemFont();

				/**
				 * @brief Sets the font of the highlighted item
				 *
				 * @param f New highlighted item font
				 */
				void setHighlightedItemFont(QString f);

				/**
				 * @brief Gets the previously highlighted item
				 *
				 * Storing the previously highlighted item is necessary if an item can be deleted by the user, but
				 * we still want moving to the next and previous item to work properly. \n
				 * Used by the rewind and fast forward buttons.
				 *
				 * @return int The previously highlighted item's index
				 */
				int getLastHighlightedItem();

				/**
				 * @brief Sets the previously highlighted item
				 *
				 * Storing the previously highlighted item is necessary if an item can be deleted by the user, but
				 * we still want moving to the next and previous item to work properly. \n
				 * Used by the rewind and fast forward buttons.
				 *
				 * @param index The previously highlighted item's new index
				 */
				void setLastHighlightedItem(int index);

				/**
				 * @brief Gets the currently highlighted item
				 *
				 * @return int The currently highlighted item's index
				 */
				int getHighlightedItem();

				/**
				 * @brief Sets the currently highlighted item
				 *
				 * @param index The currently highlighted item's new index
				 */
				void setHighlightedItem(int index);

			protected:
				QColor highlightedItemColorVar; /**< @brief Variable storing the highlighted item's color */
				QFont highlightedItemFontVar;	/**< @brief Variable storing the highlighted item's font */

				int lastHighlightedItem;		/**< @brief The previously highlighted item's index */

			signals:

			public slots:

		};
	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // PlaylistWIDGET_H
