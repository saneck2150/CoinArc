#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include "BinanceRestApi.hpp"
#include "BinanceWebSocketApi.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_chart(nullptr),
      m_series(nullptr),
      m_chartView(nullptr),
      m_axisX(nullptr),
      m_axisY(nullptr),
      m_restApi(nullptr),
      m_wsApi(nullptr)
{
    setupUi();
    initRestRequest();
    initWebSocketStream();
}

MainWindow::~MainWindow()
{
    if (m_restApi)  delete m_restApi;
    if (m_wsApi)    delete m_wsApi;
}

void MainWindow::setupUi()
{
    m_chart = new QChart();
    m_series = new QLineSeries(m_chart);
    m_chart->addSeries(m_series);

    m_axisX = new QValueAxis();
    m_axisX->setTitleText("Тики (условная ось времени)");
    m_axisX->setLabelFormat("%d");
    m_axisX->setRange(0, 50); 

    m_axisY = new QValueAxis();
    m_axisY->setTitleText("Цена");
    m_axisY->setLabelFormat("%.2f");
    m_axisY->setRange(0, 30000); 

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    m_chart->setTitle("График цены Binance (BTCUSDT)");

    m_chartView = new QChartView(m_chart, this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(m_chartView);

    resize(800, 600);
}

void MainWindow::initRestRequest()
{
    m_restApi = new BinanceRestApi(this);

    connect(m_restApi, &BinanceRestApi::currentPriceReceived,
            this, &MainWindow::onRestPriceReceived);

    m_restApi->requestCurrentPrice("BTCUSDT");
}

void MainWindow::initWebSocketStream()
{
    m_wsApi = new BinanceWebSocketApi(this);

    connect(m_wsApi, &BinanceWebSocketApi::priceUpdated,
            this, &MainWindow::onWebSocketPriceUpdated);

    connect(m_wsApi, &BinanceWebSocketApi::socketError,
            this, &MainWindow::onWebSocketError);

    m_wsApi->connectToPriceStream("BTCUSDT");
}

void MainWindow::onRestPriceReceived(const QString &symbol, double price)
{
    qDebug() << "[REST]" << symbol << " => " << price;
    m_series->append(m_xCounter, price);
    m_xCounter++;

    if (m_xCounter > 50) {
        m_axisX->setRange(m_xCounter - 50, m_xCounter);
    }

    if (price > m_axisY->max()) {
        m_axisY->setMax(price * 1.1);
    } else if (price < m_axisY->min()) {
        m_axisY->setMin(price * 0.9);
    }
}
void MainWindow::onWebSocketPriceUpdated(const QString &symbol, double price)
{
    qDebug() << "[WebSocket]" << symbol << " => " << price;

    m_series->append(m_xCounter, price);
    m_xCounter++;

    if (m_xCounter > 50) {
        m_axisX->setRange(m_xCounter - 50, m_xCounter);
    }

    if (price > m_axisY->max()) {
        m_axisY->setMax(price * 1.1);
    } else if (price < m_axisY->min()) {
        m_axisY->setMin(price * 0.9);
    }
}

void MainWindow::onWebSocketError(const QString &errorMsg)
{
    QMessageBox::warning(this,
                         tr("WebSocket ошибка"),
                         tr("Ошибка WebSocket: %1").arg(errorMsg));
}
