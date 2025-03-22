#pragma once

#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QTimer>

// Включаем пространство имён для QtCharts
QT_BEGIN_NAMESPACE
class QChart;
QT_END_NAMESPACE

// Прототипы используемых классов:
class BinanceWebSocketApi;
class BinanceRestApi;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Методы:
    void setupUi();
    void initRestRequest();     // Можно сразу запросить REST для стартовой цены
    void initWebSocketStream(); // Инициализируем WebSocket подписку

private slots:
    void onRestPriceReceived(const QString &symbol, double price);
    void onWebSocketPriceUpdated(const QString &symbol, double price);
    void onWebSocketError(const QString &errorMsg);

private:
    // Графические элементы:
    QChart        *m_chart;
    QLineSeries   *m_series;
    QChartView    *m_chartView;
    QValueAxis              *m_axisX;
    QValueAxis              *m_axisY;

    // Счётчик для оси X (имитация «временной» шкалы)
    int m_xCounter = 0;

    // Binance API объекты:
    BinanceRestApi      *m_restApi;
    BinanceWebSocketApi *m_wsApi;
};
