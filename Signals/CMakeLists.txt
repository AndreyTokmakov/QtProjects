cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Signals)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)


add_compile_options(-c -Wall -Wextra -O3 -std=c++23)


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
)

# include all components
add_executable(Signals
        main.cpp main.moc
)

target_link_libraries(Signals ${Qt5Widgets_LIBRARIES})
