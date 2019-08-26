cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(BasicSimulation)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/../Engine/core/*.cpp
    ${CMAKE_SOURCE_DIR}/../Engine/interface/*.cpp
    ${CMAKE_SOURCE_DIR}/../Engine/renderer/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/../Engine/core/headers/*.hpp
    ${CMAKE_SOURCE_DIR}/../Engine/interface/*.hpp
    ${CMAKE_SOURCE_DIR}/../Engine/math/*.hpp
    ${CMAKE_SOURCE_DIR}/../Engine/renderer/headers/*.hpp)


set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")
set(NLOHMANN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/nlohmann")
set(SDL_TTF_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/SDL2_ttf-2.0.15")
set(FREETYPE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/freetype-2.9.1/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/../lib/x64/SDL2main.lib")
  set(SDL2_TTF_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/SDL_ttf/x64/SDL2_ttf.lib")
else ()
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/../lib/x86/SDL2main.lib")
  set(SDL2_TTF_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/SDL_ttf/x86/SDL2_ttf.lib")
endif ()

set(FREETYPE_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/../lib/libfreetype-6.lib")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS} ${NLOHMANN_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${FREETYPE_LIBRARY} ${SDL2_TTF_LIBRARIES})