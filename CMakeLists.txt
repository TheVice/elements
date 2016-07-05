
cmake_minimum_required(VERSION 2.8.12)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Build process cannot start from project source directory")
endif()

project("elements")

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
set(REQUIRED_SYS_INCLUDES)

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

  file(GLOB ZLIB_SRC_FILES ${zlib_Path}/*.h ${zlib_Path}/*.c)
  add_library(z STATIC ${ZLIB_SRC_FILES})
  list(APPEND REQUIRED_SYS_INCLUDES ${zlib_Path})
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

# oel
set(oel_Path ${CMAKE_SOURCE_DIR}/third-party/oel)
file(GLOB OEL_SRC_FILES ${oel_Path}/*.cpp ${oel_Path}/*.h)
add_library(oel ${OEL_SRC_FILES})
target_include_directories(oel SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${oel_Path})

# elements
set(elements_Path ${CMAKE_SOURCE_DIR}/elements)
# file(GLOB_RECURSE ELEMENTS_SRC_FILES ${elements_Path}/*.h ${elements_Path}/*.cpp)
# list(FILTER ELEMENTS_SRC_FILES EXCLUDE REGEX ${elements_Path}/simulation/*)
set(ELEMENTS_SRC_FILES ${elements_Path}/assets/assets.h
                       ${elements_Path}/assets/assets_storage.cpp
                       ${elements_Path}/assets/assets_storage.h
                       ${elements_Path}/assets/asset_blob.cpp
                       ${elements_Path}/assets/asset_blob.h
                       ${elements_Path}/assets/asset_operations.h
                       ${elements_Path}/assets/asset_operations_stream.cpp
                       ${elements_Path}/assets/asset_operations_stream.h
                       ${elements_Path}/assets/asset_texture.cpp
                       ${elements_Path}/assets/asset_texture.h
                       ${elements_Path}/assets/asset_xml.cpp
                       ${elements_Path}/assets/asset_xml.h

                       ${elements_Path}/math/common.h
                       ${elements_Path}/math/constants.h
                       ${elements_Path}/math/geometric.h
                       ${elements_Path}/math/transform.h
                       ${elements_Path}/math/types.h

                       ${elements_Path}/metrics/metrics.cpp
                       ${elements_Path}/metrics/metrics.h

                       ${elements_Path}/preferences/preferences.cpp
                       ${elements_Path}/preferences/preferences.h

                       ${elements_Path}/rendering/computation/compute_product_index.cpp
                       ${elements_Path}/rendering/computation/compute_product_index.h
                       ${elements_Path}/rendering/computation/compute_target.cpp
                       ${elements_Path}/rendering/computation/compute_target.h

                       ${elements_Path}/rendering/core/buffer.h
                       ${elements_Path}/rendering/core/opengl.h
                       ${elements_Path}/rendering/core/program.cpp
                       ${elements_Path}/rendering/core/program.h
                       ${elements_Path}/rendering/core/shader.cpp
                       ${elements_Path}/rendering/core/shader.h
                       ${elements_Path}/rendering/core/target.h
                       ${elements_Path}/rendering/core/target_db.h
                       ${elements_Path}/rendering/core/texture.h
                       ${elements_Path}/rendering/core/texture_policy.h

                       ${elements_Path}/rendering/effects/blend.cpp
                       ${elements_Path}/rendering/effects/blend.h
                       ${elements_Path}/rendering/effects/blur.cpp
                       ${elements_Path}/rendering/effects/blur.h
                       ${elements_Path}/rendering/effects/clear.cpp
                       ${elements_Path}/rendering/effects/clear.h
                       ${elements_Path}/rendering/effects/forwards.h
                       ${elements_Path}/rendering/effects/gradient.cpp
                       ${elements_Path}/rendering/effects/gradient.h
                       ${elements_Path}/rendering/effects/light_scattered.cpp
                       ${elements_Path}/rendering/effects/light_scattered.h
                       ${elements_Path}/rendering/effects/tone.cpp
                       ${elements_Path}/rendering/effects/tone.h

                       ${elements_Path}/rendering/passes/pass_base.h
                       ${elements_Path}/rendering/passes/pass_composition.cpp
                       ${elements_Path}/rendering/passes/pass_composition.h
                       ${elements_Path}/rendering/passes/pass_input_slot.h
                       ${elements_Path}/rendering/passes/pass_target.cpp
                       ${elements_Path}/rendering/passes/pass_target.h
                       ${elements_Path}/rendering/passes/pass_target_input.cpp
                       ${elements_Path}/rendering/passes/pass_target_input.h
                       ${elements_Path}/rendering/passes/pass_target_placement.cpp
                       ${elements_Path}/rendering/passes/pass_target_placement.h
                       ${elements_Path}/rendering/passes/pass_target_storage.cpp
                       ${elements_Path}/rendering/passes/pass_target_storage.h

                       ${elements_Path}/rendering/primitives/square.cpp
                       ${elements_Path}/rendering/primitives/square.h

                       ${elements_Path}/rendering/state/state.h
                       ${elements_Path}/rendering/state/state_macro.h
                       ${elements_Path}/rendering/state/state_traits.h

                       ${elements_Path}/rendering/utils/program_loader.cpp
                       ${elements_Path}/rendering/utils/program_loader.h

                       # ${elements_Path}/simulation/air/system.cpp
                       # ${elements_Path}/simulation/air/system.h
                       # ${elements_Path}/simulation/air/volume.cpp
                       # ${elements_Path}/simulation/air/volume.h

                       # ${elements_Path}/simulation/liquid/config.cpp
                       # ${elements_Path}/simulation/liquid/config.h
                       # ${elements_Path}/simulation/liquid/obstacle.h
                       # ${elements_Path}/simulation/liquid/particle.h
                       # ${elements_Path}/simulation/liquid/system.cpp
                       # ${elements_Path}/simulation/liquid/system.h
                       # ${elements_Path}/simulation/liquid/volume.cpp
                       # ${elements_Path}/simulation/liquid/volume.h

                       ${elements_Path}/synchronization/future.h
                       ${elements_Path}/synchronization/signal.h
                       ${elements_Path}/synchronization/task.h

                       ${elements_Path}/timing/framerate.cpp
                       ${elements_Path}/timing/framerate.h
                       ${elements_Path}/timing/timer.cpp
                       ${elements_Path}/timing/timer.h
                       ${elements_Path}/timing/update.cpp
                       ${elements_Path}/timing/update.h

                       ${elements_Path}/ui/control.cpp
                       ${elements_Path}/ui/control.h
                       ${elements_Path}/ui/system.cpp
                       ${elements_Path}/ui/system.h
                       ${elements_Path}/ui/types.h

                       ${elements_Path}/ui/controls/button.cpp
                       ${elements_Path}/ui/controls/button.h
                       ${elements_Path}/ui/controls/label.cpp
                       ${elements_Path}/ui/controls/label.h
                       ${elements_Path}/ui/controls/panel.cpp
                       ${elements_Path}/ui/controls/panel.h
                       ${elements_Path}/ui/controls/slider.cpp
                       ${elements_Path}/ui/controls/slider.h

                       ${elements_Path}/ui/freetype/forwards.h
                       ${elements_Path}/ui/freetype/line.cpp
                       ${elements_Path}/ui/freetype/line.h
                       ${elements_Path}/ui/freetype/manager.cpp
                       ${elements_Path}/ui/freetype/manager.h

                       ${elements_Path}/utils/std/dependency_index.h
                       ${elements_Path}/utils/std/enum.h
                       ${elements_Path}/utils/std/iterator_range.h
                       ${elements_Path}/utils/std/pointer.h
                       ${elements_Path}/utils/std/product.h)

add_library(elements ${ELEMENTS_SRC_FILES})
target_include_directories(elements PRIVATE ${elements_Path})
target_include_directories(elements SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${elements_Path})

# platform library
set(platform_Path ${CMAKE_SOURCE_DIR}/platform/desktop)
file(GLOB PLATFORM_SRC_FILES ${platform_Path}/*.h ${platform_Path}/*.cpp)
add_library(desktop ${PLATFORM_SRC_FILES})
target_include_directories(desktop PRIVATE ${REQUIRED_INCLUDES})
target_include_directories(desktop SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${platform_Path})

# apps
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

file(GLOB_RECURSE SHADER_FILES RELATIVE ${CMAKE_SOURCE_DIR}/assets/shaders ${CMAKE_SOURCE_DIR}/assets/shaders/*.prog)
foreach(SHADER_FILE ${SHADER_FILES})
  string(REPLACE ".prog" "" app_path ${SHADER_FILE})
  set(app_full_path ${CMAKE_SOURCE_DIR}/platform/desktop/${app_path})

  if((EXISTS ${app_full_path}) AND (IS_DIRECTORY ${app_full_path}))
    string(FIND ${app_path} "/" pos1 REVERSE)

    if(${pos1} GREATER -1)
      string(LENGTH ${app_path} string_length)
      string(SUBSTRING ${app_path} 0 ${pos1} tmp_path)
      string(FIND ${tmp_path} "/" pos2 REVERSE)

      if(${pos2} GREATER -1)
        math(EXPR pos2 "${pos2} + 1")
      else()
        set(pos2 0)
      endif()

      string(SUBSTRING ${app_path} ${pos2} ${string_length} app_path)
      string(REPLACE "/" "_" app_path ${app_path})
    endif()

    file(GLOB SRC_FILES ${app_full_path}/*.h ${app_full_path}/*.cpp)
    add_executable(${app_path} ${IS_SUBSYSTEM_WIN32} ${SRC_FILES})

    target_link_libraries(${app_path} ${REQUIRED_LIBRARIES})
    target_include_directories(${app_path} PRIVATE ${REQUIRED_INCLUDES})
    target_include_directories(${app_path} SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
    target_include_directories(${app_path} PRIVATE ${REQUIRED_INCLUDES})

    # Copy assets
    set(RESOURCE_FILE ${CMAKE_SOURCE_DIR}/assets/shaders/${SHADER_FILE})
    set(destination ${CMAKE_BINARY_DIR}/shaders/${SHADER_FILE})
    add_custom_command(TARGET ${app_path} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RESOURCE_FILE}" "${destination}")

    set(RESOURCE_FILE ${CMAKE_SOURCE_DIR}/assets/textures/noise.png)
    set(destination ${CMAKE_BINARY_DIR}/textures/noise.png)
    add_custom_command(TARGET ${app_path} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RESOURCE_FILE}" "${destination}")
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
    add_definitions(-DFT_CONFIG_OPTION_NO_ASSEMBLER)
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++14")
  endif()
endif()
