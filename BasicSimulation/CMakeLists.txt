cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(BasicSimulation)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/../Engine/core/*.cpp
    ${CMAKE_SOURCE_DIR}/../Engine/utils/*.cpp
    ${CMAKE_SOURCE_DIR}/../Engine/renderer/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/../Engine/core/headers/*.hpp
    ${CMAKE_SOURCE_DIR}/../Engine/utils/*.hpp
    ${CMAKE_SOURCE_DIR}/../Engine/math/*.hpp
    ${CMAKE_SOURCE_DIR}/../Engine/renderer/headers/*.hpp)

find_package(SDL2 REQUIRED)
set(NLOHMANN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/nlohmann")

# Support both 32 and 64 bit Windows builds
if (WIN32)
    # Currently text support only available in Windows
    set(SDL_TTF_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/SDL2_ttf-2.0.15")
    set(FREETYPE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include/freetype-2.9.1/include")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/../lib/x64/SDL2main.lib")
        set(SDL2_TTF_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/SDL_ttf/x64/SDL2_ttf.lib")
    else ()
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/../lib/x86/SDL2main.lib")
        set(SDL2_TTF_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../lib/SDL_ttf/x86/SDL2_ttf.lib")
    endif ()
    set(FREETYPE_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/../lib/libfreetype-6.lib")
endif (WIN32)

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

if (WIN32)
    include_directories(${SDL2_INCLUDE_DIRS} ${NLOHMANN_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})  
else ()
    include_directories(${SDL2_INCLUDE_DIRS} ${NLOHMANN_INCLUDE_DIRS})  
endif ()

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${FREETYPE_LIBRARY} ${SDL2_TTF_LIBRARIES})
else ()
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif ()