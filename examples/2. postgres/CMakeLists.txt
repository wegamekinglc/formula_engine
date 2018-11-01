file(GLOB_RECURSE PG_FILES "*.hpp" "*.cpp")

add_executable(postgres ${PG_FILES})

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(postgres libpqxxD)
else()
    target_link_libraries(postgres libpqxx)
endif()

install(TARGETS postgres
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )