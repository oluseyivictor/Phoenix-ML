if(ENABLE_TESTING)

    set(TEST_SOURCES
        "ADT/matvec.cpp")

    add_executable(testRunner  ${TEST_SOURCES} )
    target_link_libraries(testRunner ${LIBRARY_NAME} GTest::gtest_main)

endif()