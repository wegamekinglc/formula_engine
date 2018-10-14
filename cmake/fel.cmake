cmake_minimum_required(VERSION 3.0)
macro(get_fe_library_name FE_OUTPUT_NAME)
message(STATUS "fe library name tokens:")
# MSVC: Give QuantLib built library different names following code in 'ql/autolink.hpp'
if (MSVC)
    # - toolset
    # ...taken from FindBoost.cmake
    if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.10)
        set(FE_LIB_TOOLSET "-vc141")
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19)
        set(FE_LIB_TOOLSET "-vc140")
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18)
        set(FE_LIB_TOOLSET "-vc120")
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
        set(FE_LIB_TOOLSET "-vc110")
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
        set(FE_LIB_TOOLSET "-vc100")
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15)
        set(FE_LIB_TOOLSET "-vc90")
    else ()
        message(FATAL_ERROR "Compiler below vc90 is not supported")
    endif ()
    message(STATUS " - Toolset: ${FE_LIB_TOOLSET}")

    # - platform
    if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
        set(FE_LIB_PLATFORM "-x64")
    endif ()
    message(STATUS " - Platform: ${FE_LIB_PLATFORM}")
    # - thread linkage
    set(FE_LIB_THREAD_OPT "-mt")  # _MT is defined for /MD and /MT runtimes (https://docs.microsoft.com/es-es/cpp/build/reference/md-mt-ld-use-run-time-library)
    message(STATUS " - Thread opt: ${FE_LIB_THREAD_OPT}")

    # - static/dynamic linkage
    if (${MSVC_RUNTIME} STREQUAL "static")
        set(FE_LIB_RT_OPT "-s")
        set(CMAKE_DEBUG_POSTFIX "gd")
    else ()
        set(CMAKE_DEBUG_POSTFIX "-gd")
    endif ()
    message(STATUS " - Linkage opt: ${FE_LIB_RT_OPT}")

    set(${FE_OUTPUT_NAME} "fel${FE_LIB_TOOLSET}${FE_LIB_PLATFORM}${FE_LIB_THREAD_OPT}${FE_LIB_RT_OPT}")
else ()
    set(${FE_OUTPUT_NAME} "fel")
endif ()
if(${CMAKE_BUILD_TYPE} MATCHES Release)
    message(STATUS "fe library name: ${${FE_OUTPUT_NAME}}")
else()
    message(STATUS "fe library name: ${${FE_OUTPUT_NAME}}${CMAKE_DEBUG_POSTFIX}")
endif()
endmacro(get_fe_library_name)

macro(configure_msvc_runtime)
# Credit: https://stackoverflow.com/questions/10113017/setting-the-msvc-runtime-in-cmake
if (MSVC)
    # Default to dynamically-linked runtime.
    if ("${MSVC_RUNTIME}" STREQUAL "")
        set(MSVC_RUNTIME "dynamic")
    endif ()

    # Set compiler options.
    set(variables
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
            )

    if (${MSVC_RUNTIME} STREQUAL "static")
        message(STATUS "MSVC -> forcing use of statically-linked runtime.")
        foreach (variable ${variables})
            if (${variable} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
            endif ()
        endforeach ()
    else ()
        message(STATUS "MSVC -> forcing use of dynamically-linked runtime.")
        foreach (variable ${variables})
            if (${variable} MATCHES "/MT")
                string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
            endif ()
        endforeach ()
    endif ()
endif ()
endmacro()