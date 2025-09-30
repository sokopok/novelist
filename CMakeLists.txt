cmake_minimum_required(VERSION 3.16)

project(
  novelist
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Network Sql LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appnovelist src/novelist/main.cpp)

qt_add_qml_module(
  appnovelist
  URI
  be.oncruyt.novelist
  VERSION
  1.0
  QML_FILES
  src/novelist/qml/Main.qml
  RESOURCES
  src/novelist/qml/ai.svg
  src/novelist/qml/user.svg
  src/novelist/qml/bubble-square.svg
  src/novelist/qml/ai-square.svg
  src/novelist/qml/computer-square.svg
  src/novelist/qml/user-square.svg
  src/novelist/qml/human-square.svg
  SOURCES
  src/libai/json.h)

target_include_directories(appnovelist PUBLIC src)

# set_target_properties(appnovelist PROPERTIES OUTPUT_NAME appnovelist )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1. If
# you are developing for iOS or macOS you should consider setting an explicit,
# fixed bundle identifier manually though.
set_target_properties(
  appnovelist
  PROPERTIES # MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appnovelist
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE)

target_link_libraries(appnovelist PRIVATE Qt6::Quick Qt6::Gui Qt6::Network
                                          Qt6::Sql libai libnovelist)
target_link_libraries(appnovelist PRIVATE Qt6::Core)

add_library(
  libai STATIC
  src/libai/libai_nl_BE.ts
  src/libai/request.h
  src/libai/client.h
  src/libai/client.cpp
  src/libai/request.cpp
  src/libai/logging.h
  src/libai/logging.cpp
  src/libai/config/message.h
  src/libai/config/base.h
  src/libai/config/input.h
  src/libai/config/conversation.h
  src/libai/config.h
  src/libai/config/streamoptions.h
  src/libai/config/outputmessage.h
  src/libai/responses/request.cpp
  src/libai/responses/request.h
  src/libai/responses/client.cpp
  src/libai/responses/client.h
  src/libai/response.h
  src/libai/response.cpp
  src/libai/responses/response.h
  src/libai/responses/response.cpp
  src/libai/config/reasoning.h
  src/libai/config/output.h)

target_include_directories(libai PUBLIC src)

target_link_libraries(libai PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Network
                                    Qt6::Sql)
target_link_libraries(libai PRIVATE Qt6::Core)

target_compile_definitions(libai PRIVATE LIBAI_LIBRARY)

add_library(
  libnovelist STATIC
  src/libnovelist/libnovelist_nl_BE.ts
  src/libnovelist/novelist.cpp
  src/libnovelist/novelist.h
  src/libnovelist/projectstore.cpp
  src/libnovelist/projectstore.h
  src/libnovelist/project.cpp
  src/libnovelist/project.h
  src/libnovelist/field.h
  src/libnovelist/field.cpp
  src/libnovelist/element.h
  src/libnovelist/element.cpp
  src/libnovelist/node.h
  src/libnovelist/node.cpp
  src/libnovelist/interfaces.h
  src/libnovelist/interfaces.cpp
  src/libnovelist/logging.h
  src/libnovelist/logging.cpp)

target_include_directories(libnovelist PUBLIC src)

target_link_libraries(libnovelist PRIVATE Qt6::Core Qt6::Gui Qt6::Quick
                                          Qt6::Network Qt6::Sql libai)

target_compile_definitions(libnovelist PRIVATE LIBNOVELIST_LIBRARY)

if(COMMAND qt_create_translation)
  qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
  qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)
install(
  TARGETS appnovelist
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
