get_fe_library_name(FE_OUTPUT_NAME)

file(GLOB_RECURSE FE_EILES "*.hpp" "*.cpp")

if(WIN32)
    if (${BUILD_SHARED_LIBS})
        message(FATAL_ERROR "You should build in STATIC mode as nothing is exported from the library. Use BUILD_SHARED_LIBS=OFF")
    endif()
    add_library(${FE_OUTPUT_NAME} ${FE_EILES})
    set_property(TARGET ${FE_OUTPUT_NAME} PROPERTY PROJECT_LABEL "fel")
else()
    add_library(${FE_OUTPUT_NAME} ${FE_EILES})
endif()

install(DIRECTORY . DESTINATION include/fengine
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")
set(FE_LINK_LIBRARY ${FE_OUTPUT_NAME} PARENT_SCOPE)

install(TARGETS ${FE_OUTPUT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)