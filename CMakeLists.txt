cmake_minimum_required(VERSION 3.19)
project(SystemHelper LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Test)

qt_standard_project_setup()

qt_add_executable(SystemHelper
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ollamaclient.h ollamaclient.cpp
)

target_link_libraries(SystemHelper
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

install(TARGETS SystemHelper
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SystemHelper
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

enable_testing()

qt_add_executable(TestyAplikacji
    tst_main.cpp
    ollamaclient.cpp
    ollamaclient.h
)

target_link_libraries(TestyAplikacji PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Test
)

add_test(NAME MojeTesty COMMAND TestyAplikacji)