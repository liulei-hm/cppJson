//
// Created by liulei on 2023/4/27.
//

#ifndef CPPJSON_READER_H
#define CPPJSON_READER_H

#include <string>
#include <fstream>
#include <sstream>

class Reader{
public:
    Reader(){};
    std::string readfile(const std::string &path){
        std::fstream fin(path);
        std::stringstream ss;
        ss << fin.rdbuf();
        return ss.str();
    }
};

#endif //CPPJSON_READER_H
