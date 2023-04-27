cmake_minimum_required(VERSION 3.23)
project(cppJson)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)

# 添加源文件目录
aux_source_directory(./src DIR_SRCS) #别名,只会遍历src目录下，无嵌套

add_executable(cppJson ${DIR_SRCS} include/timer.h include/log.h)


#手动添加到工程的方法
file(GLOB JSONCPP_SOURCE_FILES
        test_jsoncpp/*.cpp
        test_jsoncpp/*.h
        test_jsoncpp/lib/*.h
        test_jsoncpp/lib/*.cpp
        )
add_executable(test_jsoncpp ${JSONCPP_SOURCE_FILES})


#手动添加到工程的方法
file(GLOB CJSON_SOURCE_FILES
        test_cJSON/*.h
        test_cJSON/*.c
        test_cJSON/lib/*.c
        test_cJSON/lib/*.h
        )
add_executable(test_cJSON ${CJSON_SOURCE_FILES})