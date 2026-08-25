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

# Common and Raven now live in External/, so they need their own glob -
# Source/CMakeLists.txt only covers Source/.
file(GLOB_RECURSE COMMON_HEADERS CONFIGURE_DEPENDS "${EXTERNAL_ROOT_DIR}/Common/*.h")
file(GLOB_RECURSE COMMON_CPPS    CONFIGURE_DEPENDS "${EXTERNAL_ROOT_DIR}/Common/*.cpp")
file(GLOB_RECURSE RAVEN_HEADERS  CONFIGURE_DEPENDS "${EXTERNAL_ROOT_DIR}/Raven/*.h")
file(GLOB_RECURSE RAVEN_CPPS     CONFIGURE_DEPENDS "${EXTERNAL_ROOT_DIR}/Raven/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${COMMON_HEADERS} ${COMMON_CPPS} ${RAVEN_HEADERS} ${RAVEN_CPPS})

# Replicate the Source/Common/Raven folder hierarchies as VS solution filters.
# Common and Raven live under External/ on disk, so they're nested under an
# "External" filter too, alongside raylib/raygui below.
source_group(TREE "${PROJECT_ROOT_DIR}/Source" PREFIX "Source" FILES ${SOURCE_HEADERS_CLIENT} ${SOURCE_CPPS_CLIENT})
source_group(TREE "${EXTERNAL_ROOT_DIR}/Common" PREFIX "External/Common" FILES ${COMMON_HEADERS} ${COMMON_CPPS})
source_group(TREE "${EXTERNAL_ROOT_DIR}/Raven" PREFIX "External/Raven" FILES ${RAVEN_HEADERS} ${RAVEN_CPPS})

# Add libraries HEADER
target_include_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}/raylib/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}/raygui")
target_include_directories(${PROJECT_NAME} PUBLIC "${EXTERNAL_ROOT_DIR}")

# raygui's single-translation-unit implementation lives alongside the header in
# External/raygui (compiled as C — see the comment in raygui_impl.c for why).
target_sources(${PROJECT_NAME} PRIVATE "${EXTERNAL_ROOT_DIR}/raygui/raygui_impl.c")

# raylib/raygui: add their top-level files (headers + the .c modules raylib's
# own build compiles into the prebuilt raylib.lib we link against below) so
# they're browsable in the Visual Studio solution. The .c files are marked
# HEADER_FILE_ONLY so VS shows them without compiling/linking them a second
# time (that would duplicate symbols already in raylib.lib). raygui.h gets the
# same treatment for consistency; raygui_impl.c above is a real, compiled
# source and is left alone.
file(GLOB RAYLIB_LIB_FILES "${EXTERNAL_ROOT_DIR}/raylib/include/*.h" "${EXTERNAL_ROOT_DIR}/raylib/include/*.c")
file(GLOB RAYGUI_LIB_HEADERS "${EXTERNAL_ROOT_DIR}/raygui/*.h")
set(RAYLIB_LIB_CPPS ${RAYLIB_LIB_FILES})
list(FILTER RAYLIB_LIB_CPPS INCLUDE REGEX "\\.c$")
set_source_files_properties(${RAYLIB_LIB_CPPS} PROPERTIES HEADER_FILE_ONLY TRUE)
target_sources(${PROJECT_NAME} PRIVATE ${RAYLIB_LIB_FILES} ${RAYGUI_LIB_HEADERS})
source_group(TREE "${EXTERNAL_ROOT_DIR}/raylib/include" PREFIX "External/raylib" FILES ${RAYLIB_LIB_FILES})
source_group("External/raygui" FILES ${RAYGUI_LIB_HEADERS} "${EXTERNAL_ROOT_DIR}/raygui/raygui_impl.c")

# Raven and Common now live in External/ (as a shared submodule dependency) so
# their many "#include \"2D/Vector2D.h\""-style includes keep resolving via
# these dirs. Common's own subfolders (2D, Game, Graph, misc, fuzzy) don't need
# their own entries: every cross-folder include is already written with that
# prefix (resolved via the "External/Common" entry below), and same-folder
# includes resolve via the includer's own directory regardless of -I flags.
target_include_directories(${PROJECT_NAME} PUBLIC
    "${EXTERNAL_ROOT_DIR}/Raven"
    "${EXTERNAL_ROOT_DIR}/Common"
    "${PROJECT_ROOT_DIR}/Source/Game")

# Raven loads maps/*.map with paths relative to the process's working directory,
# so copy them next to the built exe.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${EXTERNAL_ROOT_DIR}/Raven/maps" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/maps"
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