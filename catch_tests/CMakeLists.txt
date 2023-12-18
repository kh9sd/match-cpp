add_compile_options("${WARNINGS_LIST}")

# currently we have a mini convention that executables use underscores (ex. exe_name)
# while libraries use hyphens (ex. lib-name)
# we can probably change this later if it's unhelpful/straight up harmful

# building tests for watchdog and redlines
add_subdirectory(watchdog)
add_executable(watchdog_tests
        catch_runner.cpp)
target_link_libraries(watchdog_tests PRIVATE
        watchdog-tests-lib)

# building tests for everything
# if you add a new test lib, don't forget to add it here
add_executable(all_tests
        catch_runner.cpp)
target_link_libraries(all_tests PRIVATE
        watchdog-tests-lib)
