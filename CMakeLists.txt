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

qt_standard_project_setup(REQUIRES 6.8)

if(COMMAND qt_create_translation)
  qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
  qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)

qt_add_executable(appnovelist main.cpp)

qt_add_qml_module(
  appnovelist
  URI
  appnovelist
  QML_FILES
  qml/Main.qml
  qml/SettingsPage.qml
  qml/ChatPage.qml
  qml/RoundButton.qml
  qml/util.js
  qml/SquareBubble.qml
  RESOURCES
  qml/ai.svg
  qml/user.svg
  qml/bubble-square.svg
  qml/ai-square.svg
  qml/computer-square.svg
  qml/user-square.svg
  qml/human-square.svg
  QML_FILES
  qml/ChatOutput.qml
  SOURCES
  textareautils.h
  textareautils.cpp
  QML_FILES
  QML_FILES
  qml/FieldListView.qml
  RESOURCES
  qml/element.svg
  qml/field.svg
  QML_FILES
  qml/NodeListView.qml
  RESOURCES
  qml/node.svg
  RESOURCES
  qml/modified.svg
  QML_FILES
  qml/ValueListView.qml
  RESOURCES
  qml/value.svg
  RESOURCES
  qml/element-modified.svg
  qml/field-modified.svg
  qml/value-modified.svg
  QML_FILES
  qml/Dot.qml
  QML_FILES
  qml/FieldTypeListView.qml
  QML_FILES
  qml/ValueTypeListView.qml
  RESOURCES
  qml/elementtype.svg
  qml/fieldtype.svg
  qml/valuetype.svg
  QML_FILES
  qml/FieldTypeListViewDelegateRow.qml
  QML_FILES
  qml/ElementTreeView.qml
  QML_FILES
  qml/ElementTreeviewDelegateLabel.qml
  QML_FILES
  qml/ElementTreeviewDelegateValue.qml
  QML_FILES
  qml/ElementTypeTableView.qml)

set_target_properties(appnovelist PROPERTIES OUTPUT_NAME novelist)

target_link_libraries(
  appnovelist
  PRIVATE Qt6::Core
          Qt6::Quick
          Qt6::Gui
          Qt6::Network
          Qt6::Sql
          libaiplugin
          libnovelistplugin)

add_subdirectory(libai)
add_subdirectory(libnovelist)
