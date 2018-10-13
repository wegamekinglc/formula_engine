cmake_minimum_required(VERSION 3.0)

project(FormulaEngin VERSION 1.0.0)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/fel.cmake)

if(MSVC)
    # Remove warnings
    INCLUDE_DIRECTORIES($ENV{GTEST_ROOT}/include)

    set(MSVC_RUNTIME "dynamic" CACHE STRING "MSVC runtime to link")
    set_property(CACHE MSVC_RUNTIME PROPERTY STRINGS static dynamic)

    if ("${MSVC_RUNTIME}" STREQUAL "static")
        link_directories($ENV{GTEST_ROOT}/lib/${CMAKE_BUILD_TYPE}/MT)
    else()
        link_directories($ENV{GTEST_ROOT}/lib/${CMAKE_BUILD_TYPE}/MD)
    endif()

    configure_msvc_runtime()
    add_definitions(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
else()
    set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)