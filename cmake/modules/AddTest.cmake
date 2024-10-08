include(CompileWarnings)

macro(wpilib_add_test name srcdir)
    file(GLOB_RECURSE test_src ${srcdir}/*.cpp)
    if(NOT WITH_PROTOBUF)
        list(FILTER test_src EXCLUDE REGEX "/proto/")
    endif()
    add_executable(${name}_test ${test_src})
    set_property(TARGET ${name}_test PROPERTY FOLDER "tests")
    wpilib_target_warnings(${name}_test)
    if(BUILD_SHARED_LIBS)
        target_compile_definitions(${name}_test PRIVATE -DGTEST_LINKED_AS_SHARED_LIBRARY)
    endif()
    if(MSVC)
        target_compile_options(${name}_test PRIVATE /wd4101 /wd4251)
    endif()
    add_test(NAME ${name} COMMAND ${name}_test)
endmacro()
