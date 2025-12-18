add_executable(qrgen-cli
    main.cpp
    src/CliArgumentParser.cpp
)

target_link_libraries(qrgen-cli
    PRIVATE 
        qrgen_core
        qrgen_infra
        qrgen_adapters
)

target_include_directories(qrgen-cli
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
