# Sample Version Of CMake minimum setup
cmake_minimum_required(VERSION 3.15)

#Project name and version
project(RaylibBasic VERSION 0.1 LANGUAGES CXX C)

# Set path 
set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(EXTERNAL_ROOT_DIR "${PROJECT_ROOT_DIR}/External")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_ROOT_DIR}/Bin")

message(STATUS "PROJECT_ROOT_DIR: ${PROJECT_ROOT_DIR}")
message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")

# Compiler setup
if (MSVC)
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    # Clang all warning
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# configure header file to pass version number
configure_file("${PROJECT_ROOT_DIR}/Source/CMakeConfig.h.in" "${PROJECT_ROOT_DIR}/Source/CMakeConfig.h")

# Add source to your executable :
add_executable(${PROJECT_NAME})

# Setup generated project
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RaylibBasic)

# Add sources (sets SOURCE_HEADERS_CLIENT and SOURCE_CPPS_CLIENT in this scope)
add_subdirectory(Source)

# Replicate the Source folder hierarchy as VS solution filters
source_group(TREE "${PROJECT_ROOT_DIR}/Source" PREFIX "Source" FILES ${SOURCE_HEADERS_CLIENT} ${SOURCE_CPPS_CLIENT})

# Add libraries HEADER
target_include_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}/raylib/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}/raygui")
target_include_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}")

# raygui's single-translation-unit implementation lives alongside the header in
# External/raygui (compiled as C — see the comment in raygui_impl.c for why).
target_sources(${PROJECT_NAME} PRIVATE "${EXTERNAL_ROOT_DIR}/raygui/raygui_impl.c")

# Raven (Buckland Chapter 7-10) sources live as siblings under Source/ so its many
# "..\Common\..." style relative includes keep resolving the same way they did in
# the original project layout.
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_ROOT_DIR}/Source/Raven"
    "${PROJECT_ROOT_DIR}/Source/Common"
    "${PROJECT_ROOT_DIR}/Source/Common/2D"
    "${PROJECT_ROOT_DIR}/Source/Common/Game"
    "${PROJECT_ROOT_DIR}/Source/Common/Graph"
    "${PROJECT_ROOT_DIR}/Source/Common/misc"
    "${PROJECT_ROOT_DIR}/Source/Common/Debug"
    "${PROJECT_ROOT_DIR}/Source/Common/fuzzy")

# Raven loads maps/*.map with paths relative to the process's working directory,
# so copy them next to the built exe.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_ROOT_DIR}/Source/Raven/maps" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/maps"
    COMMENT "Copying Raven maps/ next to the built exe")

# Determine architecture folder (x64 / Win32) like the MSBuild $(Platform) macro
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(RAYLIB_ARCH "x64")
else()
    set(RAYLIB_ARCH "Win32")
endif()

# Link libraries BINARY
# $<CONFIG> replaces the MSBuild $(Configuration) macro and works with every generator (Ninja, VS, ...)
target_link_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}/raylib/lib/${RAYLIB_ARCH}/$<CONFIG>")
target_link_libraries(${PROJECT_NAME} raylib winmm)

# set Raylib definitions
add_compile_definitions(GRAPHICS_API_OPENGL_33 PLATFORM_DESKTOP)

# set target properties
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Raven's maps/ get copied next to the exe (see POST_BUILD step above), so debug
# from that directory too.
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")