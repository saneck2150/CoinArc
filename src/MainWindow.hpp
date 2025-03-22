#pragma once

#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QChart;
QT_END_NAMESPACE

class BinanceWebSocketApi;
class BinanceRestApi;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
    void initRestRequest();    
    void initWebSocketStream(); 

private slots:
    void onRestPriceReceived(const QString &symbol, double price);
    void onWebSocketPriceUpdated(const QString &symbol, double price);
    void onWebSocketError(const QString &errorMsg);

private:
    QChart        *m_chart;
    QLineSeries   *m_series;
    QChartView    *m_chartView;
    QValueAxis              *m_axisX;
    QValueAxis              *m_axisY;

    int m_xCounter = 0;

    BinanceRestApi      *m_restApi;
    BinanceWebSocketApi *m_wsApi;
};
