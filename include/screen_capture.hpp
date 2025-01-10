#pragma once

#include <opencv2/opencv.hpp>
#include <memory>
#include <windows.h>

class ScreenCapture {
public:
    ScreenCapture();
    ~ScreenCapture();

    bool initialize();
    cv::Mat captureScreen();
    
private:
    HWND desktopHwnd;
    HDC desktopDC;
    HDC captureDC;
    HBITMAP captureBitmap;
    int screenWidth;
    int screenHeight;

    void cleanup();
};
