#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <QObject>
#include <QtNetwork>

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
		 * @brief The playlist window
		 *
		 */
		class HttpHandler : public QObject
		{				
				Q_OBJECT
			public:
				enum RequestType{REQUEST_POST, REQUEST_GET};

				explicit HttpHandler(QObject* parent = 0);

				void sendRequest(RequestType type, QUrl url);

				QString getResponse();

			signals:
				void receivedResponse(QString response);
				void responseError(QString error);

			private slots:
				void handleResponse(QNetworkReply *networkReply);

			private:
				QNetworkAccessManager networkManager;
				QString response;

		};

	}  /*! @} End of Doxygen Group Core*/
} /*! @} End of Doxygen Group QtGui*/

#endif // HTTPHANDLER_H
