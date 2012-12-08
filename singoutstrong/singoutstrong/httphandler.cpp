#include "httphandler.h"

namespace SoS
{
	namespace QtGui
	{

		HttpHandler::HttpHandler(QObject *parent) :
			QObject(parent),
			timerId(0),
			reply(0)
		{
			connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
					this, SLOT(handleResponse(QNetworkReply*)));
		}

		void HttpHandler::timerEvent(QTimerEvent *event)
		{
			if(event->timerId() == timerId)
			{
				reply->abort();
				reply->deleteLater();
				reply = 0;
				killTimer(timerId);
				timerId = 0;

				emit responseError("The request has timed out.");
			}
		}

		void HttpHandler::sendRequest(RequestType type, QUrl url)
		{
			if(!reply)
			{
				QNetworkRequest request(url);
				request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

				if(type == REQUEST_POST) reply = networkManager.post(request, url.encodedQuery());
				else reply = networkManager.get(request);

				timerId = this->startTimer(30000);
			}
		}

		void HttpHandler::handleResponse(QNetworkReply *networkReply)
		{
			networkReply->deleteLater();
			reply = 0;
			killTimer(timerId);
			timerId = 0;
			if (!networkReply->error()) {
				emit receivedResponse(networkReply->readAll());
			}
			else
				emit responseError(networkReply->errorString());
		}

	}
}
