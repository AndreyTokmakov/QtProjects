cmake_minimum_required(VERSION 3.25)
project(DarkMode)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# QT dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
# find_package(QtProjects COMPONENTS Core REQUIRED)


# set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
# add_compile_options(-c -Wall -Wextra -O3 -std=c++2a)


add_executable(DarkMode
        main.cpp
        )


target_link_libraries(DarkMode pthread ${Qt5Widgets_LIBRARIES})

