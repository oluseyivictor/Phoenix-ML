

#add_executable(${EXECUTABLE_NAME} test.cpp)
#add_library(${EXECUTABLE_NAME} SHARED binding.cpp)

add_library(${EXECUTABLE_NAME} SHARED "wlinear.cpp")
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})


#target_compile_options(${LIBRARY_NAME} PRIVATE -fPIC)