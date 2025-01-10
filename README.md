# PrivacyScreen

A real-time intelligent screen privacy tool that automatically detects and blurs sensitive information during screen sharing and streaming.

## Features
- Real-time screen capture with minimal latency
- AI-powered detection of sensitive information
- Automatic blurring of personal data (messages, notifications, phone numbers)
- Virtual camera output for streaming platforms
- Compatible with major streaming and conferencing platforms
- Low CPU/GPU resource usage

## Requirements
- Windows 10 or later
- CMake 3.15+
- Visual Studio 2019 or later with C++17 support
- OpenCV 4.x
- Qt 6.x
- CUDA toolkit (optional, for GPU acceleration)

## Building from Source
1. Clone the repository
2. Create a build directory:
```bash
mkdir build
cd build
```
3. Configure with CMake:
```bash
cmake ..
```
4. Build the project:
```bash
cmake --build . --config Release
```

## Usage
1. Launch PrivacyScreen
2. Select areas or types of content to blur
3. Start your preferred streaming/conferencing application
4. Select "PrivacyScreen Camera" as your video source

## License
This project is licensed under the MIT License - see the LICENSE file for details.
