cmake_minimum_required(VERSION 3.16.0)

Project(
    phoenix-ML
    VERSION 1.1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS         ON)

# Set CXX flags to -fPIC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME calculator_module)



set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
    GIT_SHALLOW TRUE
)



FetchContent_MakeAvailable(googletest)


option(COMPLE_EXECUTABLE "option to compile the executable" ON)
option(ENABLE_TESTING "option to enable a unit testing build" ON)
option(PARALLEL "option to enable parallel computation" OFF)

add_subdirectory(library)
add_subdirectory(examples)
#add_subdirectory(Test)

