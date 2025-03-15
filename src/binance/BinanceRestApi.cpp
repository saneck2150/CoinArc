#include "BinanceRestApi.hpp"
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

BinanceRestApi::BinanceRestApi(QObject *parent)
    : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished,
            this, &BinanceRestApi::onPriceReplyFinished);
}

void BinanceRestApi::requestCurrentPrice(const QString &symbol)
{
    QUrl url("https://api.binance.com/api/v3/ticker/price");

    QUrlQuery query;
    query.addQueryItem("symbol", symbol);
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}

void BinanceRestApi::onPriceReplyFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Price reqest error: " << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    if (!doc.isObject()) {
        qWarning() << "Wrong JSON format: " << responseData;
        return;
    }

    QJsonObject obj = doc.object();
    QString symbol = obj.value("symbol").toString();
    double price   = obj.value("price").toString().toDouble();

    emit currentPriceReceived(symbol, price);
}