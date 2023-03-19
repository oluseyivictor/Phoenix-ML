set(LIBRARY_SOURCES 
    "src/activations.cpp"
    "src/utils.cpp"
    "src/io.cpp"
    "src/nnet/nn.cpp"
    "src/nnet/simplenn.cpp"
    "src/nnet/LinearRegression.cpp")

set(INCLUDE_SOURCES 
    "include/"
    "include/ADT/"
    "include/nnet/")

configure_file(
    "config.hpp.in"
    "${CMAKE_BINARY_DIR}/version_files/include/config.hpp" ESCAPE_QUOTES
)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})

target_include_directories(${LIBRARY_NAME}  PUBLIC 
    ${INCLUDE_SOURCES}
    "${CMAKE_BINARY_DIR}/version_files/include/" )