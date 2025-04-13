#include "BinanceRunner.hpp"
#include <QTimer>
#include <QDebug>
#include "BinanceRestApi.hpp"
#include "BinanceWebSocketApi.hpp"

void runApp(const QString &symbol, const QString &interval, QCoreApplication *app)
{
    auto restApi = new BinanceOhlcRestApi(app);
    QObject::connect(restApi, &BinanceOhlcRestApi::ohlcReceived,
                     [=](const QList<OhlcRecord> &records){
        qInfo() << "=== Last 10 OHLC for" << symbol << "===";
        for (int i = 0; i < records.size(); ++i) {
            const auto &r = records.at(i);
            qInfo() << i << ") OpenTime:" << r.openTime
                    << "O:" << r.open
                    << "H:" << r.high
                    << "L:" << r.low
                    << "C:" << r.close
                    << "Volume:" << r.volume;
        }
        qInfo() << "=========================================";
    });

    QObject::connect(restApi, &BinanceOhlcRestApi::requestError,
                     [](const QString &err){
        qWarning() << "REST Error:" << err;
    });

    restApi->requestLast10Ohlc(symbol, interval);

    auto wsApi = new BinanceKlineWebSocketApi(app);
    QObject::connect(wsApi, &BinanceKlineWebSocketApi::klineUpdated,
                     [](const KlineData &kline){
        qInfo() << "[Kline WS]"
                << kline.symbol << "(" << kline.interval << ")"
                << "Open=" << kline.open
                << "High=" << kline.high
                << "Low=" << kline.low
                << "Close=" << kline.close
                << (kline.isKlineClosed ? "[closed]" : "[forming]");
    });

    QObject::connect(wsApi, &BinanceKlineWebSocketApi::socketError,
                     [](const QString &err){
        qWarning() << "WS Error:" << err;
    });

    wsApi->connectToKlineStream(symbol, interval);

    QTimer::singleShot(3 * 60 * 1000, app, &QCoreApplication::quit);
}