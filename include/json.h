//
// Created by liulei on 2023/3/28.
//

#ifndef CPPTHING_JSON_H
#define CPPTHING_JSON_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;
namespace liulei {
    class Json {
    public:
        enum Type {
            json_null = 0,
            json_bool,
            json_int,
            json_double,
            json_string,
            json_array,
            json_object
        };

        //构造函数
        Json();

        Json(bool value);

        Json(int value);

        Json(double value);

        Json(const string &value);

        Json(const char *value);

        Json(Type type);

        //拷贝构造和拷贝赋值
        Json(const Json &other);

        Json &operator=(Json &other);

        //移动构造和移动赋值
        Json(Json &&other);

        Json &operator=(Json &&other) noexcept;

        //类型判断
        bool isNull() const { return m_type == json_null; }

        bool isBool() const { return m_type == json_bool; }

        bool isInt() const { return m_type == json_int; }

        bool isDouble() const { return m_type == json_double; }

        bool isString() const { return m_type == json_string; }

        bool isArray() const { return m_type == json_array; }

        bool isObject() const { return m_type == json_object; }

        //重载运算符，使得json对象可以赋值给bool类型的变量
        operator bool();

        operator int();

        operator double();

        operator string();

        //获取值
        bool asBool() const;

        int asInt() const;

        double asDouble() const;

        string asString() const;


        //数组运算符重载
        Json &operator[](int index);

        void append(const Json &other);

        //对象运算符重载
        Json &operator[](const char *key);

        Json &operator[](const string &key);

        //释放内存
        void clear();

        //数组遍历迭代器
        typedef std::vector<Json>::iterator iterator;

        iterator begin() {
            return m_value.m_array->begin();
        }

        iterator end() {
            return m_value.m_array->end();
        }

        //判断两个json是不是相等
        bool operator==(const Json &other);

        bool operator!=(const Json &other);

        //判断数组是否有某索引，对象是否有key
        bool has(int index);

        bool has(const char *key);

        bool has(const string &key);

        void remove(int index);

        void remove(const char *key);

        void remove(const string &key);

        //json序列化
        string str() const;

        //json字符串解析(反序列化)
        void parse(const string &str);

    private:
        union Value {
            bool m_bool;
            int m_int;
            double m_double;
            std::string *m_string;
            std::vector<Json> *m_array;
            std::map<string, Json> *m_object;
        };
        Type m_type;
        Value m_value;
    };
}
#endif //CPPTHING_JSON_H
