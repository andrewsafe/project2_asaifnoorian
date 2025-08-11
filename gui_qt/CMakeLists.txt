cmake_minimum_required(VERSION 3.22)
project(project2_asaifnoorian LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(vp_core STATIC
    ../src/deck.cpp
    ../src/hand.cpp
    ../src/player.cpp
    ../src/evaluator.cpp
)
target_include_directories(vp_core PUBLIC ../include)

add_executable(project2_asaifnoorian
    main_qt.cpp
    MainWindow.h
    MainWindow.cpp
)
target_link_libraries(project2_asaifnoorian PRIVATE Qt6::Widgets vp_core)
