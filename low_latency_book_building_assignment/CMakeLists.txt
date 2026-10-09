cmake_minimum_required(VERSION 3.16)

project(low_latency_book_building_assignment VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS LinguistTools QUIET)

set(TS_FILES low_latency_book_building_assignment_en_IN.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    orderbookwindow.h
    orderbookwindow.cpp
    orderbookmanager.h
    orderbookmanager.cpp
    orderbook.h
    orderbook.cpp
    orderbookmodel.h
    orderbookmodel.cpp
    marketdepth.h
    tbtrecord.h
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(orderbook
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        README.md
    )
    if(TARGET Qt6::lrelease)
        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
else()
    add_executable(orderbook
        ${PROJECT_SOURCES}
    )
    if(TARGET Qt5::lrelease)
        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
endif()

add_executable(low_latency_book_building_assignment ALIAS orderbook)

target_link_libraries(orderbook PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
)

include(GNUInstallDirs)
install(TARGETS orderbook
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(orderbook)
endif()

