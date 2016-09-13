
cmake_minimum_required(VERSION 2.8.12)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Build process cannot start from project source directory")
endif()

project("elements")

if(MSVC)
  # if(NOT CHARACTER_SET)
  #   add_definitions(-D_UNICODE -DUNICODE)
  # else()
    add_definitions(-D_MBCS)
  # endif()
  add_definitions(-DNOMINMAX)
  # message(FATAL_ERROR "Could not support Visual Studio")
endif()

if(WIN32)
  add_definitions(-DWIN32)
  add_definitions(-D_WIN32)
  add_definitions(-D_WINDOWS)
  add_definitions(-DNOCOMM)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-D_WIN32_WINNT=0x0500)
endif()

set(REQUIRED_INCLUDES)
set(REQUIRED_LIBRARIES)
set(REQUIRED_SYS_INCLUDES)

if(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
  list(APPEND REQUIRED_SYS_INCLUDES /usr/local/include/)
  link_directories(${LINK_DIRECTORIES} /usr/local/lib/)
endif()

# freetype
if(WIN32 OR UNIX)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/freetype)
    set(freetype_Path ${CMAKE_SOURCE_DIR}/third-party/freetype)
  elseif(EXISTS ${CMAKE_SOURCE_DIR}/third-party/freetype-2.6.2)
    set(freetype_Path ${CMAKE_SOURCE_DIR}/third-party/freetype-2.6.2)
  elseif(DEFINED ENV{FREETYPE_PATH})
    string(REPLACE "\\" "/" freetype_Path $ENV{FREETYPE_PATH})
  elseif(DEFINED FREETYPE_PATH)
    string(REPLACE "\\" "/" freetype_Path ${FREETYPE_PATH})
  else()
    message(FATAL_ERROR "Could not find freetype library, please check it at https://sourceforge.net/projects/freetype/files/")
  endif()

  if(MSVC)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      add_definitions(-DFT_CONFIG_OPTION_NO_ASSEMBLER)
    endif()
  endif()

  add_subdirectory(${freetype_Path} ${CMAKE_BINARY_DIR}/freetype)

  list(APPEND REQUIRED_SYS_INCLUDES ${freetype_Path}/include)
endif()

# glew
if(WIN32)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/glew)
    set(glew_Path ${CMAKE_SOURCE_DIR}/third-party/glew)
  elseif(DEFINED ENV{GLEW_PATH})
    string(REPLACE "\\" "/" glew_Path $ENV{GLEW_PATH})
  elseif(DEFINED GLEW_PATH)
    string(REPLACE "\\" "/" glew_Path ${GLEW_PATH})
  else()
    message(FATAL_ERROR "Could not find glew library, please check it at https://github.com/nigels-com/glew/releases")
  endif()

  set(C_FILES ${glew_Path}/src/glew.c)
  file(GLOB_RECURSE INC_FILES ${glew_Path}/include/*.h)

  add_library(GLEW STATIC ${INC_FILES} ${C_FILES})

  target_include_directories(GLEW SYSTEM PRIVATE ${glew_Path}/include)
  add_definitions(-DGLEW_STATIC)

  if(MSVC)
    set_target_properties(GLEW PROPERTIES COMPILE_FLAGS "/W0")
  else()
    set_target_properties(GLEW PROPERTIES COMPILE_FLAGS "-w")
  endif(MSVC)
  list(APPEND REQUIRED_SYS_INCLUDES ${glew_Path}/include)
endif()

# glfw
if(UNIX)
  add_definitions(-DGLFW_EXPOSE_NATIVE_X11)
  add_definitions(-DGLFW_EXPOSE_NATIVE_GLX)
else()
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/glfw)
    set(glfw_Path ${CMAKE_SOURCE_DIR}/third-party/glfw)
  elseif(DEFINED ENV{GLFW_PATH})
    string(REPLACE "\\" "/" glfw_Path $ENV{GLFW_PATH})
  elseif(DEFINED GLFW_PATH)
    string(REPLACE "\\" "/" glfw_Path ${GLFW_PATH})
  else()
    message(FATAL_ERROR "Could not find glfw library, please check it at https://github.com/glfw/glfw/releases")
  endif()

  add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32)
  add_definitions(-DGLFW_EXPOSE_NATIVE_WGL)

  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory(${glfw_Path} ${CMAKE_BINARY_DIR}/glfw)

  list(APPEND REQUIRED_SYS_INCLUDES ${glfw_Path}/include)
endif()

# glm
if(WIN32)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/glm)
    set(glm_Path ${CMAKE_SOURCE_DIR}/third-party/glm)
  elseif(DEFINED ENV{GLM_PATH})
    string(REPLACE "\\" "/" glm_Path $ENV{GLM_PATH})
  elseif(DEFINED GLM_PATH)
    string(REPLACE "\\" "/" glm_Path ${GLM_PATH})
  else()
    message(FATAL_ERROR "Could not find glm library, please check it at https://github.com/g-truc/glm/releases")
  endif()
  list(APPEND REQUIRED_SYS_INCLUDES ${glm_Path})
endif()

# libpng
if(WIN32)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/libpng)
    set(libpng_Path ${CMAKE_SOURCE_DIR}/third-party/libpng)
  elseif(DEFINED ENV{LIBPNG_PATH})
    string(REPLACE "\\" "/" libpng_Path $ENV{LIBPNG_PATH})
  elseif(DEFINED LIBPNG_PATH)
    string(REPLACE "\\" "/" libpng_Path ${LIBPNG_PATH})
  else()
    message(FATAL_ERROR "Could not find libpng library, please check it at https://sourceforge.net/projects/libpng/files/")
  endif()

  file(GLOB LIBPNG_SRC_FILES ${libpng_Path}/*.h ${libpng_Path}/*.c)
  list(REMOVE_ITEM LIBPNG_SRC_FILES ${libpng_Path}/example.c ${libpng_Path}/pngtest.c)
  add_library(libpng STATIC ${LIBPNG_SRC_FILES})
  target_include_directories(libpng SYSTEM PRIVATE ${zlib_Path})
  list(APPEND REQUIRED_SYS_INCLUDES ${libpng_Path})
endif()

# pugixml
if(WIN32)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/pugixml)
    set(pugixml_Path ${CMAKE_SOURCE_DIR}/third-party/pugixml)
  elseif(DEFINED ENV{PUGIXML_PATH})
    string(REPLACE "\\" "/" pugixml_Path $ENV{PUGIXML_PATH})
  elseif(DEFINED PUGIXML_PATH)
    string(REPLACE "\\" "/" pugixml_Path ${PUGIXML_PATH})
  else()
    message(FATAL_ERROR "Could not find pugixml library, please check it at https://github.com/zeux/pugixml/releases")
  endif()

  file(GLOB PUGIXML_SRC_FILES ${pugixml_Path}/src/*.hpp ${pugixml_Path}/src/*.cpp)
  add_library(pugixml STATIC ${PUGIXML_SRC_FILES})
  list(APPEND REQUIRED_SYS_INCLUDES ${pugixml_Path}/src)
endif()

# assimp
if(WIN32)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/assimp/code)
    set(assimp_Path ${CMAKE_SOURCE_DIR}/third-party/assimp)
  elseif(EXISTS ${CMAKE_SOURCE_DIR}/third-party/assimp-3.2/code)
    set(assimp_Path ${CMAKE_SOURCE_DIR}/third-party/assimp-3.2)
  elseif(DEFINED ENV{ASSIMP_PATH})
    string(REPLACE "\\" "/" assimp_Path $ENV{ASSIMP_PATH})
  elseif(DEFINED ASSIMP_PATH)
    string(REPLACE "\\" "/" assimp_Path ${ASSIMP_PATH})
  else()
    message(FATAL_ERROR "Could not find assimp library, please check it at https://github.com/assimp/assimp/releases")
  endif()

  set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
  set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
  # ASSIMP_NO_EXPORT
  # ASSIMP_BUILD_ZLIB
  # ASSIMP_BUILD_ASSIMP_VIEW
  # ASSIMP_INSTALL_PDB
  add_subdirectory(${assimp_Path} ${CMAKE_BINARY_DIR}/assimp)

  list(APPEND REQUIRED_SYS_INCLUDES ${assimp_Path}/include)
endif()

# z
if(WIN32)
  if(EXISTS ${assimp_Path}/contrib/zlib)
    set(zlib_Path ${assimp_Path}/contrib/zlib)
  elseif(EXISTS ${CMAKE_SOURCE_DIR}/third-party/zlib)
    set(zlib_Path ${CMAKE_SOURCE_DIR}/third-party/zlib)
  elseif(DEFINED ENV{ZLIB_PATH})
    string(REPLACE "\\" "/" zlib_Path $ENV{ZLIB_PATH})
  elseif(DEFINED ZLIB_PATH)
    string(REPLACE "\\" "/" zlib_Path ${ZLIB_PATH})
  else()
    message(FATAL_ERROR "Could not find zlib library, please check it at https://sourceforge.net/projects/libpng/files/zlib/")
  endif()

  file(GLOB ZLIB_SRC_FILES ${zlib_Path}/*.h ${zlib_Path}/*.c)
  add_library(z STATIC ${ZLIB_SRC_FILES})
  list(APPEND REQUIRED_SYS_INCLUDES ${zlib_Path})
endif()

# oel
set(oel_Path ${CMAKE_SOURCE_DIR}/third-party/oel)
file(GLOB OEL_SRC_FILES ${oel_Path}/*.h ${oel_Path}/*.cpp)
add_library(oel ${OEL_SRC_FILES})
target_include_directories(oel SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${oel_Path})

# elements
set(elements_Path ${CMAKE_SOURCE_DIR}/elements)
file(GLOB_RECURSE ELEMENTS_SRC_FILES ${elements_Path}/*.h ${elements_Path}/*.cpp)

add_library(elements ${ELEMENTS_SRC_FILES})
target_include_directories(elements PRIVATE ${elements_Path})
target_include_directories(elements SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${elements_Path})

# platform library
set(platform_Path ${CMAKE_SOURCE_DIR}/platform/desktop)
file(GLOB PLATFORM_SRC_FILES ${platform_Path}/*.h ${platform_Path}/*.cpp
                             ${platform_Path}/Library/*.h ${platform_Path}/Library/*.cpp)
add_library(desktop ${PLATFORM_SRC_FILES})
target_include_directories(desktop PRIVATE ${REQUIRED_INCLUDES})
target_include_directories(desktop SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${platform_Path})

# Copy assets
file(GLOB WALLPAPER_FOLDERS RELATIVE ${CMAKE_SOURCE_DIR}/platform/android/elements ${CMAKE_SOURCE_DIR}/platform/android/elements/*Wallpaper)
file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_SOURCE_DIR}/assets/*
                                 ${CMAKE_SOURCE_DIR}/platform/android/elements/*Wallpaper/src/main/assets/*)

add_custom_target(copyAssets)

foreach(RESOURCE_FILE ${RESOURCE_FILES})
  string(REPLACE "//" "/" sourcePath ${RESOURCE_FILE})
  string(REPLACE ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets destination ${sourcePath})

  foreach(WALLPAPER ${WALLPAPER_FOLDERS})
    set(ADDITION_RESOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/${WALLPAPER}/src/main/assets)
    string(REPLACE ${ADDITION_RESOURCE_PATH} ${CMAKE_BINARY_DIR}/assets destination ${destination})
  endforeach()

  add_custom_command(TARGET copyAssets PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sourcePath}" "${destination}")
endforeach()

# experiments
set(IS_SUBSYSTEM_WIN32)
if(MSVC)
  set(IS_SUBSYSTEM_WIN32 WIN32)
endif()

list(APPEND REQUIRED_LIBRARIES desktop)
list(APPEND REQUIRED_LIBRARIES elements)
list(APPEND REQUIRED_LIBRARIES freetype)

if(WIN32)
  list(APPEND REQUIRED_LIBRARIES libpng)
elseif(UNIX)
  list(APPEND REQUIRED_LIBRARIES png16)
endif()
list(APPEND REQUIRED_LIBRARIES z)
list(APPEND REQUIRED_LIBRARIES pugixml)
list(APPEND REQUIRED_LIBRARIES oel)
list(APPEND REQUIRED_LIBRARIES GLEW)
if(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
  list(APPEND REQUIRED_LIBRARIES glfw3)
else()
  list(APPEND REQUIRED_LIBRARIES glfw)
endif()
list(APPEND REQUIRED_LIBRARIES assimp)
if(WIN32)
  list(APPEND REQUIRED_LIBRARIES glu32)
  list(APPEND REQUIRED_LIBRARIES opengl32)
elseif(UNIX)
  list(APPEND REQUIRED_LIBRARIES GL)
  list(APPEND REQUIRED_LIBRARIES GLU)
  list(APPEND REQUIRED_LIBRARIES X11)
  if(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    list(APPEND REQUIRED_LIBRARIES Xrandr Xi Xxf86vm Xcursor Xinerama)
  endif()
  list(APPEND REQUIRED_LIBRARIES pthread)
endif()

file(GLOB Experiments RELATIVE ${CMAKE_SOURCE_DIR}/experiments ${CMAKE_SOURCE_DIR}/experiments/*)
foreach(Experiment ${Experiments})
  if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    set(Experiment_Path ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    set(ADDITION_SOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)

    file(GLOB SRC_FILES ${Experiment_Path}/*.h
                        ${Experiment_Path}/*.cpp
                        ${CMAKE_SOURCE_DIR}/platform/desktop/${Experiment}/*.h
                        ${CMAKE_SOURCE_DIR}/platform/desktop/${Experiment}/*.cpp)

    file(GLOB ADDITION_SRC_FILES ${ADDITION_SOURCE_PATH}/${Experiment}/*.h
                                 ${ADDITION_SOURCE_PATH}/${Experiment}/*.cpp)
    list(REMOVE_ITEM ADDITION_SRC_FILES ${ADDITION_SOURCE_PATH}/${Experiment}/${Experiment}_jni.cpp)
    list(APPEND SRC_FILES ${ADDITION_SRC_FILES})

    add_executable(${Experiment} ${IS_SUBSYSTEM_WIN32} ${SRC_FILES})

    target_include_directories(${Experiment} PRIVATE ${REQUIRED_INCLUDES}
                                                     ${elements_Path}/..
                                                     ${CMAKE_SOURCE_DIR}/experiments/${Experiment}
                                                     ${CMAKE_SOURCE_DIR}/platform/desktop/${Experiment}
                                                     ${ADDITION_SOURCE_PATH}/${Experiment})
    target_include_directories(${Experiment} SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
    target_link_libraries(${Experiment} ${REQUIRED_LIBRARIES})

    add_dependencies(${Experiment} copyAssets)
  endif()
endforeach()

# Flags
if(MSVC)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(FLAGS "${FLAGS} -Wall -Wextra")# -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS} -std=c11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++1y")
    add_definitions(-D__clang__)
  else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /EHsc /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc /W4")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /EHsc /W0 /GS")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHsc /W0 /GS")
    if(CMAKE_CL_64)
      set(LINK_FLAGS_RELEASE "${LINK_FLAGS_RELEASE} /DynamicBase /NXCompat")
    else()
      set(LINK_FLAGS_RELEASE "${LINK_FLAGS_RELEASE} /SafeSEH /DynamicBase /NXCompat")
    endif()
  endif()
else()
  set(FLAGS "${FLAGS} -Wall -Wextra")# -Werror")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS} -std=c11")
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++1y")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++14")
  endif()
endif()
