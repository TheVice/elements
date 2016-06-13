
cmake_minimum_required(VERSION 2.8.12)

project("elements")

if(MSVC)
  # if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.0)
  #   message(FATAL_ERROR "Could not support Visual Studio less than 2013")
  # endif()
  # if(NOT CHARACTER_SET)
  #   add_definitions(-D_UNICODE -DUNICODE)
  # else()
  #   add_definitions(-D_MBCS)
  # endif()
  # add_definitions(-DNOMINMAX)
  message(FATAL_ERROR "Could not support Visual Studio")
endif()

set(REQUIRED_INCLUDES)
set(REQUIRED_LIBRARIES)

# freetype
if(CMAKE_HOST_WIN32)
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
  message(${FREETYPE_INCLUDE_DIRS})
  set(FREETYPE_SRC_DIR ${freetype_Path}/src)

  set(FREETYPE_SRC_FILES ${FREETYPE_SRC_DIR}/autofit/autofit.c
                         ${FREETYPE_SRC_DIR}/base/ftbbox.c
                         ${FREETYPE_SRC_DIR}/base/ftbitmap.c
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
                         ${FREETYPE_SRC_DIR}/cache/ftcache.c
                         ${FREETYPE_SRC_DIR}/cff/cff.c
                         ${FREETYPE_SRC_DIR}/cid/type1cid.c
                         ${FREETYPE_SRC_DIR}/gzip/ftgzip.c
                         ${FREETYPE_SRC_DIR}/lzw/ftlzw.c
                         ${FREETYPE_SRC_DIR}/pcf/pcf.c
                         ${FREETYPE_SRC_DIR}/pfr/pfr.c
                         ${FREETYPE_SRC_DIR}/psaux/psaux.c
                         ${FREETYPE_SRC_DIR}/pshinter/pshinter.c
                         ${FREETYPE_SRC_DIR}/raster/raster.c
                         ${FREETYPE_SRC_DIR}/sfnt/sfnt.c
                         ${FREETYPE_SRC_DIR}/smooth/smooth.c
                         ${FREETYPE_SRC_DIR}/truetype/truetype.c
                         ${FREETYPE_SRC_DIR}/type1/type1.c
                         ${FREETYPE_SRC_DIR}/type42/type42.c
                         ${FREETYPE_SRC_DIR}/winfonts/winfnt.c)
  if(WIN32)
      list(APPEND FREETYPE_SRC_FILES ${FREETYPE_SRC_DIR}/../builds/windows/ftdebug.c
                                     ${FREETYPE_SRC_DIR}/base/ftbase.c
                                     ${FREETYPE_SRC_DIR}/psnames/psmodule.c)
  endif()

  add_library(freetype SHARED ${FREETYPE_SRC_FILES})
  # target_compile_definitions(freetype PRIVATE FT_CONFIG_OPTIONS_H="${freetype_Path}/devel/ftoption.h")
  # target_compile_definitions(freetype PRIVATE FT_CONFIG_OPTIONS_H="${freetype_Path}/include/freetype/config/ftconfig.h")

  target_compile_definitions(freetype PRIVATE FT2_BUILD_LIBRARY)
  target_include_directories(freetype SYSTEM PRIVATE ${FREETYPE_INCLUDE_DIRS})
endif()
list(APPEND REQUIRED_LIBRARIES freetype)

# glew
if(CMAKE_HOST_WIN32)
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
  list(APPEND REQUIRED_INCLUDES ${glew_Path}/include)
endif()
list(APPEND REQUIRED_LIBRARIES GLEW)

# glm
if(CMAKE_HOST_WIN32)
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
if(CMAKE_HOST_WIN32)
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
# list(APPEND REQUIRED_LIBRARIES z)

# libpng
if(CMAKE_HOST_WIN32)
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
# list(APPEND REQUIRED_LIBRARIES libpng)

# pugixml
if(CMAKE_HOST_WIN32)
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
# list(APPEND REQUIRED_LIBRARIES pugixml)

# elements
set(ELEMENTS_PATH ${CMAKE_SOURCE_DIR}/elements)
file(GLOB_RECURSE H_Files ${ELEMENTS_PATH}/*.h)
file(GLOB_RECURSE Cpp_Files ${ELEMENTS_PATH}/*.cpp)

add_library(elements ${Cpp_Files} ${H_Files})
target_include_directories(elements PRIVATE ${ELEMENTS_PATH})
target_include_directories(elements SYSTEM PRIVATE ${REQUIRED_INCLUDES})
list(APPEND REQUIRED_LIBRARIES elements)

# experiments
set(IS_SUBSYSTEM_WIN32)
if(MSVC)
  set(IS_SUBSYSTEM_WIN32 WIN32)
endif()

if(NOT MSVC)
  list(APPEND REQUIRED_LIBRARIES libpng)
  list(APPEND REQUIRED_LIBRARIES z)
  list(APPEND REQUIRED_LIBRARIES pugixml)
endif()

if(CMAKE_HOST_WIN32)
  add_definitions(-DWIN32)
  add_definitions(-D_WIN32)
  add_definitions(-D_WINDOWS)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-D_WIN32_WINNT=0x0500)
  list(APPEND REQUIRED_LIBRARIES glu32)
  list(APPEND REQUIRED_LIBRARIES opengl32)
endif(CMAKE_HOST_WIN32)

set(PLATFORM)
if(CMAKE_HOST_WIN32 OR CMAKE_HOST_UNIX)
  set(PLATFORM desktop)
endif()
file(GLOB PLATFORM_SRC_FILES ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/*.h ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/*.hpp ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/*.c ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/*.cpp)

file(GLOB Experiments RELATIVE ${CMAKE_SOURCE_DIR}/experiments ${CMAKE_SOURCE_DIR}/experiments/*)
list(REMOVE_ITEM Experiments Library)
foreach(Experiment ${Experiments})
  if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    # message(${Experiment})
    set(Experiment_Path ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    file(GLOB SRC_FILES ${Experiment_Path}/*.h ${Experiment_Path}/*.hpp ${Experiment_Path}/*.c ${Experiment_Path}/*.cpp)

    add_executable(${Experiment} ${IS_SUBSYSTEM_WIN32} ${SRC_FILES} ${PLATFORM_SRC_FILES})

    target_link_libraries(${Experiment} ${REQUIRED_LIBRARIES})
    target_include_directories(${Experiment} PRIVATE ${ELEMENTS_PATH} ${ELEMENTS_PATH}/..)
    target_include_directories(${Experiment} SYSTEM PRIVATE ${REQUIRED_INCLUDES})
  endif()
endforeach()

# Flags
if(MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /EHsc /W4")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc /W4")

  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /EHsc /W0 /GS")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHsc /W0 /GS")
  if(CMAKE_CL_64)
    set(LINK_FLAGS_RELEASE "${LINK_FLAGS_RELEASE} /DynamicBase /NXCompat")
  else()
    set(LINK_FLAGS_RELEASE "${LINK_FLAGS_RELEASE} /SafeSEH /DynamicBase /NXCompat")
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
