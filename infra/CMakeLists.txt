# Ręczne znajdowanie biblioteki (Tryb modułu, zgodnie z instrukcją vcpkg)
find_path(QRENCODE_INCLUDE_DIR NAMES qrencode.h)
find_library(QRENCODE_LIBRARY_RELEASE NAMES qrencode)
find_library(QRENCODE_LIBRARY_DEBUG NAMES qrencoded)
find_package(lodepng CONFIG REQUIRED)

if(QRENCODE_INCLUDE_DIR)
    message(STATUS "Found QRENCODE include directory: ${QRENCODE_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "libqrencode files not found!")
endif()

set(QRENCODE_LIBRARIES optimized ${QRENCODE_LIBRARY_RELEASE} debug ${QRENCODE_LIBRARY_DEBUG})


add_library(qrgen_infra STATIC
    src/QrEncoderLibqrencode.cpp
)

target_include_directories(qrgen_infra
    # Ścieżka do nagłówków dla samego qrgen_infra (Twój kod)
    PUBLIC
        # Dostęp do nagłówków wewnątrz infra/include (np. dla innych, którzy z infra korzystają)
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    # Ustawienie nagłówka 'qrgen/...'
    # Dodanie katalogu głównego projektu, aby kompilator znalazł 'qrgen/'
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> 

    # Ścieżka do nagłówków biblioteki zewnętrznej (libqrencode)
    PRIVATE
        ${QRENCODE_INCLUDE_DIR}
)

target_link_libraries(qrgen_infra
    # Linkowanie do core (od tego odziedziczy się nagłówki core)
    PUBLIC qrgen_core 
    
    # Linkowanie do libqrencode
    PRIVATE ${QRENCODE_LIBRARIES}
    lodepng
)