cmake_minimum_required(VERSION 3.15)
project(rcTest)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


//my implementation-files
set(PROJECT_SOURCES
    include/ESN1/Acivation-impl.cpp
    include/ESN1/ESN.cpp
    include/ESN1/Linear.cpp
    include/ESN1/LRReadout.cpp
    include/Metrics/BasicComp.cpp
    include/qcustomplot/qcustomplot.cpp
)
list(APPEND CMAKE_PREFIX_PATH "/Users/dashielbalnaves/Qt/6.11.1/macos")

# 1. Find Qt components (QCustomPlot requires Core, Gui, and Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)
# Note: Change "Qt6" to "Qt5" above if you are using Qt 5.

//my headers

set(PROJECT_HEADERS
    include/ESN1/Acivation.hpp
    include/ESN1/ESN.hpp
    include/ESN1/Linear.hpp
    include/ESN1/LRReadout.hpp
    include/qcustomplot/qcustomplot.hpp

)

add_executable(main
    src/main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS}
)

# Set the include directories to point to the GUDHI headers
include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(MyQCustomPlotProject PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::PrintSupport # Required by QCustomPlot for PDF/Printer export
)