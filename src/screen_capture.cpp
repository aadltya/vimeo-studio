#include "screen_capture.hpp"

ScreenCapture::ScreenCapture() 
    : desktopHwnd(nullptr), desktopDC(nullptr), captureDC(nullptr), captureBitmap(nullptr) {
}

ScreenCapture::~ScreenCapture() {
    cleanup();
}

bool ScreenCapture::initialize() {
    desktopHwnd = GetDesktopWindow();
    desktopDC = GetDC(desktopHwnd);
    
    if (!desktopDC) {
        return false;
    }

    captureDC = CreateCompatibleDC(desktopDC);
    if (!captureDC) {
        cleanup();
        return false;
    }

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    captureBitmap = CreateCompatibleBitmap(desktopDC, screenWidth, screenHeight);
    if (!captureBitmap) {
        cleanup();
        return false;
    }

    SelectObject(captureDC, captureBitmap);
    return true;
}

cv::Mat ScreenCapture::captureScreen() {
    BitBlt(captureDC, 0, 0, screenWidth, screenHeight, desktopDC, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -screenHeight;  // Top-down image
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;

    cv::Mat screen(screenHeight, screenWidth, CV_8UC3);
    GetDIBits(captureDC, captureBitmap, 0, screenHeight, screen.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    
    return screen;
}

void ScreenCapture::cleanup() {
    if (captureBitmap) {
        DeleteObject(captureBitmap);
        captureBitmap = nullptr;
    }
    if (captureDC) {
        DeleteDC(captureDC);
        captureDC = nullptr;
    }
    if (desktopDC) {
        ReleaseDC(desktopHwnd, desktopDC);
        desktopDC = nullptr;
    }
}
