cmake_minimum_required(VERSION 3.19)
project(untitled2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#опция CMAKE_INCLUDE_CURRENT_DIR обязательно должна быть включена,
#если вы не меняли пути генерации файлов для Qt.
#при использовании .ui файлов, Qt на их основе генерирует промежуточные
#файлы исходников, и будет складывать их в директории сборки.
#Чтобы среда их видела, необходимо добавить в директории для включения
#(include, директории, хранящие подключаемые .h файлы), директорию сборки:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ( CMAKE_COMPILER_IS_GNUCC )
   set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
   set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

#здесь мы создаем переменную CHAT_LIBRARIES, в которой будем хранить
#все подключаемые к проекту библиотеки, в т.ч. и библиотеки Qt
set(CHAT_LIBRARIES)

#здесь мы создаем и заполняем список подключаемых модулей Qt
#если нужно добавить модули, добавьте их в этот список по образцу:
#set(Qt5Modules [модуль 1] [модуль 2] ... [модуль n])
set(Qt5Modules Core Widgets)

#здесь мы формируем из списка модулей список библиотек,
#которые требуется подключить, и складываем их в CHAT_LIBRARIES
foreach(QtModule IN LISTS Qt5Modules)
 list(APPEND CHAT_LIBRARIES Qt5::${QtModule})
endforeach(QtModule)


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

#здесь мы формируем список всех исходников, ассоциированных с
#проектом Chat.
#на самом деле, обязательными являются только SRC RC и UI,
#но я добавляю так же HEADERS, что бы они так же отображались
#в дереве проектов.

#!!! не забывайте, что при добавлении/удалении файлов  обязательно
#нужно запускать CMake
file(GLOB_RECURSE SRC_FILES sources/*.cpp)
file(GLOB_RECURSE HEADERS_FILES sources/*.h)
file(GLOB_RECURSE RC_FILES sources/*.qrc)
file(GLOB_RECURSE UI_FILES sources/*.ui)

#здесь мы включаем обязательные для нас опции
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#вызываем обработку .ui и .qrc файлов. Здесь же происходит генерация
#промежуточных исходников.
qt6_wrap_ui(QUI ${UI_FILES})
qt6_add_resources(QRC ${RC_FILES})

qt_standard_project_setup()

qt_add_executable(untitled2
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    chat.cpp chat.h
    users.cpp users.h
    server.cpp server.h
    Message.h
    loginform.cpp loginform.h loginform.ui
    startscreen.cpp startscreen.h startscreen.ui
    logger.cpp logger.h
    bad_login.cpp bad_login.h
    bad_password.cpp bad_password.h
    registrationform.h registrationform.cpp registrationform.ui
)

target_link_libraries(untitled2
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS untitled2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET untitled2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
