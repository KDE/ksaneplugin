
project(ksaneplugin)

find_package(KSane REQUIRED)
include_directories(${KSANE_INCLUDE_DIR})
########### target ###############
kde4_add_plugin(ksaneplugin sanedialog.cpp)

target_link_libraries(ksaneplugin ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KSANE_LIBRARY})

install(TARGETS ksaneplugin  DESTINATION ${PLUGIN_INSTALL_DIR} )

########### install files ###############
install( FILES ksane_scan_service.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )

