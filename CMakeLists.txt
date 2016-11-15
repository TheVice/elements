cmake_minimum_required(VERSION 2.8.12)

project("elements")

if(ANDROID)

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

add_subdirectory(${EXTERNAL_PATH_ASSIMP})
target_compile_options(assimp PRIVATE -fexceptions -frtti)

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

#freetype

set(EXTERNAL_PATH_FREETYPE ${EXTERNAL_PATH}/freetype2)
add_subdirectory(${EXTERNAL_PATH_FREETYPE})
target_compile_definitions(freetype PRIVATE FT2_BUILD_LIBRARY)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_FREETYPE}/include)
list(APPEND EXTERNAL_LIBRARIES freetype)

# glm

set(EXTERNAL_PATH_GLM ${EXTERNAL_PATH}/glm)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_GLM})

# libpng

set(EXTERNAL_PATH_PNG ${EXTERNAL_PATH}/libpng)
configure_file(${EXTERNAL_PATH_PNG}/scripts/pnglibconf.h.prebuilt
               ${EXTERNAL_PATH_PNG}/pnglibconf.h)
file(GLOB LIBPNG_SOURCE_FILES ${EXTERNAL_PATH_PNG}/*.h ${EXTERNAL_PATH_PNG}/*.c)
add_library(png STATIC ${LIBPNG_SOURCE_FILES})
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_PNG})
list(APPEND EXTERNAL_LIBRARIES png)

# pugixml

set(EXTERNAL_PATH_PUGIXML ${EXTERNAL_PATH}/pugixml)
add_subdirectory(${EXTERNAL_PATH_PUGIXML})
target_compile_definitions(pugixml PRIVATE PUGIXML_NO_EXCEPTIONS)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_PUGIXML}/src)
list(APPEND EXTERNAL_LIBRARIES pugixml)

# snape

set(EXTERNAL_PATH_SNAPE ${EXTERNAL_PATH}/snape)
list(APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_SNAPE}/include)

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

#experiments
set(EXPERIMENTS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/experiments)

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

        if(EXPERIMENTS_LIGHT)
            set(SOURCE_FILES
                ${JNI_PATH}/demo/demo_jni.cpp
                ${JNI_PATH}/demo/demo_renderer.h
                ${JNI_PATH}/demo/demo_renderer.cpp)
            list(APPEND EXPERIMENTS_SOURCE_FILES ${SOURCE_FILES})
        endif()

        add_library(experiments SHARED ${EXPERIMENTS_SOURCE_FILES})
        target_link_libraries(experiments android elements ${EXTERNAL_LIBRARIES} atomic GLESv2 log)
        target_include_directories(experiments PRIVATE ${JNI_PATH})
        target_compile_options(elements PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)
        target_compile_options(elements PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wextra -Werror>)
        target_compile_options(elements PUBLIC $<$<CONFIG:RELEASE>:-O3 -ffast-math -Wall -Wextra -Werror>)

    endif()
endif()

else()

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Build process cannot start from project source directory")
endif()

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
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/freetype2)
    set(freetype_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/freetype2)
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

  if(UNIX)
    include_directories(${CMAKE_BINARY_DIR}/libpng ${CMAKE_CURRENT_SOURCE_DIR}/third-party/libpng)
  endif()
  add_subdirectory(${freetype_Path} ${CMAKE_BINARY_DIR}/freetype)

  list(APPEND REQUIRED_SYS_INCLUDES ${freetype_Path}/include)

# SwiftShader
if(UNIX)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/SwiftShader)
    set(SwiftShader_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third-party/SwiftShader)
  elseif(DEFINED ENV{SWIFTSHADER_PATH})
    string(REPLACE "\\" "/" SwiftShader_PATH $ENV{SWIFTSHADER_PATH})
  elseif(DEFINED SWIFTSHADER_PATH)
    string(REPLACE "\\" "/" SwiftShader_PATH ${SWIFTSHADER_PATH})
  else()
    message(FATAL_ERROR "Could not find SwiftShader library, please check it at https://swiftshader.googlesource.com/SwiftShader")
  endif()

  if(NOT EXISTS ${SwiftShader_PATH}/CMakeLists.txt)
    message(FATAL_ERROR "Could not find CMakeLists.txt for SwiftShader library, please check it at https://swiftshader.googlesource.com/SwiftShader")
  endif()

#  file(READ ${SwiftShader_PATH}/CMakeLists.txt file_content)
#  string(REGEX REPLACE "CMAKE_SOURCE_DIR" "SwiftShader_PATH" file_content ${file_content})
#  file(WRITE ${CMAKE_BINARY_DIR}/SwiftShader/CMakeLists.txt ${file_content})

#  # set(BUILD_EGL OFF CACHE BOOL "" FORCE)
#  set(BUILD_GL32 OFF CACHE BOOL "" FORCE)
#  # set(BUILD_GLESv2 OFF CACHE BOOL "" FORCE)
#  set(BUILD_GLES_CM OFF CACHE BOOL "" FORCE)
#  set(BUILD_EXTRA_PROGRAMS OFF CACHE BOOL "" FORCE)
#  add_subdirectory(${CMAKE_BINARY_DIR}/SwiftShader ${CMAKE_BINARY_DIR}/SwiftShader)

#  list(APPEND REQUIRED_SYS_INCLUDES ${SwiftShader_PATH}/include)
endif()

# glew
if(WIN32)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glew-1.13.0)
    set(glew_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glew-1.13.0)
  elseif(DEFINED ENV{GLEW_PATH})
    string(REPLACE "\\" "/" glew_Path $ENV{GLEW_PATH})
  elseif(DEFINED GLEW_PATH)
    string(REPLACE "\\" "/" glew_Path ${GLEW_PATH})
  else()
    message(FATAL_ERROR "Could not find glew library, please check it at https://github.com/nigels-com/glew/releases")
  endif()
else()
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glew)
    set(glew_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glew)
  elseif(DEFINED ENV{GLEW_PATH})
    string(REPLACE "\\" "/" glew_Path $ENV{GLEW_PATH})
  elseif(DEFINED GLEW_PATH)
    string(REPLACE "\\" "/" glew_Path ${GLEW_PATH})
  else()
    message(FATAL_ERROR "Could not find glew library, please check it at https://github.com/nigels-com/glew/releases")
  endif()
endif()

if(UNIX)
  # glfixes
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfixes)
    set(glfixes_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfixes)
  elseif(DEFINED ENV{GLFIXES_PATH})
    string(REPLACE "\\" "/" glfixes_Path $ENV{GLFIXES_PATH})
  elseif(DEFINED GLFIXES_PATH)
    string(REPLACE "\\" "/" glfixes_Path ${GLFIXES_PATH})
  else()
    message(FATAL_ERROR "Could not find glfixes library, please check it at https://github.com/nigels-com/glfixes/releases")
  endif()

  if(NOT EXISTS "${CMAKE_BINARY_DIR}/glew")
    message("Copying ${glew_Path} into ${CMAKE_BINARY_DIR}/glew")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${glew_Path}" "${CMAKE_BINARY_DIR}/glew")
  endif()

  set(REQUIRED_TO_WRITE FALSE)
  file(READ "${CMAKE_BINARY_DIR}/glew/auto/Makefile" file_content)

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
    message("Write ${CMAKE_BINARY_DIR}/glew/auto/Makefile")
    file(WRITE "${CMAKE_BINARY_DIR}/glew/auto/Makefile" "${file_content}")
  endif()

  if(NOT EXISTS "${CMAKE_BINARY_DIR}/glew/auto/registry")
    message("Copying ${glfixes_Path} into ${CMAKE_BINARY_DIR}/glew/auto/registry")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${glfixes_Path}" "${CMAKE_BINARY_DIR}/glew/auto/registry")
  endif()

  # file(READ "${CMAKE_BINARY_DIR}/glew/build/cmake/CMakeLists.txt" file_content)
  # string(FIND "${file_content}" "add_custom_command" pos)
  # if("${pos}" EQUAL -1)
  #   set(ADDITION_COMMAND "add_custom_command(\n    OUTPUT \${CMAKE_BINARY_DIR}/glew/src/glew.c \${CMAKE_BINARY_DIR}/glew/src/glewinfo.c\n    WORKING_DIRECTORY .\n    COMMAND \${CMAKE_MAKE_PROGRAM}\n)\n")
  #   set(file_content "${file_content}\n\n${ADDITION_COMMAND}\n")
  #   message("Write ${CMAKE_BINARY_DIR}/glew/build/cmake/CMakeLists.txt")
  #   file(WRITE "${CMAKE_BINARY_DIR}/glew/build/cmake/CMakeLists.txt" "${file_content}")
  # endif()

  # add_subdirectory("${CMAKE_BINARY_DIR}/glew/build/cmake" "${CMAKE_BINARY_DIR}/glew/build/cmake")

  execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} -C "${CMAKE_BINARY_DIR}/glew/auto")
  set(glew_Path ${CMAKE_BINARY_DIR}/glew)
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

# glfw
if(UNIX)
  add_definitions(-DGLFW_EXPOSE_NATIVE_X11)
  add_definitions(-DGLFW_EXPOSE_NATIVE_GLX)
elseif(WIN32)
  add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32)
  add_definitions(-DGLFW_EXPOSE_NATIVE_WGL)
endif()    
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfw)
    set(glfw_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfw)
  elseif(DEFINED ENV{GLFW_PATH})
    string(REPLACE "\\" "/" glfw_Path $ENV{GLFW_PATH})
  elseif(DEFINED GLFW_PATH)
    string(REPLACE "\\" "/" glfw_Path ${GLFW_PATH})
  else()
    message(FATAL_ERROR "Could not find glfw library, please check it at https://github.com/glfw/glfw/releases")
  endif()

  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory(${glfw_Path} ${CMAKE_BINARY_DIR}/glfw)

  list(APPEND REQUIRED_SYS_INCLUDES ${glfw_Path}/include)

# glm
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glm)
    set(glm_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glm)
  elseif(DEFINED ENV{GLM_PATH})
    string(REPLACE "\\" "/" glm_Path $ENV{GLM_PATH})
  elseif(DEFINED GLM_PATH)
    string(REPLACE "\\" "/" glm_Path ${GLM_PATH})
  else()
    message(FATAL_ERROR "Could not find glm library, please check it at https://github.com/g-truc/glm/releases")
  endif()
  list(APPEND REQUIRED_SYS_INCLUDES ${glm_Path})

# libpng
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/libpng)
    set(libpng_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/libpng)
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

  configure_file(${libpng_Path}/scripts/pnglibconf.h.prebuilt
                 ${CMAKE_BINARY_DIR}/libpng/pnglibconf.h)
  target_include_directories(libpng SYSTEM PRIVATE ${zlib_Path} ${CMAKE_BINARY_DIR}/libpng)
  list(APPEND REQUIRED_SYS_INCLUDES ${CMAKE_BINARY_DIR}/libpng)
  # target_include_directories(freetype ${CMAKE_BINARY_DIR}/libpng ${libpng_Path})
  # include_directories(${libpng_Path})

  list(APPEND REQUIRED_SYS_INCLUDES ${libpng_Path})

# pugixml
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/pugixml)
    set(pugixml_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/pugixml)
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

# assimp
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/assimp/code)
    set(assimp_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/assimp)
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

# z
  if(EXISTS ${assimp_Path}/contrib/zlib)
    set(zlib_Path ${assimp_Path}/contrib/zlib)
  elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third-party/zlib)
    set(zlib_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/zlib)
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

# oel
set(oel_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/oel)
file(GLOB OEL_SRC_FILES ${oel_Path}/*.h ${oel_Path}/*.cpp)
add_library(oel ${OEL_SRC_FILES})
target_include_directories(oel SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${oel_Path})

# snape
set(snape_Path ${CMAKE_CURRENT_SOURCE_DIR}/third-party/snape)

# elements
set(elements_Path ${CMAKE_CURRENT_SOURCE_DIR}/elements)
file(GLOB_RECURSE ELEMENTS_SRC_FILES ${elements_Path}/*.h ${elements_Path}/*.cpp)

add_library(elements ${ELEMENTS_SRC_FILES})
target_include_directories(elements PRIVATE ${elements_Path} ${snape_Path}/include)
target_include_directories(elements SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${elements_Path})

# platform library
set(platform_Path ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop)
file(GLOB PLATFORM_SRC_FILES ${platform_Path}/Library/*.h ${platform_Path}/Library/*.cpp
                             ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/asset_fs.h
                             ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/asset_fs.cpp
                             ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/metrics.h
                             ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/metrics.cpp
                             ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/preferences.h
                             ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni/preferences.cpp)

add_library(desktop ${PLATFORM_SRC_FILES})
target_include_directories(desktop PRIVATE ${REQUIRED_INCLUDES}
                                           ${elements_Path}/..
                                           ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)
target_include_directories(desktop SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
list(APPEND REQUIRED_INCLUDES ${platform_Path} ${platform_Path}/Library
                                               ${elements_Path}/..
                                               ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)

# Copy assets
file(GLOB WALLPAPER_FOLDERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements
                                     ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/*Wallpaper
                                     ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/Demo)
file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*
                                 ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/*Wallpaper/src/main/assets/*
                                 ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/Demo/src/main/assets/*)

add_custom_target(copyAssets)

foreach(RESOURCE_FILE ${RESOURCE_FILES})
  string(REPLACE "//" "/" sourcePath ${RESOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets destination ${sourcePath})

  foreach(WALLPAPER ${WALLPAPER_FOLDERS})
    set(ADDITION_RESOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/${WALLPAPER}/src/main/assets)
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
list(APPEND REQUIRED_LIBRARIES libpng)
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
if(UNIX)
  list(APPEND REQUIRED_LIBRARIES X11)
  if(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    list(APPEND REQUIRED_LIBRARIES Xrandr Xi Xxf86vm Xcursor Xinerama)
  endif()
  list(APPEND REQUIRED_LIBRARIES pthread)
  list(APPEND REQUIRED_LIBRARIES GL)
  list(APPEND REQUIRED_LIBRARIES GLU)
endif()
if(WIN32)
  list(APPEND REQUIRED_LIBRARIES glu32)
  list(APPEND REQUIRED_LIBRARIES opengl32)
endif()

file(GLOB Experiments RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/experiments ${CMAKE_CURRENT_SOURCE_DIR}/experiments/*)
foreach(Experiment ${Experiments})
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/experiments/${Experiment})
    set(Experiment_Path ${CMAKE_CURRENT_SOURCE_DIR}/experiments/${Experiment})
    set(ADDITION_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/elements/libs/Elements/src/main/jni)

    file(GLOB SRC_FILES ${Experiment_Path}/*.h
                        ${Experiment_Path}/*.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop/${Experiment}/*.h
                        ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop/${Experiment}/*.cpp)

    file(GLOB ADDITION_SRC_FILES ${ADDITION_SOURCE_PATH}/${Experiment}/*.h
                                 ${ADDITION_SOURCE_PATH}/${Experiment}/*.cpp)
    list(REMOVE_ITEM ADDITION_SRC_FILES ${ADDITION_SOURCE_PATH}/${Experiment}/${Experiment}_jni.cpp)
    list(APPEND SRC_FILES ${ADDITION_SRC_FILES})
    list(APPEND SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/platform/android/input.h)

    add_executable(${Experiment} ${IS_SUBSYSTEM_WIN32} ${SRC_FILES})

    target_include_directories(${Experiment} PRIVATE ${REQUIRED_INCLUDES}
                                                     ${snape_Path}/include
                                                     ${CMAKE_CURRENT_SOURCE_DIR}/experiments/${Experiment}
                                                     ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop/${Experiment}
                                                     ${ADDITION_SOURCE_PATH}/${Experiment}
                                                     ${CMAKE_CURRENT_SOURCE_DIR}/platform)
    target_include_directories(${Experiment} SYSTEM PRIVATE ${REQUIRED_SYS_INCLUDES})
    target_link_libraries(${Experiment} ${REQUIRED_LIBRARIES})

    add_dependencies(${Experiment} copyAssets)
  endif()
endforeach()

# Flags
if(MSVC)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(FLAGS "${FLAGS} -Wall -Wextra -Werror")
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
  set(FLAGS "${FLAGS} -Wall -Wextra -Werror")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS} -std=c11")
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++1y")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++14")
  endif()
endif()

endif()
