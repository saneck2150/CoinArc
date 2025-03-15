#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "binance/BinanceRestApi.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("CoinArc (Console Version)");
    parser.addHelpOption();
    parser.addPositionalArgument("symbol", "Crypto pair symbol, e.g. BTCUSDT");

    parser.process(app);

    QString symbol = "BTCUSDT";
    if (!parser.positionalArguments().isEmpty()) {
        symbol = parser.positionalArguments().first().toUpper();
    }

    BinanceRestApi binanceRest;

    QObject::connect(&binanceRest, &BinanceRestApi::currentPriceReceived,
                     [&](const QString &sym, double price) {
        qInfo() << "Current price for" << sym << "is" << price;

        QCoreApplication::quit();
    });

    binanceRest.requestCurrentPrice(symbol);

    return app.exec();
}
