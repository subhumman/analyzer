cmake_minimum_required(VERSION 3.14) 
project(analyzer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES 
    "main.cpp"
    "scripts/src/*.cpp"
)

add_executable(analyzer ${SOURCES})

target_include_directories(analyzer PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/lib
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(cmake/CPM.cmake)

CPMAddPackage("gh:nlohmann/json@3.12.0")

target_link_libraries(analyzer PRIVATE 
    nlohmann_json::nlohmann_json 

)
