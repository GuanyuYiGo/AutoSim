cmake_minimum_required(VERSION 3.5)
project(planningPcoS)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)

# find source files
file(GLOB_RECURSE SOURCES "LaneMarkSensor/*.cpp" "*.cpp")

# add executable to project
add_executable(${PROJECT_NAME} ${SOURCES})

# include directories
include_directories(
    "D:/Users/25104/AppData/Local/Programs/Python/Python310/Lib/site-packages/pybind11/include"
    "D:/Users/25104/AppData/Local/Programs/Python/Python310/include"
    "D:/Users/25104/AppData/Local/Programs/Python/Python310/Lib/site-packages/numpy/core/include"
    "D:/OpenDrive/matplotlibcpp"
    "D:/OpenDrive"
)

# link libraries
target_link_libraries(${PROJECT_NAME}
    "D:/Users/25104/AppData/Local/Programs/Python/Python310/libs/python310.lib"
)
