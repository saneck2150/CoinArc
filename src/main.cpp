#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QTimer>

#include "BinanceRestApi.hpp"
#include "BinanceWebSocketApi.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("ConsoleKlineApp");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Binance Kline console demo");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption symbolOption(QStringList() << "s" << "symbol",
                                    "Symbol (e.g. BTCUSDT)",
                                    "symbol",
                                    "BTCUSDT");
    parser.addOption(symbolOption);

    QCommandLineOption intervalOption(QStringList() << "i" << "interval",
                                      "Interval (e.g. 1m,15m,1h)",
                                      "interval",
                                      "1m");
    parser.addOption(intervalOption);

    parser.process(app);

    const QString symbol   = parser.value(symbolOption).toUpper();
    const QString interval = parser.value(intervalOption);
    BinanceOhlcRestApi restApi;
    QObject::connect(&restApi, &BinanceOhlcRestApi::ohlcReceived,
                     [&](const QList<OhlcRecord> &records){
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
    QObject::connect(&restApi, &BinanceOhlcRestApi::requestError,
                     [&](const QString &err){
        qWarning() << "REST Error:" << err;
    });

    restApi.requestLast10Ohlc(symbol, interval);
    BinanceKlineWebSocketApi wsApi;
    QObject::connect(&wsApi, &BinanceKlineWebSocketApi::klineUpdated,
                     [&](const KlineData &kline){
        qInfo() << "[Kline WS]"
                << kline.symbol << "(" << kline.interval << ")"
                << "Open=" << kline.open
                << "High=" << kline.high
                << "Low=" << kline.low
                << "Close=" << kline.close
                << (kline.isKlineClosed ? "[closed]" : "[forming]");
    });
    QObject::connect(&wsApi, &BinanceKlineWebSocketApi::socketError,
                     [&](const QString &err){
        qWarning() << "WS Error:" << err;
    });

    wsApi.connectToKlineStream(symbol, interval);
    QTimer::singleShot(3 * 60 * 1000, &app, &QCoreApplication::quit);

    return app.exec();
}
