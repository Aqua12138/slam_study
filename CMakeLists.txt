cmake_minimum_required(VERSION 3.20)
project(slam_study)

set(CMAKE_CXX_STANDARD 14)

add_executable(slam_study main.cpp Sophus_study.cpp Sophus_study.h Opencv_study.cpp Opencv_study.h)
SET(CMAKE_EXE_LINKER_FLAGS " -no-pie")
find_package(fmt)
include_directories(${Fmt_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} fmt::fmt)

find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})