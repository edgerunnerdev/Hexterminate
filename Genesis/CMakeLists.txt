cmake_minimum_required(VERSION 3.14)
project(Genesis)

add_subdirectory("ext/soloud20200207")
add_subdirectory("libs/imgui")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/src FILES ${SOURCE_FILES})

find_package(imgui REQUIRED)
find_package(GLM REQUIRED)
find_package(soloud REQUIRED)

include_directories(
  src/ 
  ${IMGUI_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${SOLOUD_INCLUDE_DIRS}
)

add_library(Genesis STATIC ${SOURCE_FILES})
set_target_properties(Genesis PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/libs/Genesis/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE})

if(WIN32)
    target_compile_definitions(Genesis PRIVATE UNICODE _UNICODE _HASEXCEPTIONS=0)
    target_compile_options(Genesis PUBLIC $<$<CONFIG:Debug>:/MTd> $<$<CONFIG:Release>:/MT>)
    target_compile_options(Genesis PUBLIC $<$<CONFIG:Release>:/Ob2 /GL>)
    target_compile_options(Genesis PUBLIC /Zi) # Debug information format: Program database.
    target_compile_options(Genesis PUBLIC /MP) # Enable parallel compilation.
endif()

target_link_libraries(Genesis PRIVATE GLEW::GLEW)
target_link_libraries(Genesis PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(Genesis PRIVATE SDL2::SDL2_image)
target_link_libraries(Genesis PRIVATE LinearMath Bullet3Common BulletDynamics BulletCollision)

target_compile_definitions(Genesis PRIVATE $<$<CONFIG:Debug>:_DEBUG>)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
     target_compile_options(Genesis PRIVATE
          -Wall 
          -Werror
          -Wno-reorder-ctor
          -fstandalone-debug
     )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
     target_compile_options(Genesis PRIVATE
          -Wall 
          -Werror
          -Wno-reorder-ctor
          -g # generate debug symbols
     )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
     target_compile_options(Genesis PRIVATE
          /W4
          /WX # warnings as errors
          /wd4100 # unreferenced formal parameter
          /wd4121 # alignment of a member was sensitive to packing
          /wd4127 # conditional expression is constant
          /wd4505 # unreferenced local function has been removed
          /wd4189 # local variable is initialized but not referenced
          /wd4201 # nonstandard extension used : nameless struct/union
          /wd4702 # unreachable code
     )
endif()

target_compile_definitions(Genesis PRIVATE $<$<CONFIG:Debug>:OPENGL_ERROR_CHECKING=1>)