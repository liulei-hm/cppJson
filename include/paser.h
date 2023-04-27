//
// Created by liulei on 2023/4/12.
//

#ifndef CPPTHING_PASER_H
#define CPPTHING_PASER_H
#pragma once

#include <string>
#include "json.h"

using namespace std;

namespace liulei {
    class Parser {
    public:
        Parser();

        void load(const string &str);

        Json parse();

    private:
        void skip_space();

        char get_token();

        Json parse_null();

        Json parse_bool();

        Json parse_number();

        Json parse_int();

        Json parse_double();

        string parse_string();

        Json parse_array();

        Json parse_object();

    private:

        string m_str;
        int m_idx;
    };

}
#endif //CPPTHING_PASER_H
