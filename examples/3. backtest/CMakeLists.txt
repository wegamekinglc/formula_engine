file(GLOB_RECURSE BT_FILES "*.hpp" "*.cpp")

add_executable(backtest ${BT_FILES})

target_link_libraries(backtest ${FEL_LINK_LIBRARY})
if(WIN32)
else()
    target_link_libraries(backtest pqxx)
    target_link_libraries(backtest pq)
endif()

install(TARGETS backtest
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)