cmake_minimum_required(VERSION 3.20)

project(qrgen-core LANGUAGES CXX)

add_library(qrgen_core STATIC
    src/QrGenerator.cpp
)

target_include_directories(qrgen_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(qrgen_core PUBLIC cxx_std_20)
