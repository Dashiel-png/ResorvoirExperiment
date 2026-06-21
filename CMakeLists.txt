cmake_minimum_required(VERSION 3.15)
project(rcdisp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


#my implementation-files
set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/include/ESN1/Activation-impl.cpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/ESN.cpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/Tanh-impl.cpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/Linear.cpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/LRReadout.cpp
    ${PROJECT_SOURCE_DIR}/include/Metrics/BasicComp.cpp
    ${PROJECT_SOURCE_DIR}/src/mainwindow.cpp
    ${PROJECT_SOURCE_DIR}/include/qcustomplot/qcustomplot.cpp
)
list(APPEND CMAKE_PREFIX_PATH "/Users/dashielbalnaves/Qt/6.11.1/macos")

# 1. Find Qt components (QCustomPlot requires Core, Gui, and Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)
# Note: Change "Qt6" to "Qt5" above if you are using Qt 5.

#my headers

set(PROJECT_HEADERS
    ${PROJECT_SOURCE_DIR}/include/ESN1/Activation.hpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/Tanh.hpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/ESN.hpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/Linear.hpp
    ${PROJECT_SOURCE_DIR}/include/ESN1/LRReadout.hpp
    ${PROJECT_SOURCE_DIR}/include/qcustomplot/qcustomplot.h
    ${PROJECT_SOURCE_DIR}/src/mainwindow.h
    ${PROJECT_SOURCE_DIR}/include/Eigen

)


add_executable(main
    src/main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS}
)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include/Eigen
    ${PROJECT_SOURCE_DIR}/include/qcustomplot
    ${PROJECT_SOURCE_DIR}/include/ESN1
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)




target_link_libraries(main PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::PrintSupport # Required by QCustomPlot for PDF/Printer export
)