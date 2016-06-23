
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
# elseif(UNIX)
#   list(APPEND REQUIRED_INCLUDES /usr/include/freetype2)
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
  list(APPEND REQUIRED_INCLUDES ${glew_Path}/include)
endif()
list(APPEND REQUIRED_LIBRARIES GLEW)

# glfw
if(UNIX)
  add_definitions(-DGLFW_EXPOSE_NATIVE_X11)
  add_definitions(-DGLFW_EXPOSE_NATIVE_GLX)
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

  file(GLOB_RECURSE H_Files ${glfw_Path}/include/*.h)
  file(GLOB_RECURSE C_Files ${glfw_Path}/src/*.c)
  set(win_c_files)
  foreach(C_File ${C_Files})
    string(FIND ${C_File} "glx_" pos1 REVERSE)
    string(FIND ${C_File} "x11_" pos2 REVERSE)
    string(FIND ${C_File} "egl_" pos3 REVERSE)
    string(FIND ${C_File} "nsgl_" pos4 REVERSE)
    string(FIND ${C_File} "cocoa_" pos5 REVERSE)
    #
    string(FIND ${C_File} "linux_" pos6 REVERSE)
    string(FIND ${C_File} "mir_" pos7 REVERSE)
    string(FIND ${C_File} "posix_" pos8 REVERSE)
    string(FIND ${C_File} "wl_" pos9 REVERSE)
    string(FIND ${C_File} "xkb_" pos10 REVERSE)
    #
    string(FIND ${C_File} "mach_" pos11 REVERSE)

    if((${pos1} GREATER -1) OR (${pos2} GREATER -1) OR (${pos3} GREATER -1) OR (${pos4} GREATER -1) OR (${pos5} GREATER -1) OR (${pos6} GREATER -1) OR (${pos7} GREATER -1) OR (${pos8} GREATER -1) OR (${pos9} GREATER -1) OR (${pos10} GREATER -1) OR (${pos11} GREATER -1))
    else()
      list(APPEND win_c_files ${C_File})
    endif()
  endforeach()

  set(C_Files ${win_c_files})

  add_library(glfw ${H_Files} ${C_Files})

  target_include_directories(glfw SYSTEM PRIVATE ${glfw_Path}/include)
  target_compile_definitions(glfw PRIVATE "_GLFW_USE_OPENGL")
  target_compile_definitions(glfw PRIVATE "_GLFW_WIN32")
  target_compile_definitions(glfw PRIVATE "_GLFW_WGL")
  add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32)
  add_definitions(-DGLFW_EXPOSE_NATIVE_WGL)

  if(MSVC)
    set_target_properties(glfw PROPERTIES COMPILE_FLAGS "/W0")
  else()
    set_target_properties(glfw PROPERTIES COMPILE_FLAGS "-w")
  endif(MSVC)
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
set(oel_Path ${CMAKE_SOURCE_DIR}/third-party/oel)
file(GLOB OEL_SRC_FILES ${oel_Path}/*.h ${oel_Path}/*.cpp)
add_library(oel ${OEL_SRC_FILES})
target_include_directories(oel SYSTEM PRIVATE ${REQUIRED_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${oel_Path})

# elements
set(ELEMENTS_PATH ${CMAKE_SOURCE_DIR}/elements)
file(GLOB_RECURSE H_Files ${ELEMENTS_PATH}/*.h)
file(GLOB_RECURSE Cpp_Files ${ELEMENTS_PATH}/*.cpp)

add_library(elements ${Cpp_Files} ${H_Files})
target_include_directories(elements PRIVATE ${ELEMENTS_PATH})
target_include_directories(elements SYSTEM PRIVATE ${REQUIRED_INCLUDES})

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
if(WIN32)
  list(APPEND REQUIRED_LIBRARIES glu32)
  list(APPEND REQUIRED_LIBRARIES opengl32)
elseif(UNIX)
  list(APPEND REQUIRED_LIBRARIES GL)
  list(APPEND REQUIRED_LIBRARIES GLU)
  list(APPEND REQUIRED_LIBRARIES X11)
  list(APPEND REQUIRED_LIBRARIES pthread)
endif()

file(GLOB Experiments RELATIVE ${CMAKE_SOURCE_DIR}/experiments ${CMAKE_SOURCE_DIR}/experiments/*)
foreach(Experiment ${Experiments})
  if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    set(Experiment_Path ${CMAKE_SOURCE_DIR}/experiments/${Experiment})
    file(GLOB SRC_FILES ${Experiment_Path}/*.h ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/${Experiment}/*.h ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/${Experiment}/*.cpp ${Experiment_Path}/*.cpp)

    if(Experiment STREQUAL liquid)
      file(GLOB ADDITION_SRC_FILES ${CMAKE_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/liquid/*.cpp ${CMAKE_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/liquid/*.h)
      list(APPEND REQUIRED_INCLUDES ${CMAKE_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/liquid/)
      list(APPEND REQUIRED_INCLUDES ${CMAKE_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/)
      list(APPEND SRC_FILES ${ADDITION_SRC_FILES})
    endif()

    add_executable(${Experiment} ${IS_SUBSYSTEM_WIN32} ${SRC_FILES})

    target_link_libraries(${Experiment} ${REQUIRED_LIBRARIES})
    target_include_directories(${Experiment} PRIVATE ${ELEMENTS_PATH} ${ELEMENTS_PATH}/.. ${CMAKE_SOURCE_DIR}/experiments/${Experiment} ${CMAKE_SOURCE_DIR}/platform/${PLATFORM}/${Experiment})
    target_include_directories(${Experiment} SYSTEM PRIVATE ${REQUIRED_INCLUDES})
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

# Copy assets
if(NOT (CMAKE_SOURCE_DIR STREQUAL ${CMAKE_BINARY_DIR}))
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets/shaders" "${CMAKE_BINARY_DIR}/shaders")
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets/textures" "${CMAKE_BINARY_DIR}/textures")
  #
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/platform/android/elements/LiquidWallpaper/src/main/assets/textures" "${CMAKE_BINARY_DIR}/textures")
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/platform/android/elements/LiquidWallpaper/src/main/assets/ui" "${CMAKE_BINARY_DIR}/ui")
endif(NOT (CMAKE_SOURCE_DIR STREQUAL ${CMAKE_BINARY_DIR}))
