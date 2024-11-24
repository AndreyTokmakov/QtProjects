cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(PasswordManager)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)


add_compile_options(-c -Wall -Wextra -O3 -std=c++23)

# QT dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
# find_package(QtProjects COMPONENTS Core REQUIRED)

SET(OPENSSL_ROOT_DIR ${THIRD_PARTY_DIR}/openssl)

link_directories(${OPENSSL_ROOT_DIR})
include_directories("${OPENSSL_ROOT_DIR}/include")


# include all components
add_executable(${PROJECT_NAME} 
    main.cpp
    FileUtilities.cpp
)

 # Link phread library
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        pthread
        crypto
        ${Qt5Widgets_LIBRARIES}
)