find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Network Sql LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_library(libnovelist STATIC)
qt_add_qml_module(
  libnovelist
  URI
  libnovelist
  VERSION
  1.0
  RESOURCES
  libnovelist_nl_BE.ts
  SOURCES
  novelist.cpp
  novelist.h
  logging.h
  logging.cpp
  validator.cpp
  validator.h
  storable.h
  storable.cpp
  node.h
  node.cpp
  element.h
  element.cpp
  storage.h
  storage.cpp
  errorhandler.h
  field.h
  field.cpp
  nodetype.h
  nodetype.cpp
  elementtype.h
  elementtype.cpp
  fieldtype.h
  fieldtype.cpp
  value.h
  value.cpp
  valuetype.h
  valuetype.cpp
  jsonable.h
  nodelistmodel.h
  nodelistmodel.cpp
  fieldlistmodel.h
  fieldlistmodel.cpp
  valuelistmodel.h
  valuelistmodel.cpp
  SOURCES
  elementstorage.h
  elementstorage.cpp
  SOURCES
  nodestorage.h
  nodestorage.cpp
  SOURCES
  fieldstorage.h
  fieldstorage.cpp
  SOURCES
  valuestorage.h
  valuestorage.cpp
  SOURCES
  elementtypestorage.h
  elementtypestorage.cpp
  SOURCES
  nodetypestorage.h
  nodetypestorage.cpp
  SOURCES
  fieldtypestorage.h
  fieldtypestorage.cpp
  SOURCES
  valuetypestorage.h
  valuetypestorage.cpp
  SOURCES
  valuetypelistmodel.h
  valuetypelistmodel.cpp
  SOURCES
  fieldtypelistmodel.cpp
  fieldtypelistmodel.h
  SOURCES
  elementtypelistmodel.h
  elementtypelistmodel.cpp
  SOURCES
  elementtypetreemodel.h
  elementtypetreemodel.cpp
  SOURCES
  elementtypetablemodel.h
  elementtypetablemodel.cpp
  SOURCES project.h project.cpp
  SOURCES projecttype.h projecttype.cpp
  SOURCES projecttypestorage.h projecttypestorage.cpp
  SOURCES projectstorage.h projectstorage.cpp
  SOURCES basestorage.h basestorage.cpp)

target_link_libraries(libnovelist PRIVATE Qt6::Core Qt6::Quick Qt6::Gui
                                          Qt6::Network Qt6::Sql libaiplugin)
target_link_libraries(libnovelist PRIVATE Qt6::Core)
target_link_libraries(libnovelist PRIVATE Qt6::Core)
target_link_libraries(libnovelist PRIVATE Qt6::Core)
target_link_libraries(libnovelist PRIVATE Qt6::Core)
target_link_libraries(libnovelist PRIVATE Qt6::Core)

if(COMMAND qt_create_translation)
  qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
  qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)
