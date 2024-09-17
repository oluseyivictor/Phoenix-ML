include(FetchContent)

find_package(Python 3.8 REQUIRED COMPONENTS Interpreter Development)
find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

# Print the Python 3.8 include directory
# Add the found include directory to the include paths
include_directories(${_Python_INCLUDE_DIR})

execute_process(
    COMMAND ${_Python_EXECUTABLE} -c "import numpy"
    RESULT_VARIABLE numpy_check_result
    OUTPUT_QUIET ERROR_QUIET
    )

if(NOT numpy_check_result EQUAL 0)
    message(WARNING "Python 'numpy' module is not available! Installing it...")
    execute_process(
        COMMAND ${_Python_EXECUTABLE} -m pip install numpy==1.26.0
        RESULT_VARIABLE pip_install_result
        OUTPUT_QUIET ERROR_QUIET
    )
endif()

find_path(DIR_PATH
    NAMES boost
    PATHS ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0
    NO_DEFAULT_PATH  # Optional: if you want to limit the search to your specified paths
)

message(STATUS "BOOST found at ${DIR_PATH}")
if(NOT DIR_PATH)
    # If Boost is not found, download and populate it
    FetchContent_Populate(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.86.0/source/boost_1_86_0.zip
        URL_HASH SHA256=cd20a5694e753683e1dc2ee10e2d1bb11704e65893ebcc6ced234ba68e5d8646
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0
    )

    # Set Boost include and library directories
    set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0 CACHE PATH "Boost Root File")
    set(Boost_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0 CACHE PATH "Boost Root File")
    set(Boost_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0/stage/lib CACHE PATH "Boost Root File")

      # Check if the third-party 'numpy' module is available
    
    
    # change this to use bootstrap.sh for linux
    execute_process(
        COMMAND bootstrap.bat gcc
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0
        RESULT_VARIABLE BOOTSTRAP_RESULT
        ERROR_VARIABLE BOOTSTRAP_ERROR
    )
    if(BOOTSTRAP_RESULT)
        message(FATAL_ERROR "Boost bootstrap.bat failed: ${BOOTSTRAP_ERROR}")
    else()

        execute_process(
            COMMAND b2 headers
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0
        )

        execute_process(
            COMMAND b2 stage --with-thread --with-system --with-python address-model=64 --debug-configuration
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tools/boost_1_86_0
        )
    endif()

endif()

# Manually create the Boost::boost target
add_library(Boost::boost INTERFACE IMPORTED)
set_target_properties(Boost::boost PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
)

set(Boost_library
    ${Boost_LIBRARY_DIRS}/libboost_thread-mgw13-mt-x64-1_86.a
    ${Boost_LIBRARY_DIRS}/libboost_system-mgw13-mt-x64-1_86.a
    ${Boost_LIBRARY_DIRS}/libboost_chrono-mgw13-mt-x64-1_86.a
   # ${Boost_LIBRARY_DIRS}/libboost_python312-mgw13-mt-x64-1_86.a
   # ${Boost_LIBRARY_DIRS}/libboost_numpy312-mgw13-mt-x64-1_86.a
    pthread
    )

message(STATUS "Boost include directory: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost library directory: ${Boost_LIBRARY_DIRS}")

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googletest)