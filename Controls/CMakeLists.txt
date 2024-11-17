cmake_minimum_required(VERSION 3.25)
project(Controls)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# QT dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

# set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
# add_compile_options(-c -Wall -Wextra -O3 -std=c++23)

qt5_generate_moc(StatusBar/StatusBar.cpp StatusBar/StatusBar.moc)
qt5_generate_moc(ListBox/ListBox.h ListBox/ListBox.moc)

add_executable(${PROJECT_NAME}
        main.cpp
        TreeView/TreeView.cpp
        TreeWidget/TreeWidget.cpp
        ProgressBar/ProgressBar.cpp
        StatusBar/StatusBar.cpp
        ListBox/ListBox.cpp
        ../Multithreading/Threads.cpp ../Multithreading/Threads.h
)

target_link_libraries(${PROJECT_NAME} pthread ${Qt5Widgets_LIBRARIES})

