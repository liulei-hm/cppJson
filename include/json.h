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

        //���캯��
        Json();

        Json(bool value);

        Json(int value);

        Json(double value);

        Json(const string &value);

        Json(const char *value);

        Json(Type type);

        //��������Ϳ�����ֵ
        Json(const Json &other);

        Json &operator=(Json &other);

        //�ƶ�������ƶ���ֵ
        Json(Json &&other);

        Json &operator=(Json &&other) noexcept;

        //�����ж�
        bool isNull() const { return m_type == json_null; }

        bool isBool() const { return m_type == json_bool; }

        bool isInt() const { return m_type == json_int; }

        bool isDouble() const { return m_type == json_double; }

        bool isString() const { return m_type == json_string; }

        bool isArray() const { return m_type == json_array; }

        bool isObject() const { return m_type == json_object; }

        //�����������ʹ��json������Ը�ֵ��bool���͵ı���
        operator bool();

        operator int();

        operator double();

        operator string();

        //��ȡֵ
        bool asBool() const;

        int asInt() const;

        double asDouble() const;

        string asString() const;


        //�������������
        Json &operator[](int index);

        void append(const Json &other);

        //�������������
        Json &operator[](const char *key);

        Json &operator[](const string &key);

        //�ͷ��ڴ�
        void clear();

        //�������������
        typedef std::vector<Json>::iterator iterator;

        iterator begin() {
            return m_value.m_array->begin();
        }

        iterator end() {
            return m_value.m_array->end();
        }

        //�ж�����json�ǲ������
        bool operator==(const Json &other);

        bool operator!=(const Json &other);

        //�ж������Ƿ���ĳ�����������Ƿ���key
        bool has(int index);

        bool has(const char *key);

        bool has(const string &key);

        void remove(int index);

        void remove(const char *key);

        void remove(const string &key);

        //json���л�
        string str() const;

        //json�ַ�������(�����л�)
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
