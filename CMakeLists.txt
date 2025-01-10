cmake_minimum_required(VERSION 3.15)
project(PrivacyScreen VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# Add executable
add_executable(PrivacyScreen
    src/main.cpp
    src/screen_capture.cpp
    src/main_window.cpp
    include/screen_capture.hpp
    include/main_window.hpp
)

# Include directories
target_include_directories(PrivacyScreen PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(PrivacyScreen PRIVATE
    ${OpenCV_LIBS}
    Qt6::Core
    Qt6::Widgets
)
