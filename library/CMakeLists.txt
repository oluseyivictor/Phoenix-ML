set(LIBRARY_SOURCES 
    "src/activations.cpp"
    "src/utils.cpp"
    "src/io.cpp"
    "src/nnet/nn.cpp"
    "src/nnet/simplenn.cpp"
    "src/nnet/LinearRegression.cpp"
    "src/nnet/LogisticRegression.cpp")

set(INCLUDE_SOURCES 
    "include/"
    "include/ADT/"
    "include/nnet/")

configure_file(
    "config.hpp.in"
    "${CMAKE_BINARY_DIR}/version_files/include/config.hpp" ESCAPE_QUOTES
)
find_package(Boost 1.86.0 REQUIRED)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})

target_include_directories(${LIBRARY_NAME}  PUBLIC 
    ${INCLUDE_SOURCES}
    ${Boost_INCLUDE_DIRS}
    "${CMAKE_BINARY_DIR}/version_files/include/" )

target_link_libraries(${LIBRARY_NAME} PUBLIC
    Boost::boost
    ${Boost_library}
    ${PYTHON_LIBRARY}
)