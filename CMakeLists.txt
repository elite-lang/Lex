cmake_minimum_required(VERSION 2.8)
project(lex)

if(NOT BUILD_ALL) # BUILD_ALL负责确认是不是所有子项目统一配置构建
SET (CMAKE_BUILD_TYPE Debug)
SET (CMAKE_CXX_COMPILER_ENV_VAR "clang++")
SET (CMAKE_CXX_FLAGS "-std=c++11")
SET (CMAKE_CXX_FLAGS_DEBUG   "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL  "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE  "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(../ExIconv/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ExIconv/build)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../extlib/lib)
endif()


# 核心路径配置
include_directories(include src ../header_libs/cereal-1.1.2)
file(GLOB_RECURSE source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM  source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(USE_DYNAMIC)
	add_library(lex SHARED ${source_files}) # 使用动态库
	install(TARGETS lex runtime DESTINATION bin)
else()
	add_library(lex STATIC ${source_files}) # 使用静态库
	install(TARGETS lex ARCHIVE DESTINATION lib)
endif()


if(NOT BUILD_ALL)

add_executable(lextest ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(lextest lex exiconv iconv charsetdetect)

endif()
