find_package(lodepng CONFIG REQUIRED)
find_path(QRENCODE_INCLUDE_DIR NAMES qrencode.h)
find_library(QRENCODE_LIBRARY NAMES qrencode)

add_library(qrgen_adapters STATIC
    encoders/LibqrencodeAdapter.cpp
    exporters/PngExporter.cpp
    exporters/SvgExporter.cpp
)

target_link_libraries(qrgen_adapters
    PUBLIC qrgen_core
    PRIVATE ${QRENCODE_LIBRARY} lodepng
)

target_include_directories(qrgen_adapters
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${QRENCODE_INCLUDE_DIR}
)
