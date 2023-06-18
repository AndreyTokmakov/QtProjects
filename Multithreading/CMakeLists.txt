cmake_minimum_required(VERSION 3.25)
project(Multithreading)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# QT dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
# find_package(QtProjects COMPONENTS Core REQUIRED)

qt5_generate_moc(Threads.cpp Threads.moc)

add_executable(Multithreading main.cpp Threads.cpp Threads.moc)
target_link_libraries(Multithreading pthread ${Qt5Widgets_LIBRARIES})
