cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(qrgen-core LANGUAGES CXX)

add_library(qrgen_core STATIC
    services/QrGeneratorService.cpp
    domain/QrCodeOptions.hpp
)

target_include_directories(qrgen_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/domain
        ${CMAKE_CURRENT_SOURCE_DIR}/ports
        ${CMAKE_CURRENT_SOURCE_DIR}/services
)

target_compile_features(qrgen_core PUBLIC cxx_std_23)
