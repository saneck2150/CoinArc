#include "BinanceWebSocketApi.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

BinanceWebSocketApi::BinanceWebSocketApi(QObject *parent)
    : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected,
            this, &BinanceWebSocketApi::onConnected);

    connect(&m_webSocket,
            QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this,
            &BinanceWebSocketApi::onError);
}

void BinanceWebSocketApi::connectToPriceStream(const QString &symbol)
{
    m_currentSymbol = symbol;
    QString wsUrl = QString("wss://stream.binance.com:9443/ws/%1@trade")
                        .arg(symbol.toLower());
    m_webSocket.open(QUrl(wsUrl));
}

void BinanceWebSocketApi::onConnected()
{
    qDebug() << "[WebSocket] Connected to" << m_currentSymbol;

    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &BinanceWebSocketApi::onTextMessageReceived);
}

void BinanceWebSocketApi::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) {
        return; 
    }

    QJsonObject obj = doc.object();
    double price = 0.0;
    if (obj.contains("p")) {
        price = obj.value("p").toString().toDouble();
    } else {
        return;
    }
    emit priceUpdated(m_currentSymbol, price);
}

void BinanceWebSocketApi::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    QString errString = m_webSocket.errorString();
    qWarning() << "[WebSocket] Error:" << errString;
    emit socketError(errString);
}
