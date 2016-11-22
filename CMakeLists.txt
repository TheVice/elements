cmake_minimum_required(VERSION 3.3)

project("elements")

# Third-party
set(EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(EXTERNAL_INCLUDES)
set(EXTERNAL_LIBRARIES)

# assimp

set(EXTERNAL_PATH_ASSIMP ${EXTERNAL_PATH}/assimp)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
if(NOT ANDROID)
    set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(${EXTERNAL_PATH_ASSIMP})
target_compile_options(assimp PRIVATE -fexceptions -frtti)
if(NOT ANDROID)
    set_target_properties(assimp PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# build importers
target_compile_definitions(assimp PRIVATE
    ASSIMP_BUILD_NO_X_IMPORTER
    ASSIMP_BUILD_NO_3DS_IMPORTER
    ASSIMP_BUILD_NO_MD3_IMPORTER
    ASSIMP_BUILD_NO_MDL_IMPORTER
    ASSIMP_BUILD_NO_MD2_IMPORTER
    ASSIMP_BUILD_NO_PLY_IMPORTER
    ASSIMP_BUILD_NO_ASE_IMPORTER
    ASSIMP_BUILD_NO_HMP_IMPORTER
    ASSIMP_BUILD_NO_SMD_IMPORTER
    ASSIMP_BUILD_NO_MDC_IMPORTER
    ASSIMP_BUILD_NO_MD5_IMPORTER
    ASSIMP_BUILD_NO_STL_IMPORTER
    ASSIMP_BUILD_NO_LWO_IMPORTER
    ASSIMP_BUILD_NO_DXF_IMPORTER
    ASSIMP_BUILD_NO_NFF_IMPORTER
    ASSIMP_BUILD_NO_RAW_IMPORTER
    ASSIMP_BUILD_NO_OFF_IMPORTER
    ASSIMP_BUILD_NO_AC_IMPORTER
    ASSIMP_BUILD_NO_BVH_IMPORTER
    ASSIMP_BUILD_NO_IRRMESH_IMPORTER
    ASSIMP_BUILD_NO_IRR_IMPORTER
    ASSIMP_BUILD_NO_Q3D_IMPORTER
    ASSIMP_BUILD_NO_B3D_IMPORTER
    ASSIMP_BUILD_NO_TERRAGEN_IMPORTER
    ASSIMP_BUILD_NO_CSM_IMPORTER
    ASSIMP_BUILD_NO_3D_IMPORTER
    ASSIMP_BUILD_NO_LWS_IMPORTER
    ASSIMP_BUILD_NO_OGRE_IMPORTER
    ASSIMP_BUILD_NO_MS3D_IMPORTER
    ASSIMP_BUILD_NO_COB_IMPORTER
    ASSIMP_BUILD_NO_Q3BSP_IMPORTER
    ASSIMP_BUILD_NO_NDO_IMPORTER
    ASSIMP_BUILD_NO_IFC_IMPORTER
    ASSIMP_BUILD_NO_XGL_IMPORTER
    ASSIMP_BUILD_NO_FBX_IMPORTER
    ASSIMP_BUILD_NO_C4D_IMPORTER
    ASSIMP_BUILD_NO_ASSBIN_IMPORTER
    ASSIMP_BUILD_NO_BLEND_IMPORTER
    ASSIMP_BUILD_NO_GEO_IMPORTER
    ASSIMP_BUILD_NO_IRRMESH_IMPORTER)

# build processes
target_compile_definitions(assimp PRIVATE
    ASSIMP_BUILD_NO_MAKELEFTHANDED_PROCESS
    ASSIMP_BUILD_NO_DEBONE_PROCESS
    ASSIMP_BUILD_NO_FINDDEGENERATES_PROCESS
    ASSIMP_BUILD_NO_FINDINSTANCES_PROCESS
    ASSIMP_BUILD_NO_FINDINVALIDDATA_PROCESS
    ASSIMP_BUILD_NO_FIXINFACINGNORMALS_PROCESS
    ASSIMP_BUILD_NO_GENFACENORMALS_PROCESS
    ASSIMP_BUILD_NO_GENUVCOORDS_PROCESS
    ASSIMP_BUILD_NO_GENVERTEXNORMALS_PROCESS
    ASSIMP_BUILD_NO_IMPROVECACHELOCALITY_PROCESS
    ASSIMP_BUILD_NO_LIMITBONEWEIGHTS_PROCESS
    ASSIMP_BUILD_NO_OPTIMIZEGRAPH_PROCESS
    ASSIMP_BUILD_NO_OPTIMIZEMESHES_PROCESS
    ASSIMP_BUILD_NO_PRETRANSFORMVERTICES_PROCESS
    ASSIMP_BUILD_NO_REMOVEVC_PROCESS
    ASSIMP_BUILD_NO_REMOVE_REDUNDANTMATERIALS_PROCESS
    ASSIMP_BUILD_NO_SORTBYPTYPE_PROCESS
    ASSIMP_BUILD_NO_SPLITBYBONECOUNT_PROCESS
    ASSIMP_BUILD_NO_SPLITLARGEMESHES_PROCESS
    ASSIMP_BUILD_NO_TRANSFORMTEXCOORDS_PROCESS)

list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_ASSIMP}/include)
list(APPEND EXTERNAL_LIBRARIES assimp)

if(NOT ANDROID)
    set_target_properties(zlibstatic PROPERTIES POSITION_INDEPENDENT_CODE ON)
    set(EXTERNAL_PATH_ZLIBSTATIC ${CMAKE_BINARY_DIR}/third-party/assimp/contrib/zlib
                                 ${EXTERNAL_PATH_ASSIMP}/contrib/zlib)
endif()

#freetype

set(EXTERNAL_PATH_FREETYPE ${EXTERNAL_PATH}/freetype2)
add_subdirectory(${EXTERNAL_PATH_FREETYPE})
target_compile_definitions(freetype PRIVATE FT2_BUILD_LIBRARY)
if(NOT ANDROID)
    set_target_properties(freetype PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_FREETYPE}/include)
list(APPEND EXTERNAL_LIBRARIES freetype)

# glm

set(EXTERNAL_PATH_GLM ${EXTERNAL_PATH}/glm)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_GLM})

# libpng

set(EXTERNAL_PATH_PNG ${EXTERNAL_PATH}/libpng)
if(ANDROID)
    configure_file(${EXTERNAL_PATH_PNG}/scripts/pnglibconf.h.prebuilt
                   ${EXTERNAL_PATH_PNG}/pnglibconf.h)
else()
    configure_file(${EXTERNAL_PATH_PNG}/scripts/pnglibconf.h.prebuilt
                   ${CMAKE_BINARY_DIR}/third-party/libpng/pnglibconf.h)
endif()
file(GLOB LIBPNG_SOURCE_FILES ${EXTERNAL_PATH_PNG}/*.h ${EXTERNAL_PATH_PNG}/*.c)
list(REMOVE_ITEM LIBPNG_SOURCE_FILES ${EXTERNAL_PATH_PNG}/pngtest.c)
add_library(png STATIC ${LIBPNG_SOURCE_FILES})
if(NOT ANDROID)
    add_dependencies(png zlibstatic)
    target_include_directories(png SYSTEM PRIVATE ${CMAKE_BINARY_DIR}/third-party/libpng
                                                  ${EXTERNAL_PATH_ZLIBSTATIC})
    set_target_properties(png PROPERTIES POSITION_INDEPENDENT_CODE ON)
    list(APPEND EXTERNAL_INCLUDES ${CMAKE_BINARY_DIR}/third-party/libpng)
endif()
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_PNG})
list(APPEND EXTERNAL_LIBRARIES png)
if(NOT ANDROID)
    list(APPEND EXTERNAL_LIBRARIES zlibstatic)
endif()

# pugixml

set(EXTERNAL_PATH_PUGIXML ${EXTERNAL_PATH}/pugixml)
if(ANDROID)
    add_subdirectory(${EXTERNAL_PATH_PUGIXML})
else()
    set(SOURCES
        ${EXTERNAL_PATH_PUGIXML}/src/pugixml.hpp
        ${EXTERNAL_PATH_PUGIXML}/src/pugiconfig.hpp
        ${EXTERNAL_PATH_PUGIXML}/src/pugixml.cpp)
    add_library(pugixml STATIC ${SOURCES})
    target_compile_options(pugixml PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
    set_target_properties(pugixml PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
target_compile_definitions(pugixml PRIVATE PUGIXML_NO_EXCEPTIONS)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_PUGIXML}/src)
list(APPEND EXTERNAL_LIBRARIES pugixml)

# snape

set(EXTERNAL_PATH_SNAPE ${EXTERNAL_PATH}/snape)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_SNAPE}/include)

if(NOT ANDROID)

    if(UNIX)

        # SwiftShader

        set(EXTERNAL_PATH_SWIFT_SHADER ${CMAKE_CURRENT_SOURCE_DIR}/third-party/SwiftShader)

        # file(READ ${EXTERNAL_PATH_SWIFT_SHADER}/CMakeLists.txt file_content)
        # string(REGEX REPLACE "CMAKE_SOURCE_DIR" "EXTERNAL_PATH_SWIFT_SHADER" file_content ${file_content})
        # file(WRITE ${CMAKE_BINARY_DIR}/third-party/SwiftShader/CMakeLists.txt ${file_content})

        # set(BUILD_EGL OFF CACHE BOOL "" FORCE)
        # set(BUILD_GL32 OFF CACHE BOOL "" FORCE)
        # set(BUILD_GLESv2 OFF CACHE BOOL "" FORCE)
        # set(BUILD_GLES_CM OFF CACHE BOOL "" FORCE)
        # set(BUILD_EXTRA_PROGRAMS OFF CACHE BOOL "" FORCE)
        # add_subdirectory(${CMAKE_BINARY_DIR}/third-party/SwiftShader ${CMAKE_BINARY_DIR}/third-party/SwiftShader)
        # set_target_properties(libEGL PROPERTIES POSITION_INDEPENDENT_CODE ON)
        # set_target_properties(libGLESv2 PROPERTIES POSITION_INDEPENDENT_CODE ON)

        # list(APPEND REQUIRED_SYS_INCLUDES ${EXTERNAL_PATH_SWIFT_SHADER}/include)
        # list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_SWIFT_SHADER}/include)
        # list(APPEND EXTERNAL_LIBRARIES libEGL)
        # list(APPEND EXTERNAL_LIBRARIES libGLESv2)

    endif()

    # glew

    if(WIN32)
        if(EXISTS ${EXTERNAL_PATH}/glew-1.13.0)
            set(EXTERNAL_PATH_GLEW ${EXTERNAL_PATH}/glew-1.13.0)
        elseif(DEFINED ENV{GLEW_PATH})
            string(REPLACE "\\" "/" EXTERNAL_PATH_GLEW $ENV{GLEW_PATH})
        elseif(DEFINED GLEW_PATH)
            string(REPLACE "\\" "/" EXTERNAL_PATH_GLEW ${GLEW_PATH})
        else()
            message(FATAL_ERROR "Could not find glew library, please check it at https://github.com/nigels-com/glew/issues/31#issuecomment-145498979 or https://sourceforge.net/projects/glew/files/glew/1.13.0/")
        endif()
    else()
        set(EXTERNAL_PATH_GLEW ${EXTERNAL_PATH}/glew)
    endif()

    if(UNIX)

        # glfixes

        set(glfixes_Path ${EXTERNAL_PATH}/glfixes)

        if(NOT EXISTS "${CMAKE_BINARY_DIR}/third-party/glew")
            message("Copying ${EXTERNAL_PATH_GLEW} into ${CMAKE_BINARY_DIR}/third-party/glew")
            execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${EXTERNAL_PATH_GLEW}" "${CMAKE_BINARY_DIR}/third-party/glew")
        endif()

        set(REQUIRED_TO_WRITE FALSE)
        file(READ "${CMAKE_BINARY_DIR}/third-party/glew/auto/Makefile" file_content)

        string(FIND "${file_content}" "\$(GIT_CLONE)" pos)
        if("${pos}" EQUAL -1)
        else()
            string(REPLACE "\$(GIT_CLONE)" "# \$(G_I_T_CLONE)" file_content "${file_content}")
            set(REQUIRED_TO_WRITE TRUE)
        endif()

        string(FIND "${file_content}" "GIT_CLONE" pos)
        if("${pos}" EQUAL -1)
        else()
            string(REPLACE "GIT_CLONE" "# G_I_T_CLONE" file_content "${file_content}")
            set(REQUIRED_TO_WRITE TRUE)
        endif()

        if(REQUIRED_TO_WRITE)
            message("Write ${CMAKE_BINARY_DIR}/third-party/glew/auto/Makefile")
            file(WRITE "${CMAKE_BINARY_DIR}/third-party/glew/auto/Makefile" "${file_content}")
        endif()

        if(NOT EXISTS "${CMAKE_BINARY_DIR}/third-party/glew/auto/registry")
            message("Copying ${glfixes_Path} into ${CMAKE_BINARY_DIR}/third-party/glew/auto/registry")
            execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${glfixes_Path}" "${CMAKE_BINARY_DIR}/third-party/glew/auto/registry")
        endif()

        execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} -C "${CMAKE_BINARY_DIR}/third-party/glew/auto")
        set(EXTERNAL_PATH_GLEW ${CMAKE_BINARY_DIR}/third-party/glew)
    endif()

    add_library(glew_s STATIC ${EXTERNAL_PATH_GLEW}/src/glew.c)
    set_target_properties(glew_s PROPERTIES POSITION_INDEPENDENT_CODE ON)

    target_include_directories(glew_s SYSTEM PRIVATE ${EXTERNAL_PATH_GLEW}/include)
    target_compile_definitions(glew_s PRIVATE GLEW_STATIC)
    list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_GLEW}/include)
    list(APPEND EXTERNAL_LIBRARIES glew_s)

    # glfw

    set(EXTERNAL_PATH_GLFW ${EXTERNAL_PATH}/glfw)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(${EXTERNAL_PATH_GLFW})
    set_target_properties(glfw PROPERTIES POSITION_INDEPENDENT_CODE ON)

    if(UNIX)
        target_compile_definitions(glfw PRIVATE GLFW_EXPOSE_NATIVE_X11)
        target_compile_definitions(glfw PRIVATE GLFW_EXPOSE_NATIVE_GLX)
    elseif(WIN32)
        target_compile_definitions(glfw PRIVATE GLFW_EXPOSE_NATIVE_WIN32)
        target_compile_definitions(glfw PRIVATE GLFW_EXPOSE_NATIVE_WGL)
    endif()

    list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_GLFW}/include)
    list(APPEND EXTERNAL_LIBRARIES glfw)

    # oel

    set(EXTERNAL_PATH_OEL ${EXTERNAL_PATH}/oel)
    file(GLOB OEL_SOURCE_FILES ${EXTERNAL_PATH_OEL}/*.h ${EXTERNAL_PATH_OEL}/*.cpp)
    add_library(oel STATIC ${OEL_SOURCE_FILES})
    target_include_directories(oel PRIVATE ${EXTERNAL_PATH_GLEW}/include ${EXTERNAL_PATH_GLFW}/include ${EXTERNAL_PATH_GLM})
    target_compile_options(oel PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
    set_target_properties(oel PROPERTIES POSITION_INDEPENDENT_CODE ON)

    if(WIN32)
        target_compile_definitions(oel PRIVATE WIN32)
    endif()

    list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_OEL})
    list(APPEND EXTERNAL_LIBRARIES oel)

endif()

# elements

set(ELEMENTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/elements)

set(ELEMENTS_SOURCE_ASSETS_PATH ${ELEMENTS_PATH}/assets)
set(ELEMENTS_SOURCE_ASSETS
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_blob.cpp
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_blob.h
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_model.cpp
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_model.h
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_texture.cpp
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_texture.h
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_xml.cpp
    ${ELEMENTS_SOURCE_ASSETS_PATH}/asset_xml.h
    ${ELEMENTS_SOURCE_ASSETS_PATH}/assets_storage.cpp
    ${ELEMENTS_SOURCE_ASSETS_PATH}/assets_storage.h
    ${ELEMENTS_SOURCE_ASSETS_PATH}/assets.h)

set(ELEMENTS_SOURCE_COLLISION_PATH ${ELEMENTS_PATH}/collision)
set(ELEMENTS_SOURCE_COLLISION
    ${ELEMENTS_SOURCE_COLLISION_PATH}/aabb.cpp
    ${ELEMENTS_SOURCE_COLLISION_PATH}/aabb.h
    ${ELEMENTS_SOURCE_COLLISION_PATH}/collide.cpp
    ${ELEMENTS_SOURCE_COLLISION_PATH}/collide.h
    ${ELEMENTS_SOURCE_COLLISION_PATH}/contact.h)

set(ELEMENTS_SOURCE_IO_PATH ${ELEMENTS_PATH}/io)
set(ELEMENTS_SOURCE_IO
    ${ELEMENTS_SOURCE_IO_PATH}/utils/file_guard.h
    ${ELEMENTS_SOURCE_IO_PATH}/file.h
    ${ELEMENTS_SOURCE_IO_PATH}/path.cpp
    ${ELEMENTS_SOURCE_IO_PATH}/path.h
    ${ELEMENTS_SOURCE_IO_PATH}/system.h)

set(ELEMENTS_SOURCE_MATH_PATH ${ELEMENTS_PATH}/math)
set(ELEMENTS_SOURCE_MATH
    ${ELEMENTS_SOURCE_MATH_PATH}/common.h
    ${ELEMENTS_SOURCE_MATH_PATH}/constants.h
    ${ELEMENTS_SOURCE_MATH_PATH}/geometric.h
    ${ELEMENTS_SOURCE_MATH_PATH}/matrix.h
    ${ELEMENTS_SOURCE_MATH_PATH}/quaternion.h
    ${ELEMENTS_SOURCE_MATH_PATH}/transform.h
    ${ELEMENTS_SOURCE_MATH_PATH}/trigonometry.h
    ${ELEMENTS_SOURCE_MATH_PATH}/types.h)

set(ELEMENTS_SOURCE_METRICS_PATH ${ELEMENTS_PATH}/metrics)
set(ELEMENTS_SOURCE_METRICS
    ${ELEMENTS_SOURCE_METRICS_PATH}/metrics.cpp
    ${ELEMENTS_SOURCE_METRICS_PATH}/metrics.h)

set(ELEMENTS_SOURCE_PREFERENCES_PATH ${ELEMENTS_PATH}/preferences)
set(ELEMENTS_SOURCE_PREFERENCES
    ${ELEMENTS_SOURCE_PREFERENCES_PATH}/preferences.cpp
    ${ELEMENTS_SOURCE_PREFERENCES_PATH}/preferences.h)

set(ELEMENTS_SOURCE_RENDERING_PATH ${ELEMENTS_PATH}/rendering)
set(ELEMENTS_SOURCE_RENDERING
    ${ELEMENTS_SOURCE_RENDERING_PATH}/computation/compute_product_index.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/computation/compute_product_index.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/computation/compute_target.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/computation/compute_target.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/buffer.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/opengl.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/program.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/program.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/shader.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/shader.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target_attachment.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target_buffered.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target_buffered.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target_maker.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target_maker.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/target.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/texture_maker.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/texture_policy.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/texture.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/core/texture.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/blend.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/blend.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/blur.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/blur.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/clear.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/clear.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/forwards.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/gradient.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/gradient.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/light_scattered.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/light_scattered.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/tone.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/effects/tone.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/models/model_warehouse.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/models/model_warehouse.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/models/model.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/models/model.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/models/process_load_model.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/models/process_load_model.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_base.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_composition.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_composition.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_slot.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target_input.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target_input.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target_placement.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target_placement.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target_storage.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target_storage.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/passes/pass_target.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/primitives/icosphere.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/primitives/icosphere.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/primitives/square.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/primitives/square.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/state/state_macro.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/state/state_traits.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/state/state.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/forward_process.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/forward_process.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/forward.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/forward.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_geometry_pass.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_geometry_pass.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_geometry_process.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_geometry_process.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_lighting_pass.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_lighting_pass.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_lighting_process.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_lighting_process.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_reconstruct_pass.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_reconstruct_pass.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_reconstruct_process.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp_reconstruct_process.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/techniques/lpp.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/utils/program_data.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/utils/program_data.h
    ${ELEMENTS_SOURCE_RENDERING_PATH}/utils/program_loader.cpp
    ${ELEMENTS_SOURCE_RENDERING_PATH}/utils/program_loader.h)

set(ELEMENTS_SOURCE_SCENE_PATH ${ELEMENTS_PATH}/scene)
set(ELEMENTS_SOURCE_SCENE
    ${ELEMENTS_SOURCE_SCENE_PATH}/camera/camera.cpp
    ${ELEMENTS_SOURCE_SCENE_PATH}/camera/camera.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/entity/entity.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/entity/geometry.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/entity/materials.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/entity/mesh.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/entity/vertices.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/graph/node.cpp
    ${ELEMENTS_SOURCE_SCENE_PATH}/graph/node.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/light/light.cpp
    ${ELEMENTS_SOURCE_SCENE_PATH}/light/light.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/modifier/modifier.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/modifier/positioning.cpp
    ${ELEMENTS_SOURCE_SCENE_PATH}/modifier/positioning.h
    ${ELEMENTS_SOURCE_SCENE_PATH}/scene.cpp
    ${ELEMENTS_SOURCE_SCENE_PATH}/scene.h)

set(ELEMENTS_SOURCE_SIMULATION_PATH ${ELEMENTS_PATH}/simulation)
set(ELEMENTS_SOURCE_SIMULATION
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/air/system.cpp
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/air/system.h
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/air/volume.cpp
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/air/volume.h
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/config.h
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/config.cpp
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/obstacle.h
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/particle.h
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/system.cpp
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/system.h
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/volume.cpp
    ${ELEMENTS_SOURCE_SIMULATION_PATH}/liquid/volume.h)

set(ELEMENTS_SOURCE_SYNCHRONIZATION_PATH ${ELEMENTS_PATH}/synchronization)
set(ELEMENTS_SOURCE_SYNCHRONIZATION
    ${ELEMENTS_SOURCE_SYNCHRONIZATION_PATH}/future.h
    ${ELEMENTS_SOURCE_SYNCHRONIZATION_PATH}/signal.h
    ${ELEMENTS_SOURCE_SYNCHRONIZATION_PATH}/task.h)

set(ELEMENTS_SOURCE_TIMING_PATH ${ELEMENTS_PATH}/timing)
set(ELEMENTS_SOURCE_TIMING
    ${ELEMENTS_SOURCE_TIMING_PATH}/framerate.cpp
    ${ELEMENTS_SOURCE_TIMING_PATH}/framerate.h
    ${ELEMENTS_SOURCE_TIMING_PATH}/timer.cpp
    ${ELEMENTS_SOURCE_TIMING_PATH}/timer.h
    ${ELEMENTS_SOURCE_TIMING_PATH}/update.cpp
    ${ELEMENTS_SOURCE_TIMING_PATH}/update.h)

set(ELEMENTS_SOURCE_UI_PATH ${ELEMENTS_PATH}/ui)
set(ELEMENTS_SOURCE_UI
    ${ELEMENTS_SOURCE_UI_PATH}/controls/button.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/controls/button.h
    ${ELEMENTS_SOURCE_UI_PATH}/controls/check.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/controls/check.h
    ${ELEMENTS_SOURCE_UI_PATH}/controls/label.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/controls/label.h
    ${ELEMENTS_SOURCE_UI_PATH}/controls/panel.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/controls/panel.h
    ${ELEMENTS_SOURCE_UI_PATH}/controls/slider.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/controls/slider.h
    ${ELEMENTS_SOURCE_UI_PATH}/freetype/forwards.h
    ${ELEMENTS_SOURCE_UI_PATH}/freetype/line.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/freetype/line.h
    ${ELEMENTS_SOURCE_UI_PATH}/freetype/manager.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/freetype/manager.h
    ${ELEMENTS_SOURCE_UI_PATH}/control.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/control.h
    ${ELEMENTS_SOURCE_UI_PATH}/system.cpp
    ${ELEMENTS_SOURCE_UI_PATH}/system.h
    ${ELEMENTS_SOURCE_UI_PATH}/types.h)

set(ELEMENTS_SOURCE_UTILS_PATH ${ELEMENTS_PATH}/utils)
set(ELEMENTS_SOURCE_UTILS
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/dependency_index.h
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/enum.h
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/iterator_range.h
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/optional.h
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/pointer.h
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/product.h
    ${ELEMENTS_SOURCE_UTILS_PATH}/std/values.h)

add_library(elements STATIC
    ${ELEMENTS_SOURCE_ASSETS}
    ${ELEMENTS_SOURCE_COLLISION}
    ${ELEMENTS_SOURCE_IO}
    ${ELEMENTS_SOURCE_MATH}
    ${ELEMENTS_SOURCE_METRICS}
    ${ELEMENTS_SOURCE_PREFERENCES}
    ${ELEMENTS_SOURCE_RENDERING}
    ${ELEMENTS_SOURCE_SCENE}
    ${ELEMENTS_SOURCE_SIMULATION}
    ${ELEMENTS_SOURCE_SYNCHRONIZATION}
    ${ELEMENTS_SOURCE_TIMING}
    ${ELEMENTS_SOURCE_UI}
    ${ELEMENTS_SOURCE_UTILS})

target_include_directories(elements PRIVATE ${ELEMENTS_PATH} ${EXTERNAL_INCLUDES})
target_include_directories(elements PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ELEMENTS_PATH}
    ${EXTERNAL_PATH_SNAPE}/include
    ${EXTERNAL_PATH_GLM})

target_compile_options(elements PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
target_compile_options(elements PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wextra -Werror>)
target_compile_options(elements PUBLIC $<$<CONFIG:RELEASE>:-O3 -ffast-math -Wall -Wextra -Werror>)
if(NOT ANDROID)
    set_target_properties(elements PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

#experiments
set(EXPERIMENTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/experiments)

if(NOT ANDROID)
    set(EXPERIMENTS_LIQUID TRUE)
    set(EXPERIMENTS_FIRE TRUE)
    set(EXPERIMENTS_LIGHT TRUE)
    set(EXPERIMENTS_AIR TRUE)
    set(EXPERIMENTS_STRANGE TRUE)
    set(EXPERIMENTS_CHARACTER TRUE)
    set(EXPERIMENTS_DEMO TRUE)
endif()

if(EXPERIMENTS_LIQUID)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/liquid/pass_liquid.cpp
        ${EXPERIMENTS_PATH}/liquid/pass_liquid.h
        ${EXPERIMENTS_PATH}/liquid/pass_metaballs.cpp
        ${EXPERIMENTS_PATH}/liquid/pass_metaballs.h
        ${EXPERIMENTS_PATH}/liquid/pass_particles.cpp
        ${EXPERIMENTS_PATH}/liquid/pass_particles.h
        ${EXPERIMENTS_PATH}/liquid/renderer.cpp
        ${EXPERIMENTS_PATH}/liquid/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_FIRE)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/fire/pass_fire.cpp
        ${EXPERIMENTS_PATH}/fire/pass_fire.h
        ${EXPERIMENTS_PATH}/fire/pass_raymarching.cpp
        ${EXPERIMENTS_PATH}/fire/pass_raymarching.h
        ${EXPERIMENTS_PATH}/fire/renderer.cpp
        ${EXPERIMENTS_PATH}/fire/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_LIGHT)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/light/pass_occluding.cpp
        ${EXPERIMENTS_PATH}/light/pass_occluding.h
        ${EXPERIMENTS_PATH}/light/pass_particles.cpp
        ${EXPERIMENTS_PATH}/light/pass_particles.h
        ${EXPERIMENTS_PATH}/light/pass_positions.cpp
        ${EXPERIMENTS_PATH}/light/pass_positions.h
        ${EXPERIMENTS_PATH}/light/pass_velocities.cpp
        ${EXPERIMENTS_PATH}/light/pass_velocities.h
        ${EXPERIMENTS_PATH}/light/renderer.cpp
        ${EXPERIMENTS_PATH}/light/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_AIR)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/air/pass_particles.cpp
        ${EXPERIMENTS_PATH}/air/pass_particles.h
        ${EXPERIMENTS_PATH}/air/pass_positions.cpp
        ${EXPERIMENTS_PATH}/air/pass_positions.h
        ${EXPERIMENTS_PATH}/air/pass_velocities.cpp
        ${EXPERIMENTS_PATH}/air/pass_velocities.h
        ${EXPERIMENTS_PATH}/air/renderer.cpp
        ${EXPERIMENTS_PATH}/air/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_STRANGE)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/strange/attractors.cpp
        ${EXPERIMENTS_PATH}/strange/attractors.h
        ${EXPERIMENTS_PATH}/strange/particles_product.cpp
        ${EXPERIMENTS_PATH}/strange/particles_product.h
        ${EXPERIMENTS_PATH}/strange/pass_particles.cpp
        ${EXPERIMENTS_PATH}/strange/pass_particles.h
        ${EXPERIMENTS_PATH}/strange/pass_positions.cpp
        ${EXPERIMENTS_PATH}/strange/pass_positions.h
        ${EXPERIMENTS_PATH}/strange/renderer.cpp
        ${EXPERIMENTS_PATH}/strange/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_CHARACTER)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/character/renderer.cpp
        ${EXPERIMENTS_PATH}/character/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_DEMO)
    set(SOURCE_FILES
        ${EXPERIMENTS_PATH}/demo/renderer.cpp
        ${EXPERIMENTS_PATH}/demo/renderer.h)
    list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
endif()

if(EXPERIMENTS_SOURCE_FILES)
    if(PLATFORM_ANDROID)
        set(JNI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)
        set(SOURCE_FILES
            ${JNI_PATH}/asset_fs.cpp
            ${JNI_PATH}/asset_fs.h
            ${JNI_PATH}/jni_common.cpp
            ${JNI_PATH}/jni_environment.h
            ${JNI_PATH}/logging.h
            ${JNI_PATH}/metrics.cpp
            ${JNI_PATH}/metrics.h
            ${JNI_PATH}/preferences.cpp
            ${JNI_PATH}/preferences.h
            ${JNI_PATH}/renderer_factory.h)
        list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})

        if(EXPERIMENTS_LIQUID)
            set(SOURCE_FILES
                ${JNI_PATH}/liquid/liquid_config.cpp
                ${JNI_PATH}/liquid/liquid_config.h
                ${JNI_PATH}/liquid/liquid_jni.cpp
                ${JNI_PATH}/liquid/liquid_renderer.cpp
                ${JNI_PATH}/liquid/liquid_renderer.h
                ${JNI_PATH}/liquid/liquid_ui.cpp
                ${JNI_PATH}/liquid/liquid_ui.h)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        if(EXPERIMENTS_FIRE)
            set(SOURCE_FILES
                ${JNI_PATH}/fire/fire_config.cpp
                ${JNI_PATH}/fire/fire_config.h
                ${JNI_PATH}/fire/fire_jni.cpp
                ${JNI_PATH}/fire/fire_renderer.cpp
                ${JNI_PATH}/fire/fire_renderer.h
                ${JNI_PATH}/fire/fire_ui.cpp
                ${JNI_PATH}/fire/fire_ui.h)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        if(EXPERIMENTS_LIGHT)
            set(SOURCE_FILES
                ${JNI_PATH}/light/light_jni.cpp
                ${JNI_PATH}/light/light_renderer.h
                ${JNI_PATH}/light/light_renderer.cpp)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        if(EXPERIMENTS_STRANGE)
            set(SOURCE_FILES
                ${JNI_PATH}/strange/strange_jni.cpp
                ${JNI_PATH}/strange/strange_renderer.h
                ${JNI_PATH}/strange/strange_renderer.cpp)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        if(EXPERIMENTS_AIR)
            set(SOURCE_FILES
                ${JNI_PATH}/air/air_jni.cpp
                ${JNI_PATH}/air/air_renderer.h
                ${JNI_PATH}/air/air_renderer.cpp)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        if(EXPERIMENTS_CHARACTER)
            set(SOURCE_FILES
                ${JNI_PATH}/character/character_jni.cpp
                ${JNI_PATH}/character/character_renderer.h
                ${JNI_PATH}/character/character_renderer.cpp)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        if(EXPERIMENTS_DEMO)
            set(SOURCE_FILES
                ${JNI_PATH}/demo/demo_jni.cpp
                ${JNI_PATH}/demo/demo_renderer.h
                ${JNI_PATH}/demo/demo_renderer.cpp)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        find_library(NDK_LIBRARY_ANDROID NAMES android)
        if(NOT NDK_LIBRARY_ANDROID)
            message(FATAL_ERROR "Can not find NDK Android library")
        endif()

        find_library(NDK_LIBRARY_LOG NAMES log)
        if(NOT NDK_LIBRARY_LOG)
            message(FATAL_ERROR "Can not find NDK Log library")
        endif()

        find_library(NDK_LIBRARY_GLSE2 NAMES GLESv2)
        if(NOT NDK_LIBRARY_GLSE2)
            message(FATAL_ERROR "Can not find NDK GLESv2 library")
        endif()

        add_library(experiments SHARED ${EXPERIMENTS_SOURCE_FILES})
        target_link_libraries(experiments ${NDK_LIBRARY_ANDROID} elements atomic
            ${EXTERNAL_LIBRARIES} ${NDK_LIBRARY_GLSE2} ${NDK_LIBRARY_LOG})
        target_include_directories(experiments PRIVATE ${JNI_PATH})
        target_compile_options(experiments PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
        target_compile_options(experiments PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wextra -Werror>)
        target_compile_options(experiments PUBLIC $<$<CONFIG:RELEASE>:-O3 -ffast-math -Wall -Wextra -Werror>)

    else()
        set(JNI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)
        set(DESKTOP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop)
        set(SOURCE_FILES
            ${JNI_PATH}/asset_fs.cpp
            ${JNI_PATH}/asset_fs.h
            ${JNI_PATH}/logging.h
            ${JNI_PATH}/metrics.cpp
            ${JNI_PATH}/metrics.h
            ${JNI_PATH}/preferences.cpp
            ${JNI_PATH}/preferences.h
            ${JNI_PATH}/renderer_factory.h
            ${DESKTOP_PATH}/Library/CapsView.cpp
            ${DESKTOP_PATH}/Library/CapsView.h
            ${DESKTOP_PATH}/Library/checkbox.cpp
            ${DESKTOP_PATH}/Library/checkbox.h
            ${DESKTOP_PATH}/Library/ClearBackground.cpp
            ${DESKTOP_PATH}/Library/ClearBackground.h
            ${DESKTOP_PATH}/Library/DrawableUiGameComponent.cpp
            ${DESKTOP_PATH}/Library/DrawableUiGameComponent.h
            ${DESKTOP_PATH}/Library/ReaderHelpers.cpp
            ${DESKTOP_PATH}/Library/ReaderHelpers.h
            ${DESKTOP_PATH}/Library/RenderingGame.cpp
            ${DESKTOP_PATH}/Library/RenderingGame.h
            ${DESKTOP_PATH}/Library/SliderModel.cpp
            ${DESKTOP_PATH}/Library/SliderModel.h
            ${DESKTOP_PATH}/Library/TestCard.cpp
            ${DESKTOP_PATH}/Library/TestCard.h
            ${DESKTOP_PATH}/Library/UiAsset.cpp
            ${DESKTOP_PATH}/Library/UiAsset.h
            ${DESKTOP_PATH}/Library/UiReader.cpp
            ${DESKTOP_PATH}/Library/UiReader.h)
        list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})

        add_library(experiments STATIC ${EXPERIMENTS_SOURCE_FILES})

        if(WIN32)
            target_compile_definitions(experiments PRIVATE WIN32)
            list(APPEND EXTERNAL_LIBRARIES glu32)
            list(APPEND EXTERNAL_LIBRARIES opengl32)
        elseif(UNIX)
            list(APPEND EXTERNAL_LIBRARIES GL)
            list(APPEND EXTERNAL_LIBRARIES GLU)
        endif()

        target_link_libraries(experiments elements ${EXTERNAL_LIBRARIES})
        target_include_directories(experiments PRIVATE ${ELEMENTS_PATH} ${EXTERNAL_INCLUDES})
        target_include_directories(experiments PRIVATE ${JNI_PATH} ${DESKTOP_PATH}/Library)
        target_compile_options(experiments PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
        target_compile_options(experiments PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wextra -Werror>)
        target_compile_options(experiments PUBLIC $<$<CONFIG:RELEASE>:-O3 -ffast-math -Wall -Wextra -Werror>)
        set_target_properties(experiments PROPERTIES POSITION_INDEPENDENT_CODE ON)

        # Copy assets

        set(PLATFORM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform)
        file(GLOB WALLPAPER_FOLDERS RELATIVE ${PLATFORM_PATH}/android/elements
                                             ${PLATFORM_PATH}/android/elements/*Wallpaper
                                             ${PLATFORM_PATH}/android/elements/Demo)
        file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*
                                         ${PLATFORM_PATH}/android/elements/*Wallpaper/src/main/assets/*
                                         ${PLATFORM_PATH}/android/elements/Demo/src/main/assets/*)

        add_custom_target(copy_assets)

        foreach(RESOURCE_FILE ${RESOURCE_FILES})
            string(REPLACE "//" "/" sourcePath ${RESOURCE_FILE})
            string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets destination ${sourcePath})

            foreach(WALLPAPER ${WALLPAPER_FOLDERS})
                set(ADDITION_RESOURCE_PATH ${PLATFORM_PATH}/android/elements/${WALLPAPER}/src/main/assets)
                string(REPLACE ${ADDITION_RESOURCE_PATH} ${CMAKE_BINARY_DIR}/assets destination ${destination})
            endforeach()

            add_custom_command(TARGET copy_assets PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sourcePath}" "${destination}")
        endforeach()

        # apps

        file(GLOB_RECURSE SHADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders
                                                ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/*.prog)
        foreach(SHADER_FILE ${SHADER_FILES})
            string(REPLACE ".prog" "" app_path ${SHADER_FILE})
            set(app_full_path ${DESKTOP_PATH}/${app_path})

            if((EXISTS ${app_full_path}) AND (IS_DIRECTORY ${app_full_path}))
                string(FIND ${app_path} "/" pos1 REVERSE)

                if(${pos1} GREATER -1)
                    string(SUBSTRING ${app_path} 0 ${pos1} tmp_path)
                    string(FIND ${tmp_path} "/" pos2 REVERSE)

                    if(${pos2} GREATER -1)
                        math(EXPR pos2 "${pos2} + 1")
                    else()
                        set(pos2 0)
                    endif()

                    string(SUBSTRING ${app_path} ${pos2} -1 app_path)
                    string(REPLACE "/" "_" app_path ${app_path})
                endif()

                file(GLOB APP_SRC_FILES ${app_full_path}/*.h ${app_full_path}/*.cpp)
                add_executable(${app_path} ${APP_SRC_FILES})

                if(WIN32)
                    target_compile_definitions(${app_path} PRIVATE WIN32)
                endif()

                target_link_libraries(${app_path} experiments)
                target_include_directories(${app_path} PRIVATE ${ELEMENTS_PATH} ${EXTERNAL_INCLUDES})
                target_include_directories(${app_path} PRIVATE ${DESKTOP_PATH}/Library ${PLATFORM_PATH})
                target_compile_options(${app_path} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
                target_compile_options(${app_path} PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wextra -Werror>)
                target_compile_options(${app_path} PUBLIC $<$<CONFIG:RELEASE>:-O3 -ffast-math -Wall -Wextra -Werror>)
                set_target_properties(${app_path} PROPERTIES POSITION_INDEPENDENT_CODE ON)
                add_dependencies(${app_path} copy_assets)
            endif()
        endforeach()

    endif()
endif()
