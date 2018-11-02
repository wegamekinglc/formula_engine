file(GLOB_RECURSE PG_FILES "*.hpp" "*.cpp")

add_executable(postgres ${PG_FILES})

target_link_libraries(postgres ${FEL_LINK_LIBRARY})

install(TARGETS postgres
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )