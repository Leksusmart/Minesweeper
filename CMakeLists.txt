cmake_minimum_required(VERSION 3.16)

project(Minesweeper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/Welcome.cpp
    src/WelcomeWindow.h
    src/Welcome.ui
    src/GameWindow.h
    src/Game.cpp
    src/Game.ui
    src/resourses.qrc
    src/meta.rc
)


add_executable(Minesweeper ${PROJECT_SOURCES})


target_link_libraries(Minesweeper PRIVATE Qt6::Widgets Qt6::Core Qt6::Multimedia)

if(NOT QT6_FOUND OR QT_VERSION VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Minesweeper)
endif()
set_target_properties(Minesweeper PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Minesweeper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Minesweeper)
endif()
