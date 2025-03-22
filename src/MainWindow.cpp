#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

// Подключаем заголовки Binance API (предположительно лежат в binance/)
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
    // Освобождаем динамически созданные объекты,
    // хотя Qt обычно сам чистит «владение» QObject-ами при родителе QMainWindow.
    if (m_restApi)  delete m_restApi;
    if (m_wsApi)    delete m_wsApi;
}

void MainWindow::setupUi()
{
    // Создаём объекты графика:
    m_chart = new QChart();
    m_series = new QLineSeries(m_chart);
    m_chart->addSeries(m_series);

    // Настраиваем оси:
    m_axisX = new QValueAxis();
    m_axisX->setTitleText("Тики (условная ось времени)");
    m_axisX->setLabelFormat("%d");
    m_axisX->setRange(0, 50); // диапазон X от 0 до 50, при достижении придётся двигать

    m_axisY = new QValueAxis();
    m_axisY->setTitleText("Цена");
    m_axisY->setLabelFormat("%.2f");
    m_axisY->setRange(0, 30000); // для BTCUSDT можно задать более широкий диапазон

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    // Линию тоже привязываем к осям:
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    m_chart->setTitle("График цены Binance (BTCUSDT)");

    // Оборачиваем в QChartView:
    m_chartView = new QChartView(m_chart, this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    // Размещаем QChartView в центральной области MainWindow
    setCentralWidget(m_chartView);

    // Увеличиваем минимальный размер окна для наглядности
    resize(800, 600);
}

void MainWindow::initRestRequest()
{
    // Создаём объект REST API:
    m_restApi = new BinanceRestApi(this);

    // Связываем сигнал получения текущей цены с нашим слотом
    connect(m_restApi, &BinanceRestApi::currentPriceReceived,
            this, &MainWindow::onRestPriceReceived);

    // Делаем запрос цены на BTCUSDT (можете легко заменить на любую другую пару)
    m_restApi->requestCurrentPrice("BTCUSDT");
}

void MainWindow::initWebSocketStream()
{
    // Создаём WebSocket API:
    m_wsApi = new BinanceWebSocketApi(this);

    // При обновлении цены по WebSocket добавляем точку на график
    connect(m_wsApi, &BinanceWebSocketApi::priceUpdated,
            this, &MainWindow::onWebSocketPriceUpdated);

    // Обработка ошибки WebSocket:
    connect(m_wsApi, &BinanceWebSocketApi::socketError,
            this, &MainWindow::onWebSocketError);

    // Подключаемся к стриму цены BTCUSDT
    m_wsApi->connectToPriceStream("BTCUSDT");
}

// Слот, который вызывается при ответе REST (однократно, т.к. запрос «разовый»)
void MainWindow::onRestPriceReceived(const QString &symbol, double price)
{
    qDebug() << "[REST]" << symbol << " => " << price;
    // Добавим «начальную» точку на график
    m_series->append(m_xCounter, price);
    m_xCounter++;

    // Можем «подвинуть» диапазон по оси X, если нужно
    if (m_xCounter > 50) {
        m_axisX->setRange(m_xCounter - 50, m_xCounter);
    }

    // Аналогично, если цена внезапно высока/низка, можно подвинуть ось Y
    if (price > m_axisY->max()) {
        m_axisY->setMax(price * 1.1);
    } else if (price < m_axisY->min()) {
        m_axisY->setMin(price * 0.9);
    }
}

// Слот, который вызывается при поступлении новой цены по WebSocket (постоянно)
void MainWindow::onWebSocketPriceUpdated(const QString &symbol, double price)
{
    qDebug() << "[WebSocket]" << symbol << " => " << price;

    // Добавляем точку
    m_series->append(m_xCounter, price);
    m_xCounter++;

    // Движем ось X, если превысили её текущий верхний предел
    if (m_xCounter > 50) {
        m_axisX->setRange(m_xCounter - 50, m_xCounter);
    }

    // Аналогично двигаем ось Y
    if (price > m_axisY->max()) {
        m_axisY->setMax(price * 1.1);
    } else if (price < m_axisY->min()) {
        m_axisY->setMin(price * 0.9);
    }
}

void MainWindow::onWebSocketError(const QString &errorMsg)
{
    // Покажем пользователю сообщение об ошибке
    QMessageBox::warning(this,
                         tr("WebSocket ошибка"),
                         tr("Ошибка WebSocket: %1").arg(errorMsg));
}
