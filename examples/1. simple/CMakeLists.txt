file(GLOB_RECURSE SIMPLE_FILES "*.hpp" "*.cpp")

add_executable(simple ${SIMPLE_FILES})

target_link_libraries(simple ${FEL_LINK_LIBRARY})
if(WIN32)
else()
    target_link_libraries(simple pqxx)
    target_link_libraries(simple pq)
endif()

install(TARGETS simple
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)