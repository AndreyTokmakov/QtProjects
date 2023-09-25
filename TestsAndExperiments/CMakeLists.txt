cmake_minimum_required(VERSION 3.25)
project(TestsAndExperiments)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# QT dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
# find_package(QtProjects COMPONENTS Core REQUIRED)

qt5_generate_moc(
        main.cpp main.moc
        StatusBar.cpp StatusBar.h
)

add_executable(TestsAndExperiments main.cpp main.moc StatusBar.cpp)
target_link_libraries(TestsAndExperiments pthread ${Qt5Widgets_LIBRARIES})
