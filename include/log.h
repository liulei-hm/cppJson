//
// Created by liulei on 2023/4/27.
//

#ifndef CPPJSON_LOG_H
#define CPPJSON_LOG_H

#include <iostream>
#include <cstdarg>
#include <initializer_list>

//#define _DEBUG


#define LOG_LEVEL_ERROR             (1)
#define LOG_LEVEL_WARNING           (2)
#define LOG_LEVEL_INFO              (3)
#define LOG_LEVEL_DEBUG             (4)

#ifdef _DEBUG
#define LOG_ERROR(...)          logOut(LOG_LEVEL_ERROR, __VA_ARGS__);
#define LOG_WARNING(...)        logOut(LOG_LEVEL_WARNING, __VA_ARGS__);
#define LOG_INFO(...)           logOut(LOG_LEVEL_INFO, __VA_ARGS__);
#define LOG_DEBUG(...)          logOut(LOG_LEVEL_DEBUG, __VA_ARGS__);
#endif

#ifndef _DEBUG
#define LOG_ERROR(...)
#define LOG_WARNING(...)
#define LOG_INFO(...)
#define LOG_DEBUG(...)
#endif

template<class ...Args>
void logOut(int _log_level, Args... args)
{
    auto print = [](auto i){std::cout<< i << " ";};
    std::initializer_list<int>{(print(args),0)...};
    std::cout<< std::endl;
}



#endif //CPPJSON_LOG_H
