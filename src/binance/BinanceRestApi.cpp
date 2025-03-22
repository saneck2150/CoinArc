#include "BinanceRestApi.hpp"
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

BinanceOhlcRestApi::BinanceOhlcRestApi(QObject *parent)
    : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished,
            this, &BinanceOhlcRestApi::onReplyFinished);
}

void BinanceOhlcRestApi::requestLast10Ohlc(const QString &symbol, const QString &interval)
{
    QUrl url("https://api.binance.com/api/v3/klines");
    QUrlQuery query;
    query.addQueryItem("symbol",   symbol);
    query.addQueryItem("interval", interval);
    query.addQueryItem("limit",    QString::number(10));
    url.setQuery(query);

    QNetworkRequest request(url);
    m_networkManager.get(request);
}

void BinanceOhlcRestApi::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        const QString err = QString("OHLC request error: %1").arg(reply->errorString());
        qWarning() << err;
        emit requestError(err);
        reply->deleteLater();
        return;
    }
    QByteArray data = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        const QString err = QString("Wrong OHLC JSON format: %1").arg(QString::fromUtf8(data));
        qWarning() << err;
        emit requestError(err);
        return;
    }

    QJsonArray arr = doc.array();
    QList<OhlcRecord> list;
    list.reserve(arr.size());
    for (const QJsonValue &val : arr) {
        if (!val.isArray()) continue;
        QJsonArray candle = val.toArray();
        if (candle.size() < 6) continue;

        OhlcRecord rec;
        rec.openTime = static_cast<qint64>(candle.at(0).toDouble());
        rec.open     = candle.at(1).toString().toDouble();
        rec.high     = candle.at(2).toString().toDouble();
        rec.low      = candle.at(3).toString().toDouble();
        rec.close    = candle.at(4).toString().toDouble();
        rec.volume   = candle.at(5).toString().toDouble();
        list.append(rec);
    }

    emit ohlcReceived(list);
}
