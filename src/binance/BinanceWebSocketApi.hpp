#pragma once

#include <QObject>
#include <QWebSocket>
#include <QAbstractSocket> 

class BinanceWebSocketApi : public QObject
{
    Q_OBJECT
public:
    explicit BinanceWebSocketApi(QObject *parent = nullptr);
    void connectToPriceStream(const QString &symbol);

signals:
    void priceUpdated(const QString &symbol, double price);
    void socketError(const QString &errorMessage);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
    QString m_currentSymbol; 
};
