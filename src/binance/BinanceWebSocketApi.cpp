#include "BinanceWebSocketApi.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>

BinanceKlineWebSocketApi::BinanceKlineWebSocketApi(QObject *parent)
    : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected,
            this, &BinanceKlineWebSocketApi::onConnected);

    connect(&m_webSocket,
            QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &BinanceKlineWebSocketApi::onError);
}

void BinanceKlineWebSocketApi::connectToKlineStream(const QString &symbol, const QString &interval)
{
    m_symbol   = symbol;
    m_interval = interval;

    // Пример: wss://stream.binance.com:9443/ws/btcusdt@kline_1m
    QString wsUrl = QString("wss://stream.binance.com:9443/ws/%1@kline_%2")
                        .arg(symbol.toLower())
                        .arg(interval);
    m_webSocket.open(QUrl(wsUrl));
}

void BinanceKlineWebSocketApi::onConnected()
{
    qDebug() << "[Kline WS] Connected to" << m_symbol << "interval:" << m_interval;
    // Подписываемся на сообщения
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &BinanceKlineWebSocketApi::onTextMessageReceived);
}

void BinanceKlineWebSocketApi::onTextMessageReceived(const QString &message)
{
    // Парсим JSON
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    // eventType = obj.value("e") => "kline"
    // symbol    = obj.value("s") => "BTCUSDT", но нам важнее поле "k"
    if (!obj.contains("k")) return;

    QJsonObject kObj = obj.value("k").toObject();

    // Извлекаем нужные поля
    KlineData kdata;
    kdata.openTime      = static_cast<qint64>(kObj.value("t").toDouble());
    kdata.closeTime     = static_cast<qint64>(kObj.value("T").toDouble());
    kdata.symbol        = kObj.value("s").toString();
    kdata.interval      = kObj.value("i").toString();
    kdata.open          = kObj.value("o").toString().toDouble();
    kdata.close         = kObj.value("c").toString().toDouble();
    kdata.high          = kObj.value("h").toString().toDouble();
    kdata.low           = kObj.value("l").toString().toDouble();
    kdata.volume        = kObj.value("v").toString().toDouble();
    kdata.isKlineClosed = kObj.value("x").toBool();

    emit klineUpdated(kdata);
}

void BinanceKlineWebSocketApi::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    QString errString = m_webSocket.errorString();
    qWarning() << "[Kline WS] Error:" << errString;
    emit socketError(errString);
}
