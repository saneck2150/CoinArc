#ifndef BINANCE_REST_API_H
#define BINANCE_REST_API_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class BinanceRestApi : public QObject
{
    Q_OBJECT
public:
    explicit BinanceRestApi(QObject* parent = nullptr);

    void requestCurrentPrice(const QString& symbol);

signals:
    void currentPriceReceived(const QString& symbol, double price);

private slots:
    void onPriceReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_networkManager;
};

#endif // BINANCE_REST_API_H