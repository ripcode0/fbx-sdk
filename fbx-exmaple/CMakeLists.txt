
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

add_executable(fbx-example main.cpp)

set_target_properties(fbx-example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}
    CMAKE_CONFIGURATION_TYPES "Release;Debug"
    #COMPILE_OPTIONS 
)

target_link_libraries(fbx-example PUBLIC lib::fbx)

add_dependencies(fbx-example lib::fbx)

get_target_property(FBX lib::fbx ALIASED_TARGET)

message(STATUS "aaa ${FBX}")
# add_custom_command(
#     TARGET fbx-import
#     PRE_LINK
#     COMMAND echo "build from custom command $<CONFIG>"
# )



