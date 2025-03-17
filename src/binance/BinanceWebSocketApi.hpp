#ifndef BINANCE_WEBSOCKET_API_H
#define BINANCE_WEBSOCKET_API_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class BinanceWebSocketApi : public QObject
{
    Q_OBJECT
public:
    explicit BinanceWebSocketApi(QObject* parent = nullptr);
    void connectToPriceStream(const QString &symbol);

signals:
    void priceUpdated(const QString &symbol, double price);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
    QString m_symbol;
};

#endif // BINANCE_WEBSOCKET_API_H