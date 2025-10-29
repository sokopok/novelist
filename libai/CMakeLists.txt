cmake_minimum_required(VERSION 3.16)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Network Sql LinguistTools)

qt_add_library(libai STATIC)
qt_add_qml_module(
  libai
  URI
  libai
  VERSION
  1.0
  RESOURCES
  libai_nl_BE.ts
  SOURCES
  request.h
  request.cpp
  response.h
  response.cpp
  client.h
  client.cpp
  responsesrequest.cpp
  responsesrequest.h
  responsesresponse.h
  responsesresponse.cpp
  responsesclient.cpp
  responsesclient.h
  imagesrequest.h
  imagesrequest.cpp
  imagesresponse.cpp
  imagesresponse.h
  imagesclient.h
  imagesclient.cpp
  SOURCES
  responseutils.h
  responseutils.cpp
  SOURCES
  responsesrequestutils.h
  responsesrequestutils.cpp
  SOURCES
  responsesresponseutils.h
  responsesresponseutils.cpp)

target_link_libraries(libai PRIVATE Qt6::Core Qt6::Quick Qt6::Gui Qt6::Network
                                    Qt6::Sql)
