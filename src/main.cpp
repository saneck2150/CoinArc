#include <QCoreApplication>
#include <QCommandLineParser>
#include "binance/BinanceRunner.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("ConsoleKlineApp");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Binance Kline console demo");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption symbolOption({"s", "symbol"}, "Symbol (e.g. BTCUSDT)", "symbol", "BTCUSDT");
    QCommandLineOption intervalOption({"i", "interval"}, "Interval (e.g. 1m,15m,1h)", "interval", "1m");

    parser.addOption(symbolOption);
    parser.addOption(intervalOption);

    parser.process(app);

    const QString symbol = parser.value(symbolOption).toUpper();
    const QString interval = parser.value(intervalOption);

    runApp(symbol, interval, &app);

    return app.exec();
}
