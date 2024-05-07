cmake_minimum_required(VERSION 3.22)

project(fbx-import)


if(MSVC)
    message(STATUS "[fbx] type : ${VS_CONFIGURATION_TYPE}")
else()
    message(FATAL_ERROR "fbx 2018 sdk support msvc only")
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
    message("[fbx] built type not defined")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "build type" FORCE)
else()
    message(STATUS "[fbx] build type : ${CMAKE_BUILD_TYPE}")
endif()

set(FBX_DOWNLOAD_DIR ${CMAKE_CURRENT_LIST_DIR}/fbxsdk-2018)
set(FBX_SRC_INC_DIR ${FBX_DOWNLOAD_DIR}/include)
set(FBX_SRC_LIB_DIR ${FBX_DOWNLOAD_DIR}/lib)
#set(FBX_INTERFACE_LIBS libxml2-md.lib zlib-md.lib) #casecade libs
set(FBX_MAIN_LIB libfbxsdk.lib)
set(FBX_DLL libfbxsdk.dll)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

if(NOT DEFINED fbx_BIN_DIR)
    set(fbx_BIN_DIR ${BIN_DIR})
endif()

set(fbx_dll_debug ${FBX_DOWNLOAD_DIR}/lib/Debug/libfbxsdk.dll)
set(fbx_dll_release ${FBX_DOWNLOAD_DIR}/lib/Release/libfbxsdk.dll)
set(fbx_dll_bin ${fbx_BIN_DIR}/libfbxsdk.dll)

#create imported library for pre built
add_library(fbx SHARED IMPORTED)
set_target_properties(fbx PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${FBX_SRC_INC_DIR}"
    INTERFACE_LINK_DIRECTORIES "${FBX_SRC_LIB_DIR}"
    #INTERFACE_LINK_LIBRARIES "${FBX_INTERFACE_LIBS}"
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
    IMPORTED_IMPLIB_DEBUG "${FBX_SRC_LIB_DIR}/Debug/${FBX_MAIN_LIB}"
    IMPORTED_IMPLIB_RELEASE "${FBX_SRC_LIB_DIR}/Release/${FBX_MAIN_LIB}"
    IMPORTED_LOCATION "${FBX_SRC_LIB_DIR}/${FBX_DLL}"
    MAP_IMPORTED_CONFIG_RELWITHDEBINFO "Release"
    MAP_IMPORTED_CONFIG_MINSIZEREL "Release"
)
add_library(lib::fbx ALIAS fbx)

if(EXISTS ${fbx_dll_bin})
    message(STATUS "[fbx] ${CMAKE_BUILD_TYPE}")
endif()

if(NOT EXISTS ${BIN_DIR}/${FBX_DLL})
    message(STATUS "[fbx] ${FBX_DLL} no exist")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${FBX_SRC_LIB_DIR}/${CMAKE_BUILD_TYPE}/${FBX_DLL}
    ${BIN_DIR}/${FBX_DLL}
    RESULT_VARIABLE res
    )
    if(res)
    message(STATUS "copy ${res}")
    endif()
else()
    if(${BIN_DIR}/${FBX_DLL} STREQUAL ${FBX_SRC_LIB_DIR}/${FBX_DLL})
    message(STATUS "[fbx] ${FBX_DLL} is exist already.")
    endif()
endif()


option(FBX_BUILD_EXAMPLE ON)

# if(FBX_BUILD_EXAMPLE)
#     add_subdirectory(fbx-exmaple)
# endif()

# add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD 
#     COMMAND echo "build from custom command $<CONFIG>"
# )

add_subdirectory(fbx-exmaple)

file(SIZE ${BIN_DIR}/${FBX_DLL} size)

message(STATUS "${FBX_DLL} size ${size}")

add_custom_target(final ALL
    #DEPENDS ${ALL_TARGETS}
    COMMAND ${CMAKE_COMMAND} -E echo "--- ---- $<CONFIG>"
)

add_custom_target( FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over!"
    COMMENT "Final Message" )
#add_dependencies( FinalMessage ${ALL_TARGETS} )

#add_custom_command(TARGET)

message(STATUS ${BUILDSYSTEM_TARGETS})



# get_property(target DIRECTORY fbx-exmaple PROPERTY BUILDSYSTEM_TARGETS)

# include(CMakePrintHelpers)

# cmake_print_variables(target)

# foreach(trg  target)
#     cmake_print_variables(${trg})
#     #get_target_property(outa ${trg} NAME)
#     get_target_property(dir ${trg} INCLUDE_DIRECTORIES)
#     cmake_print_variables(dir)
# endforeach()




