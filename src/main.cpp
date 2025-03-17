#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QDebug>

#include "binance/BinanceWebSocketApi.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("MyCryptoTracker-WS");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Binance WebSocket Test");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("symbol", "Crypto pair symbol, e.g. BTCUSDT");
    parser.process(app);

    QString symbol = "BTCUSDT";
    if (!parser.positionalArguments().isEmpty()) {
        symbol = parser.positionalArguments().first().toUpper();
    }

    BinanceWebSocketApi wsApi;
    QObject::connect(&wsApi, &BinanceWebSocketApi::priceUpdated,
                     [&](const QString &sym, double price){
        qInfo() << "Real-time price for" << sym << ":" << price;
    });

    wsApi.connectToPriceStream(symbol);
    QTimer::singleShot(100000, &app, &QCoreApplication::quit);
    return app.exec();
}