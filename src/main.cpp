#include <QApplication>
#include "main_window.hpp"
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "screen_capture.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MainWindow mainWindow;
    
    // Initialize screen capture
    ScreenCapture capture;
    if (!capture.initialize()) {
        return -1;
    }

    // Create a timer for continuous capture
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        cv::Mat screen = capture.captureScreen();
        if (!screen.empty()) {
            cv::imshow("Screen Capture", screen);
            cv::waitKey(1);
        }
    });

    // Start capturing at 30 FPS
    timer.start(33);

    mainWindow.show();
    
    return app.exec();
}
