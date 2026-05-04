cmake_minimum_required(VERSION 3.16)

project(VideoPlayer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia OpenGLWidgets MultimediaWidgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(FORMS
    mainwindow.ui
)

set(HEADERS
    mainwindow.h
)

add_executable(VideoPlayer
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_link_libraries(VideoPlayer PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::OpenGLWidgets
    Qt6::MultimediaWidgets
)

if(QNX)
    set(INSTALL_EXAMPLEDIR /tmp/${PROJECT_NAME}/bin)
elseif(UNIX AND NOT ANDROID)
    set(INSTALL_EXAMPLEDIR /opt/${PROJECT_NAME}/bin)
endif()

if(INSTALL_EXAMPLEDIR)
    install(TARGETS VideoPlayer DESTINATION ${INSTALL_EXAMPLEDIR})
endif()
