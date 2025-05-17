cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(PasswordManager2)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_compile_options(-c -Wall -Wextra -O3 -std=c++23)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(UTILS ${PROJECT_DIR}/utils)
set(CRYPTO ${PROJECT_DIR}/crypto)
set(UI ${PROJECT_DIR}/ui)

include_directories(${UTILS})
include_directories(${CRYPTO})
include_directories(${UI})
include_directories(${THIRD_PARTY_DIR}/cryptopp)
link_directories(${THIRD_PARTY_DIR}/cryptopp)

# include all components
add_executable(${PROJECT_NAME} 
        main.cpp
        ${UTILS}/FileUtilities.cpp
        ${UTILS}/Utilities.cpp
        ${CRYPTO}/Encryption.cpp
        ${UI}/LoginDialog.cpp
        ${UI}/DarkThemeApplication.cpp
        ${UI}/PasswordManagerWindow.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        pthread
        -lcryptopp
        ${Qt5Widgets_LIBRARIES}
)