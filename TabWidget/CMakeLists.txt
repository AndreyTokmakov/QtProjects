cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(TabWidget)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# QT dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
# find_package(QtProjects COMPONENTS Core REQUIRED)



add_compile_options(-c -Wall -Wextra -O3 -std=c++23)

# include all components
add_executable(TabWidget
    main.cpp
)

target_link_libraries(TabWidget pthread ${Qt5Widgets_LIBRARIES})
