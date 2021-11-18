project(select)

add_executable(${PROJECT_NAME}.server server.c)
target_link_libraries(${PROJECT_NAME}.server wrap)

add_executable(${PROJECT_NAME}.client client.c)
target_link_libraries(${PROJECT_NAME}.client wrap)