if(BUILD_TESTING)
    find_package(Core REQUIRED)

    include(GoogleTest)

    add_executable(Test 
        src/vector_tests.cpp
        src/linked_list_tests.cpp
        src/stack_tests.cpp)

    target_link_libraries(
        Test
            PUBLIC
                Core::Core
            PRIVATE
                GTest::gtest
                GTest::gtest_main
                GTest::gmock
                GTest::gmock_main
                )

    gtest_discover_tests(Test)
endif()
