cmake_minimum_required(VERSION "3.22.0")

project("ReqEx")

include_directories("${PROJECT_SOURCE_DIR}")
add_executable("${PROJECT_NAME}" "main.cpp" "Storage.cpp" "Parse.cpp")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")
set_target_properties("${PROJECT_NAME}" PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "Test1.cpp")
install(FILES "main.cpp" DESTINATION src)
