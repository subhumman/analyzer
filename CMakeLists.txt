cmake_minimum_required(VERSION 3.14) 
project(analyzer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем все .cpp файлы из scripts/src
file(GLOB_RECURSE SOURCES 
    "main.cpp"
    "scripts/src/*.cpp"
)

add_executable(analyzer ${SOURCES})

# Добавляем include directories
target_include_directories(analyzer PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/lib
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(cmake/CPM.cmake)

CPMAddPackage("gh:nlohmann/json@3.12.0")
# Отключаем benchmark - он не нужен для основного функционала
# CPMAddPackage(
#   NAME benchmark
#   GIT_TAG v1.8.3 
#   GITHUB_REPOSITORY google/benchmark
#   OPTIONS "BENCHMARK_ENABLE_TESTING Off"
# )
# Убираем fmt - используем стандартный вывод
# CPMAddPackage(
#   NAME fmt
#   GIT_TAG 11.2.0 
#   GITHUB_REPOSITORY fmtlib/fmt
# )

target_link_libraries(analyzer PRIVATE 
    nlohmann_json::nlohmann_json 
)

# Убираем флаг, который не поддерживается в MSVC
# target_compile_options(fmt INTERFACE -Wno-deprecated-literal-operator)