#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>

struct OhlcRecord {
    qint64 openTime;   
    double open;
    double high;
    double low;
    double close;
    double volume;
};

class BinanceOhlcRestApi : public QObject
{
    Q_OBJECT
public:
    explicit BinanceOhlcRestApi(QObject *parent = nullptr);
    void requestLast10Ohlc(const QString &symbol, const QString &interval = "1m");

signals:
    void ohlcReceived(const QList<OhlcRecord> &records);
    void requestError(const QString &errorMsg);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};
