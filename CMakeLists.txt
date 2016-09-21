cmake_minimum_required(VERSION 2.8.12)
project(RunnerIdnConverter)

find_package(ECM 5.12.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH
     ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}
)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED CONFIG COMPONENTS Widgets Core Quick)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS I18n Service Runner TextWidgets PlasmaQuick)
find_package(ICU 57.1 COMPONENTS io i18n REQUIRED)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

set(krunner_idnconverter_SRCS
    idnconverterrunner.cpp idnconverter.cpp
)

add_library(krunner_idnconverter MODULE ${krunner_idnconverter_SRCS})
target_link_libraries(krunner_idnconverter KF5::Runner Qt5::Widgets
                      KF5::I18n
                      KF5::Service
                      KF5::Plasma
                      ICU::ICU)
                      
install(TARGETS krunner_idnconverter DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-runner-idnconverter.desktop DESTINATION ${SERVICES_INSTALL_DIR})
