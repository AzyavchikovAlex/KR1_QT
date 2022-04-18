cmake_minimum_required(VERSION 3.21)

project(KR1_Azyavchikov_QT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "~/Qt/6.3.0/mingw_64/lib/cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

set(MODELS
        Models/main_window.cpp
        Models/input_task.cpp
        Models/pick_task.cpp
        Models/audio_task.cpp
        Models/task.cpp)

#set(VIEWS
#        Views/view.cpp)

set(CONTROLLERS
        Controllers/controller.cpp)

set(SOURCES
        main.cpp
        ${MODELS}
        #${VIEWS}
        ${CONTROLLERS})

qt6_add_big_resources(RESOURCES resources.qrc)

add_executable(KR1_Azyavchikov_QT ${SOURCES} ${RESOURCES})

target_link_libraries(KR1_Azyavchikov_QT
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )

