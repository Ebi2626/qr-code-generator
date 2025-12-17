add_executable(qrgen-cli
    main.cpp
    src/parseInput.cpp
)

target_link_libraries(qrgen-cli
    PRIVATE 
        qrgen_core
        qrgen_infra
)

target_include_directories(qrgen-cli
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../core/include
)
