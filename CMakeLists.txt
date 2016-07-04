
cmake_minimum_required(VERSION 2.8.12)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Build process cannot start from project source directory")
endif()

project("elements")

if(WIN32)
  message(FATAL_ERROR "Could not support WIN32 platform")
endif()

if(MSVC)
  # if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.0)
  #   message(FATAL_ERROR "Could not support Visual Studio less than 2013")
  # endif()
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
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-D_WIN32_WINNT=0x0500)
endif()

set(REQUIRED_INCLUDES)
set(REQUIRED_LIBRARIES)

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
  list(APPEND REQUIRED_INCLUDES ${freetype_Path}/include)

  set(FREETYPE_INCLUDE_DIRS ${freetype_Path}/include ${freetype_Path}/include/freetype2)
  set(FREETYPE_SRC_DIR ${freetype_Path}/src)

  set(FREETYPE_SRC_FILES ${FREETYPE_SRC_DIR}/autofit/autofit.c
                         ${FREETYPE_SRC_DIR}/base/ftbase.c
                         ${FREETYPE_SRC_DIR}/base/ftbbox.c
                         ${FREETYPE_SRC_DIR}/base/ftbdf.c
                         ${FREETYPE_SRC_DIR}/base/ftbitmap.c
                         ${FREETYPE_SRC_DIR}/base/ftcid.c
                         ${FREETYPE_SRC_DIR}/base/ftfntfmt.c
                         ${FREETYPE_SRC_DIR}/base/ftfstype.c
                         ${FREETYPE_SRC_DIR}/base/ftgasp.c
                         ${FREETYPE_SRC_DIR}/base/ftglyph.c
                         ${FREETYPE_SRC_DIR}/base/ftgxval.c
                         ${FREETYPE_SRC_DIR}/base/ftinit.c
                         ${FREETYPE_SRC_DIR}/base/ftlcdfil.c
                         ${FREETYPE_SRC_DIR}/base/ftmm.c
                         ${FREETYPE_SRC_DIR}/base/ftotval.c
                         ${FREETYPE_SRC_DIR}/base/ftpatent.c
                         ${FREETYPE_SRC_DIR}/base/ftpfr.c
                         ${FREETYPE_SRC_DIR}/base/ftstroke.c
                         ${FREETYPE_SRC_DIR}/base/ftsynth.c
                         ${FREETYPE_SRC_DIR}/base/ftsystem.c
                         ${FREETYPE_SRC_DIR}/base/fttype1.c
                         ${FREETYPE_SRC_DIR}/base/ftwinfnt.c
                         ${FREETYPE_SRC_DIR}/bdf/bdf.c
                         ${FREETYPE_SRC_DIR}/bzip2/ftbzip2.c
                         ${FREETYPE_SRC_DIR}/cache/ftcache.c
                         ${FREETYPE_SRC_DIR}/cff/cff.c
                         ${FREETYPE_SRC_DIR}/cid/type1cid.c
                         ${FREETYPE_SRC_DIR}/gzip/ftgzip.c
                         ${FREETYPE_SRC_DIR}/lzw/ftlzw.c
                         ${FREETYPE_SRC_DIR}/pcf/pcf.c
                         ${FREETYPE_SRC_DIR}/pfr/pfr.c
                         ${FREETYPE_SRC_DIR}/psaux/psaux.c
                         ${FREETYPE_SRC_DIR}/pshinter/pshinter.c
                         ${FREETYPE_SRC_DIR}/psnames/psnames.c
                         ${FREETYPE_SRC_DIR}/raster/raster.c
                         ${FREETYPE_SRC_DIR}/sfnt/sfnt.c
                         ${FREETYPE_SRC_DIR}/smooth/smooth.c
                         ${FREETYPE_SRC_DIR}/truetype/truetype.c
                         ${FREETYPE_SRC_DIR}/type1/type1.c
                         ${FREETYPE_SRC_DIR}/type42/type42.c
                         ${FREETYPE_SRC_DIR}/winfonts/winfnt.c)

  add_library(freetype SHARED ${FREETYPE_SRC_FILES})

  if(MSVC)
    if(EXISTS "${freetype_Path}/config/ftoption.h")
      target_compile_definitions(freetype PRIVATE FT_CONFIG_OPTIONS_H="${freetype_Path}/config/ftoption.h")
    endif()
  endif()
  target_compile_definitions(freetype PRIVATE FT2_BUILD_LIBRARY)
  target_include_directories(freetype SYSTEM PRIVATE ${FREETYPE_INCLUDE_DIRS})
endif()

# SwiftShader

  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/SwiftShader)
    set(SwiftShader_PATH ${CMAKE_SOURCE_DIR}/third-party/SwiftShader)
  elseif(DEFINED ENV{SWIFTSHADER_PATH})
    string(REPLACE "\\" "/" SwiftShader_PATH $ENV{SWIFTSHADER_PATH})
  elseif(DEFINED SWIFTSHADER_PATH)
    string(REPLACE "\\" "/" SwiftShader_PATH ${SWIFTSHADER_PATH})
  else()
    message(FATAL_ERROR "Could not find SwiftShader library, please check it at https://swiftshader.googlesource.com/SwiftShader")
  endif()

  add_subdirectory(${SwiftShader_PATH} ${CMAKE_BINARY_DIR}/SwiftShader)

  list(APPEND REQUIRED_INCLUDES ${SwiftShader_PATH}/include)

# glfw
if(UNIX)
  add_definitions(-DGLFW_EXPOSE_NATIVE_X11)
  add_definitions(-DGLFW_EXPOSE_NATIVE_EGL)
else()
  if(EXISTS ${CMAKE_SOURCE_DIR}/external/glfw)
    set(glfw_Path ${CMAKE_SOURCE_DIR}/external/glfw)
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

  list(APPEND REQUIRED_INCLUDES ${glfw_Path}/include)
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
  list(APPEND REQUIRED_INCLUDES ${glm_Path})
endif()

# z
if(WIN32)
  if(EXISTS ${CMAKE_SOURCE_DIR}/third-party/zlib)
    set(zlib_Path ${CMAKE_SOURCE_DIR}/third-party/zlib)
  elseif(DEFINED ENV{ZLIB_PATH})
    string(REPLACE "\\" "/" zlib_Path $ENV{ZLIB_PATH})
  elseif(DEFINED ZLIB_PATH)
    string(REPLACE "\\" "/" zlib_Path ${ZLIB_PATH})
  else()
    message(FATAL_ERROR "Could not find zlib library, please check it at https://sourceforge.net/projects/libpng/files/zlib/")
  endif()

  file(GLOB ZLIB_SRC_FILES ${zlib_Path}/*.c ${zlib_Path}/*.h)
  add_library(z STATIC ${ZLIB_SRC_FILES})
  list(APPEND REQUIRED_INCLUDES ${zlib_Path})
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

  file(GLOB LIBPNG_SRC_FILES ${libpng_Path}/*.c ${libpng_Path}/*.h)
  list(REMOVE_ITEM LIBPNG_SRC_FILES ${libpng_Path}/example.c ${libpng_Path}/pngtest.c)
  add_library(libpng STATIC ${LIBPNG_SRC_FILES})
  target_include_directories(libpng SYSTEM PRIVATE ${zlib_Path})
  list(APPEND REQUIRED_INCLUDES ${libpng_Path})
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

  file(GLOB PUGIXML_SRC_FILES ${pugixml_Path}/src/*.cpp ${pugixml_Path}/src/*.hpp)
  add_library(pugixml STATIC ${PUGIXML_SRC_FILES})
  list(APPEND REQUIRED_INCLUDES ${pugixml_Path}/src)
endif()

# oel
list(APPEND REQUIRED_INCLUDES ${CMAKE_SOURCE_DIR}/third-party/PowerVR_SDK/Beginner/01_HelloAPI/OGLES2/)
set(oel_Path ${CMAKE_SOURCE_DIR}/third-party/oel)
file(GLOB OEL_SRC_FILES ${oel_Path}/*.h ${oel_Path}/*.cpp
                        ${CMAKE_SOURCE_DIR}/third-party/PowerVR_SDK/Beginner/01_HelloAPI/OGLES2/*.h
                        ${CMAKE_SOURCE_DIR}/third-party/PowerVR_SDK/Beginner/01_HelloAPI/OGLES2/*.cpp)
add_library(oel ${OEL_SRC_FILES})
target_include_directories(oel SYSTEM PRIVATE ${REQUIRED_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${oel_Path})

  target_compile_definitions(oel PRIVATE GL_API=)
  target_compile_definitions(oel PRIVATE GL_APICALL=)
  target_compile_definitions(oel PRIVATE GL_GLEXT_PROTOTYPES)
  target_compile_definitions(oel PRIVATE _USRDLL)
  target_compile_definitions(oel PRIVATE LIBGLESV2_EXPORTS)

# elements
set(ELEMENTS_PATH ${CMAKE_SOURCE_DIR}/elements)
file(GLOB_RECURSE H_Files ${ELEMENTS_PATH}/*.h)
file(GLOB_RECURSE Cpp_Files ${ELEMENTS_PATH}/*.cpp)

add_library(elements ${Cpp_Files} ${H_Files})
target_include_directories(elements PRIVATE ${ELEMENTS_PATH})
target_include_directories(elements SYSTEM PRIVATE ${REQUIRED_INCLUDES})

  target_compile_definitions(elements PRIVATE GL_API=)
  target_compile_definitions(elements PRIVATE GL_APICALL=)
  target_compile_definitions(elements PRIVATE GL_GLEXT_PROTOTYPES)
  target_compile_definitions(elements PRIVATE _USRDLL)
  target_compile_definitions(elements PRIVATE LIBGLESV2_EXPORTS)

# platform library
set(PLATFORM)
if(WIN32 OR UNIX)
  set(PLATFORM desktop)
endif()

file(GLOB PLATFORM_SRC_FILES ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/*.h ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/*.cpp)
add_library(${PLATFORM} ${PLATFORM_SRC_FILES})
target_include_directories(${PLATFORM} PRIVATE ${ELEMENTS_PATH} ${ELEMENTS_PATH}/..)
target_include_directories(${PLATFORM} SYSTEM PRIVATE ${REQUIRED_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/)

  target_compile_definitions(${PLATFORM} PRIVATE GL_API=)
  target_compile_definitions(${PLATFORM} PRIVATE GL_APICALL=)
  target_compile_definitions(${PLATFORM} PRIVATE GL_GLEXT_PROTOTYPES)
  target_compile_definitions(${PLATFORM} PRIVATE _USRDLL)
  target_compile_definitions(${PLATFORM} PRIVATE LIBGLESV2_EXPORTS)

# experiments
set(IS_SUBSYSTEM_WIN32)
if(MSVC)
  set(IS_SUBSYSTEM_WIN32 WIN32)
endif()

list(APPEND REQUIRED_LIBRARIES ${PLATFORM})
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
list(APPEND REQUIRED_LIBRARIES glfw)

if(UNIX)
  list(APPEND REQUIRED_LIBRARIES X11)
  list(APPEND REQUIRED_LIBRARIES pthread)
endif()

list(APPEND REQUIRED_LIBRARIES ${CMAKE_BINARY_DIR}/SwiftShader/libEGL.so ${CMAKE_BINARY_DIR}/SwiftShader/libGLESv2.so)

file(GLOB Experiments RELATIVE ${CMAKE_SOURCE_DIR}/experiments ${CMAKE_SOURCE_DIR}/experiments/*)
foreach(Experiment ${Experiments})
  if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    set(Experiment_Path ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    set(ADDITION_SOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)

    file(GLOB SRC_FILES ${Experiment_Path}/*.h ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/${Experiment}/*.h ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/${Experiment}/*.cpp ${Experiment_Path}/*.cpp)
    file(GLOB ADDITION_SRC_FILES ${ADDITION_SOURCE_PATH}/${Experiment}/*.cpp ${ADDITION_SOURCE_PATH}/${Experiment}/*.h)

    list(REMOVE_ITEM ADDITION_SRC_FILES ${ADDITION_SOURCE_PATH}/${Experiment}/${Experiment}_jni.cpp)
    list(APPEND SRC_FILES ${ADDITION_SRC_FILES})

    add_executable(${Experiment} ${IS_SUBSYSTEM_WIN32} ${SRC_FILES})

    target_compile_definitions(${Experiment} PRIVATE GL_API=)
    target_compile_definitions(${Experiment} PRIVATE GL_APICALL=)
    target_compile_definitions(${Experiment} PRIVATE GL_GLEXT_PROTOTYPES)
    target_compile_definitions(${Experiment} PRIVATE _USRDLL)
    target_compile_definitions(${Experiment} PRIVATE LIBGLESV2_EXPORTS)

    target_link_libraries(${Experiment} ${REQUIRED_LIBRARIES})
    target_include_directories(${Experiment} PRIVATE ${ELEMENTS_PATH} ${ELEMENTS_PATH}/.. ${CMAKE_SOURCE_DIR}/experiments/${Experiment} ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/${Experiment})
    target_include_directories(${Experiment} SYSTEM PRIVATE ${REQUIRED_INCLUDES} ${ADDITION_SOURCE_PATH}/${Experiment}/ ${ADDITION_SOURCE_PATH})

    # Copy assets
    file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_SOURCE_DIR}/assets/shaders/* ${CMAKE_SOURCE_DIR}/assets/textures/*)
    foreach(RESOURCE_FILE ${RESOURCE_FILES})
      string(REPLACE "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}" destination ${RESOURCE_FILE})
      add_custom_command(TARGET ${Experiment} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RESOURCE_FILE}" "${destination}")
    endforeach()

    set(ADDITION_RESOURCE_PATH)
    if(Experiment STREQUAL air)
      set(ADDITION_RESOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/AirWallpaper/src/main/assets)
    endif()
    if(Experiment STREQUAL fire)
      set(ADDITION_RESOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/FireWallpaper/src/main/assets)
    endif()
    if(Experiment STREQUAL light)
      set(ADDITION_RESOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/LightWallpaper/src/main/assets)
    endif()
    if(Experiment STREQUAL liquid)
      set(ADDITION_RESOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/LiquidWallpaper/src/main/assets)
    endif()
    if(Experiment STREQUAL strange)
      set(ADDITION_RESOURCE_PATH ${CMAKE_SOURCE_DIR}/platform/android/elements/StrangeWallpaper/src/main/assets)
    endif()

    file(GLOB_RECURSE RESOURCE_FILES ${ADDITION_RESOURCE_PATH}/*)
    foreach(RESOURCE_FILE ${RESOURCE_FILES})
      string(REPLACE "${ADDITION_RESOURCE_PATH}" "${CMAKE_BINARY_DIR}" destination ${RESOURCE_FILE})
      add_custom_command(TARGET ${Experiment} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RESOURCE_FILE}" "${destination}")
    endforeach()
  endif()
endforeach()

# Flags
if(MSVC)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(FLAGS "${FLAGS} -Wall -Wextra")# -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS} -std=c11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++1y")
    add_definitions(-DFT_CONFIG_OPTION_NO_ASSEMBLER)
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
