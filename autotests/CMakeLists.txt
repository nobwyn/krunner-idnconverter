include(ECMAddTests)

ecm_add_test(idnconverterrunnertest.cpp TEST_NAME idnconverterrunnertest LINK_LIBRARIES Qt6::Test KF6::Runner)
krunner_configure_test(idnconverterrunnertest krunner_idnconverter)
