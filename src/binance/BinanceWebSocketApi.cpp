#include "BinanceWebSocketApi.hpp"
#include <QDebug>

BinanceWebSocketApi::BinanceWebSocketApi(QObject* parent)
    : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected,
            this, &BinanceWebSocketApi::onConnected);

    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &BinanceWebSocketApi::onTextMessageReceived);
}

void BinanceWebSocketApi::connectToPriceStream(const QString &symbol)
{
    m_symbol = symbol.toUpper();
    QString endpoint = QString("wss://stream.binance.com:9443/ws/%1@ticker")
                            .arg(symbol.toLower());
    QUrl url(endpoint);

    qInfo() << "Connecting to WebSocket:" << url.toString();
    m_webSocket.open(url);
}

void BinanceWebSocketApi::onConnected()
{
    qInfo() << "WebSocket connected for symbol:" << m_symbol;
}

void BinanceWebSocketApi::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) {
        qWarning() << "Invalid JSON message from WS:" << message;
        return;
    }
    QJsonObject obj = doc.object();

    double lastPrice = 0.0;
    if (obj.contains("c")) {
        lastPrice = obj.value("c").toString().toDouble();
    } else {
        qWarning() << "No price in JSON message:" << message;
    }

    emit priceUpdated(m_symbol, lastPrice);
}

void BinanceWebSocketApi::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "WebSocket error:" << error << m_webSocket.errorString();
}