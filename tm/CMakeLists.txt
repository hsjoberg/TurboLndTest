cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
        -fexceptions
        -frtti)
        #-std=c++20) # collides with C code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

file(GLOB tm_SRC CONFIGURE_DEPENDS *.cpp)
add_library(tm STATIC ${tm_SRC})

target_include_directories(tm PUBLIC .)
target_include_directories(react_codegen_AppSpecs PUBLIC .)

target_link_libraries(tm
        jsi
        react_nativemodule_core
        react_codegen_AppSpecs
        lnd
)

# lnd
add_library(lib_lnd SHARED IMPORTED)
set_property(TARGET lib_lnd PROPERTY IMPORTED_NO_SONAME 1)
set_target_properties(lib_lnd PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/liblnd.so)

target_link_libraries(${CMAKE_PROJECT_NAME} lib_lnd)


# libb64
# set(LIBB64_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libb64)
# set(LIBB64_SOURCES
#     ${LIBB64_PATH}/src/cencode.c
#     ${LIBB64_PATH}/src/cdecode.c
# )
# target_sources(tm PRIVATE ${LIBB64_SOURCES})
# target_include_directories(tm PUBLIC ${LIBB64_PATH}/include)

# set(LIBB64_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libb64)
# include_directories(${LIBB64_PATH}/include)
# add_library(lib_libb64
#   STATIC
#   ${LIBB64_PATH}/src/cencode.c
#   ${LIBB64_PATH}/src/cdecode.c
# )

# target_link_libraries(${CMAKE_PROJECT_NAME} lib_libb64)
