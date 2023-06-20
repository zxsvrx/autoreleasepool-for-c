cmake_minimum_required(VERSION 3.0)  # Adjust the version as needed

project(libARPC)

set(SOURCES
    src/autoreleasepool.c
)

set(HEADERS
    include/autoreleasepool.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)
