#include "httphandler.h"

namespace SoS
{
	namespace QtGui
	{

		HttpHandler::HttpHandler(QObject *parent) :
			QObject(parent)
		{
			connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
					this, SLOT(handleResponse(QNetworkReply*)));
		}

		void HttpHandler::postRequest(QString url)
		{
			response = "";
			QNetworkRequest request(url);
			request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

			QByteArray data;
			QUrl params;

			params.addQueryItem("expression","Nightwish");
			params.addQueryItem("search_cat","");

			data = params.encodedQuery();
			networkManager.post(request, data);
		}

		void HttpHandler::handleResponse(QNetworkReply *networkReply)
		{
			QUrl url = networkReply->url();
			if (!networkReply->error()) {
				QStringList choices;
				QStringList hits;

				response = networkReply->readAll();
				emit receivedResponse(response);
			}
		}

	}
}
