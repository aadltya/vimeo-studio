#include "main_window.hpp"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , screenCapture(new ScreenCapture())
    , captureTimer(new QTimer(this))
    , isStreaming(false)
{
    setWindowTitle("PrivacyScreen Studio");
    resize(1280, 720);

    createMenuBar();
    createToolBar();
    createDockWindows();
    createStatusBar();
    setupCentralWidget();

    if (!screenCapture->initialize()) {
        QMessageBox::critical(this, "Error", "Failed to initialize screen capture!");
    }

    connect(captureTimer, &QTimer::timeout, this, [this]() {
        if (isStreaming) {
            cv::Mat screen = screenCapture->captureScreen();
            if (!screen.empty()) {
                // Convert OpenCV mat to QImage
                cv::Mat rgb;
                cv::cvtColor(screen, rgb, cv::COLOR_BGR2RGB);
                QImage qimg(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
                previewLabel->setPixmap(QPixmap::fromImage(qimg.scaled(
                    previewLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            }
        }
    });
}

MainWindow::~MainWindow() {
    delete screenCapture;
}

void MainWindow::createMenuBar() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Exit"), this, &QWidget::close);

    QMenu *streamMenu = menuBar()->addMenu(tr("&Stream"));
    streamMenu->addAction(tr("&Start Streaming"), this, &MainWindow::startStreaming);
    streamMenu->addAction(tr("Stop Streaming"), this, &MainWindow::stopStreaming);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(tr("Privacy Settings"), this, &MainWindow::configurePrivacySettings);
}

void MainWindow::createToolBar() {
    QToolBar *mainToolBar = addToolBar(tr("Main"));
    
    startButton = new QPushButton(tr("Start Streaming"), this);
    stopButton = new QPushButton(tr("Stop Streaming"), this);
    stopButton->setEnabled(false);
    
    mainToolBar->addWidget(startButton);
    mainToolBar->addWidget(stopButton);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startStreaming);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopStreaming);
}

void MainWindow::createDockWindows() {
    // Scenes dock
    scenesDock = new QDockWidget(tr("Scenes"), this);
    scenesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    scenesList = new QListWidget(scenesDock);
    scenesList->addItem("Main Scene");
    scenesDock->setWidget(scenesList);
    addDockWidget(Qt::LeftDockWidgetArea, scenesDock);

    // Sources dock
    sourcesDock = new QDockWidget(tr("Sources"), this);
    sourcesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    sourcesList = new QTreeWidget(sourcesDock);
    sourcesList->setHeaderLabels(QStringList() << "Source" << "Type");
    sourcesList->addTopLevelItem(new QTreeWidgetItem(QStringList() << "Screen Capture" << "Display Capture"));
    sourcesDock->setWidget(sourcesList);
    addDockWidget(Qt::LeftDockWidgetArea, sourcesDock);

    // Privacy Settings dock
    privacySettingsDock = new QDockWidget(tr("Privacy Settings"), this);
    QWidget *privacyWidget = new QWidget();
    QVBoxLayout *privacyLayout = new QVBoxLayout(privacyWidget);
    
    privacyLayout->addWidget(new QLabel("Blur Sensitivity:"));
    privacyLayout->addWidget(new QSlider(Qt::Horizontal));
    privacyLayout->addWidget(new QCheckBox("Blur Notifications"));
    privacyLayout->addWidget(new QCheckBox("Blur Phone Numbers"));
    privacyLayout->addWidget(new QCheckBox("Blur Email Addresses"));
    
    privacyWidget->setLayout(privacyLayout);
    privacySettingsDock->setWidget(privacyWidget);
    addDockWidget(Qt::RightDockWidgetArea, privacySettingsDock);
}

void MainWindow::setupCentralWidget() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    previewLabel = new QLabel(this);
    previewLabel->setMinimumSize(640, 360);
    previewLabel->setAlignment(Qt::AlignCenter);
    previewLabel->setStyleSheet("QLabel { background-color: #333333; }");
    
    layout->addWidget(previewLabel);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::startStreaming() {
    isStreaming = true;
    captureTimer->start(33); // ~30 FPS
    startButton->setEnabled(false);
    stopButton->setEnabled(true);
    statusBar()->showMessage(tr("Streaming"));
}

void MainWindow::stopStreaming() {
    isStreaming = false;
    captureTimer->stop();
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::addScene() {
    // TODO: Implement scene addition
}

void MainWindow::addSource() {
    // TODO: Implement source addition
}

void MainWindow::configurePrivacySettings() {
    // TODO: Implement privacy settings configuration
}
