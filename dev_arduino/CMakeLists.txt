cmake_minimum_required(VERSION 3.10)
project(main)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the csv-parser library
add_subdirectory(lib/csv-parser)

# Include directories
include_directories(lib/csv-parser/include)
include_directories(src)

# Add source files
add_executable(main
    src/MockArduino.cpp
    src/main.cpp
    src/sensors/Scale.cpp
    src/signal_processor/SignalProcessor.cpp
    src/timer/Timer.cpp
)

# Link libraries
target_link_libraries(main PRIVATE csv)
