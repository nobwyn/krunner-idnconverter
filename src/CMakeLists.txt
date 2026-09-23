add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_idnconverter\")

kcoreaddons_add_plugin(krunner_idnconverter SOURCES idnconverterrunner.cpp idnconverter.cpp INSTALL_NAMESPACE "kf6/krunner")

target_link_libraries(krunner_idnconverter
    Qt6::Gui
    KF6::Runner
    KF6::I18n
    ICU::uc
)
