cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
        -fexceptions
        -frtti
        -std=c++20)

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





# target_include_directories(tm PUBLIC
#   "${CMAKE_SOURCE_DIR}/../../../../../lnd"
# )
# #target_link_libraries(tm lnd)
# add_library(lnd SHARED IMPORTED)
# set_property(TARGET lnd PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/liblnd.so)


add_library(lib_foo SHARED IMPORTED)
set_property(TARGET lib_foo PROPERTY IMPORTED_NO_SONAME 1)
set_target_properties(lib_foo PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/liblnd.so)
target_include_directories(tm PUBLIC
  "${CMAKE_SOURCE_DIR}/../../../../../lnd"
)
# include_directories(${CMAKE_SOURCE_DIR}/../../../../lnd/)


target_link_libraries(${CMAKE_PROJECT_NAME} lib_foo)




add_library(lib_bar SHARED IMPORTED)
set_property(TARGET lib_bar PROPERTY IMPORTED_NO_SONAME 1)
set_target_properties(lib_bar PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/liba.so)

target_link_libraries(${CMAKE_PROJECT_NAME} lib_bar)
