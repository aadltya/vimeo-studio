#pragma once

#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "screen_capture.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStreaming();
    void stopStreaming();
    void addScene();
    void addSource();
    void configurePrivacySettings();

private:
    void createMenuBar();
    void createToolBar();
    void createDockWindows();
    void createStatusBar();
    void setupCentralWidget();

    // Dock widgets
    QDockWidget *scenesDock;
    QDockWidget *sourcesDock;
    QDockWidget *privacySettingsDock;

    // Widgets
    QListWidget *scenesList;
    QTreeWidget *sourcesList;
    QWidget *previewWidget;
    QLabel *previewLabel;
    
    // Controls
    QPushButton *startButton;
    QPushButton *stopButton;
    
    // Screen capture
    ScreenCapture *screenCapture;
    QTimer *captureTimer;
    bool isStreaming;
};
