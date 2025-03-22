#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>

// Структура для хранения одной записи OHLC
struct OhlcRecord {
    qint64 openTime;   // Метка времени открытия свечи
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
    
    // Запросить последние 10 OHLC. Параметры:
    // symbol:  тикер (например, BTCUSDT)
    // interval: интервал (например, 1m, 15m, 1h, 1d и т.д.)
    void requestLast10Ohlc(const QString &symbol, const QString &interval = "1m");

signals:
    // Возвращаем список (QList) OhlcRecord по завершении
    void ohlcReceived(const QList<OhlcRecord> &records);
    // В случае ошибки отправим сигнал
    void requestError(const QString &errorMsg);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};
