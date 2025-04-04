#pragma once

#include <QObject>
#include <QWebSocket>

struct KlineData {
    qint64 openTime;
    qint64 closeTime;
    QString symbol;
    QString interval;
    double open;
    double close;
    double high;
    double low;
    double volume;
    bool isKlineClosed; 
};

class BinanceKlineWebSocketApi : public QObject
{
    Q_OBJECT
public:
    explicit BinanceKlineWebSocketApi(QObject *parent = nullptr);
    void connectToKlineStream(const QString &symbol, const QString &interval);

signals:
    void klineUpdated(const KlineData &kline);
    void socketError(const QString &errorMsg);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
    QString m_symbol;
    QString m_interval;
};
