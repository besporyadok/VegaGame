cmake_minimum_required(VERSION 3.19)

project(VegaGame)

file(GLOB SRC "Src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_compile_options(${PROJECT_NAME} PRIVATE "/EHsc")
target_include_directories(${PROJECT_NAME} PRIVATE "3rd_party/Inc")
target_link_directories(${PROJECT_NAME} PRIVATE "3rd_party/Lib")