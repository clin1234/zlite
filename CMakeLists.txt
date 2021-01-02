cmake_minimum_required(VERSION 3.17) # For now
project(zlite VERSION 0.1
DESCRIPTION
"A modern spiffy and lightweight zlib-compatible library for compression
and decompression."
LANGUAGES CXX)

add_library(libzlite STATIC
crc32.cpp adler32.cpp deflate.cpp zlib.cpp gzip.cpp)

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options(zlite PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic -trigraphs)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    target_compile_options(zlite PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options(zlite PRIVATE /W4)
endif()

target_compile_features(libzlite PUBLIC cxx_std_17)

set_target_properties(libzlite PROPERTIES OUTPUT_NAME "zlite"
INTERPROCEDURAL_OPTIMIZATION TRUE)

include(GNUInstallDirs)

install(
    TARGETS
      zlite
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

include(InstallRequiredSystemLibraries)
set(CMAKE_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)

#include(CTest)
