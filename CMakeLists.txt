
project(ksaneplugin)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules )

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

find_package(KSane REQUIRED)
include_directories(${KSANE_INCLUDE_DIR})
add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS} -DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
include_directories (${QDBUS_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

########### target ###############
kde4_add_plugin(ksaneplugin sanedialog.cpp)

target_link_libraries(ksaneplugin ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KSANE_LIBRARY})

install(TARGETS ksaneplugin  DESTINATION ${PLUGIN_INSTALL_DIR} )

########### install files ###############
install( FILES ksane_scan_service.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )

