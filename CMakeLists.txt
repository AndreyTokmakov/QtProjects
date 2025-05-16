cmake_minimum_required(VERSION 3.25)
project(QtProjects)

set(CMAKE_CXX_STANDARD 23)

list(APPEND EXTRA_LIBS)
if (CMAKE_SYSTEM_VERSION MATCHES "5.15") # 5.15 - My home Ubuntu-20.04
    set(THIRD_PARTY_DIR /home/andtokm/DiskS/ProjectsUbuntu/third_party)
    list(APPEND EXTRA_LIBS tbb)
else()
    set(THIRD_PARTY_DIR /home/andtokm/Projects/third_party)
endif()


add_subdirectory(Controls)
add_subdirectory(DarkMode)
add_subdirectory(Multithreading)
add_subdirectory(TabWidget)
add_subdirectory(PasswordManager)
add_subdirectory(PasswordManager2)
add_subdirectory(Signals)
add_subdirectory(Tests)
add_subdirectory(TestsAndExperiments)
add_subdirectory(Widgets)

