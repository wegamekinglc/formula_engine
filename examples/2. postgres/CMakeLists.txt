file(GLOB_RECURSE PG_FILES "*.hpp" "*.cpp")

add_executable(postgres ${PG_FILES})

target_link_libraries(postgres ${FEL_LINK_LIBRARY})
if(WIN32)
else()
    target_link_libraries(postgres pqxx)
    target_link_libraries(postgres pq)
endif()

install(TARGETS postgres
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )