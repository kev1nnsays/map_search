cmake_minimum_required(VERSION 2.8.1)
project(eecs_592_homework_1)
find_package(PythonLibs REQUIRED)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

include_directories(
    include
    text_maps
    ${PYTHON_INLUCDE_DIRS}
    ${SDL2_INCLUDE_DIR}
)

#set(SOURCES src/blahblahblah.cpp src/help.cpp)

file(GLOB SOURCES "src/*.cpp")

add_executable(homework_1_search
    ${SOURCES}
)

target_link_libraries(homework_1_search
    ${PYTHON_LIBRARY}
    ${SDL2_LIBRARIES}
)