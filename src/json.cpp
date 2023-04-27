//
// Created by liulei on 2023/3/28.
//

#include "../include/json.h"
#include "../include/paser.h"
#include <sstream>
#include "log.h"
using namespace liulei;


/* 构造函数
 * 1、基本类型int、double、bool、string构造函数
 * 2、根据指定类型的构造函数，传入Json::json_int
 * 3、拷贝构造函数  浅拷贝
 * 4、移动构造函数
 */
Json::Json():m_type(json_null) {

}

Json::Json(int value) : m_type(json_int){
    m_value.m_int = value;
}
Json::Json(double value) : m_type(json_double){
    m_value.m_double = value;
}
Json::Json(bool value) : m_type(json_bool){
    m_value.m_bool = value;
}

Json::Json(const char *value) : m_type(json_string){
    m_value.m_string = new string(value);
}

Json::Json(const string &value) : m_type(json_string){
    m_value.m_string = new string(value);
}

Json::Json(Type type) : m_type(type){
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = new string("");
            break;
        case json_array:
            m_value.m_array = new std::vector<Json>();
            break;
        case json_object:
            m_value.m_object = new std::map<string,Json>();
            break;
        default:
            break;
    }
}

Json::Json(const Json &other){
    LOG_INFO("拷贝构造");
    m_type = other.m_type;
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            //浅拷贝
            m_value.m_string = other.m_value.m_string;
            break;
        case json_array:
            m_value.m_array = other.m_value.m_array;
            break;
        case json_object:
            m_value.m_object = other.m_value.m_object;
            break;
        default:
            break;
    }
}

Json::Json(Json &&other) {
    LOG_INFO("移动构造");
    m_type = other.m_type;
    other.m_type = json_null;
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            m_value.m_string = other.m_value.m_string;
            other.m_value.m_string = nullptr;
            break;
        case json_array:
            m_value.m_array = other.m_value.m_array;
            other.m_value.m_array = nullptr;
            break;
        case json_object:
            m_value.m_object = other.m_value.m_object;
            other.m_value.m_object = nullptr;
            break;
        default:
            break;
    }

}

/* 操作符重载
 * 1、移动赋值操作符
 * 2、拷贝赋值操作符
 * 3、类型转换操作符，Json::operator bool()，当 bool b = j1时会重载
 * 4、类似操作符重载，bool b = j1.asbool()，如果类型不匹配报错
 * 5、数组取下标操作符 []
 * 6、对象map取下标 []
 * 7、json对象比较 ==  !=
 */
Json &Json::operator=(Json &&other) noexcept {
    LOG_INFO("移动赋值");
    //移动赋值注意两点
    //1、不能和原对象地址一致，会导致数据删除导致丢失，例如 Json l1; l1 = l1;
    //2、防止内存泄漏，释放原指针指向的内存空间。因为使用了联合体，一定要先判断类型再delete
    if(this!=&other)
    {
        switch (other.m_type) {
            case json_null:
                break;
            case json_bool:
                m_value.m_bool = other.m_value.m_bool;
                break;
            case json_int:
                m_value.m_int = other.m_value.m_int;
                break;
            case json_double:
                m_value.m_double = other.m_value.m_double;
                break;
            case json_string:
                if(m_type==json_string)
                {
                    delete m_value.m_string;
                }
                m_value.m_string = other.m_value.m_string;
                other.m_value.m_string = nullptr;
                break;
            case json_array:
                if(m_type==json_array)
                {
                    delete m_value.m_array;
                }
                m_value.m_array = other.m_value.m_array;
                other.m_value.m_array = nullptr;
                break;
            case json_object:
                if(m_type==json_object)
                {
                    delete m_value.m_object;
                }
                m_value.m_object = other.m_value.m_object;
                other.m_value.m_object = nullptr;
                break;
            default:
                break;
        }
        m_type = other.m_type;
        other.m_type = json_null;
    }
    return *this;
}

Json &Json::operator=(Json &other) {
    LOG_INFO("拷贝赋值");
    m_type = other.m_type;
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            m_value.m_string = other.m_value.m_string;
            break;
        case json_array:
            m_value.m_array = other.m_value.m_array;
            break;
        case json_object:
            m_value.m_object = other.m_value.m_object;
            break;
        default:
            break;
    }
    return *this;
}

//c++中的类型转换operator - 简书
//https://www.jianshu.com/p/f301f72d3ab0
Json::operator bool() {
    if(m_type!=json_bool){
        throw logic_error("type error,not bool value");
    }
    return m_value.m_bool;
}
Json::operator int() {
    if(m_type!=json_int){
        throw logic_error("type error,not int value");
    }
    return m_value.m_int;
}
Json::operator double() {
    if(m_type!=json_double){
        throw logic_error("type error,not double value");
    }
    return m_value.m_double;
}
Json::operator string() {
    if(m_type!=json_string){
        throw logic_error("type error,not string value");
    }
    return *(m_value.m_string);
}

bool Json::asBool() const {
    if(m_type != json_bool)
    {
        throw std::logic_error("type error,not bool value");
    }
    return m_value.m_bool;
}

int Json::asInt() const {
    if(m_type != json_int)
    {
        throw std::logic_error("type error,not int value");
    }
    return m_value.m_int;
}

double Json::asDouble() const {
    if(m_type != json_double)
    {
        throw std::logic_error("type error,not double value");
    }
    return m_value.m_double;
}

string Json::asString() const {
    if(m_type != json_string)
    {
        throw std::logic_error("type error,not string value");
    }
    return *(m_value.m_string);
}


Json &Json::operator[](int index) {
    if(m_type != json_array){
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    if(index<0){
        throw logic_error("array[] index < 0");
    }
    int size = (m_value.m_array)->size();
    if(index >= size)
    {
        for(int i=size;i<=index;i++)
        {
            (m_value.m_array)->push_back(new Json());
        }
    }
    //return (*m_value.m_array)[index];
    //return m_value.m_array[index]; //指向vector的指针所以不能通过[]获取元素的值
    return m_value.m_array->at(index);
}

Json &Json::operator[](const char *key) {
    if(m_type != json_object){
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<string,Json>();
    }
    string name(key);
    //return (*(this))[name];
    return (*m_value.m_object)[name];
}


Json &Json::operator[](const string &key) {
    if(m_type != json_object){
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<string,Json>();
    }
    return (*m_value.m_object)[key];;
}

bool Json::operator==(const Json &other) {
    if(m_type != other.m_type){
        return false;
    }
    switch (m_type) {
        case json_null:
            return true;
        case json_bool:
            return m_value.m_bool == other.m_value.m_bool;
        case json_int:
            return m_value.m_int == other.m_value.m_int;
        case json_double:
            return m_value.m_double == other.m_value.m_double;
        case json_string:
            return *(m_value.m_string) == *(other.m_value.m_string);
        case json_array:
            //含有嵌套，只判断指针是否相等
            return m_value.m_array == other.m_value.m_array;
        case json_object:
            //含有嵌套，只判断指针是否相等
            return m_value.m_object == other.m_value.m_object;
    }
    return false;
}

bool Json::operator!=(const Json &other) {
    return !(*(this)==other);
}


/* 数组追加
 */
void Json::append(const Json &other) {
    if(m_type != json_array){
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(other);
}

/* 判断是否存在
 * 1、数组索引是否存在
 * 2、对象map中key是否存在
 * 3、删除索引
 * 4、删除key
 */
bool Json::has(int index) {
    if(m_type!=json_array)
    {
        return false;
    }
    size_t size = (m_value.m_array)->size();
    return (index>=0 && index<size);
}

bool Json::has(const char *key) {
    string name(key);
    return has(name);
}

bool Json::has(const string &key) {
    if(m_type!=json_object)
    {
        return false;
    }
    return m_value.m_object->find(key)!=m_value.m_object->end();
}

void Json::remove(int index) {
    if(m_type!=json_array)
    {
        return;
    }
    if(has(index))
    {
        (*m_value.m_array)[index].clear();
        (m_value.m_array)->erase(m_value.m_array->begin() + index);
    }
}

void Json::remove(const char *key) {
    string name(key);
    remove(name);
}

void Json::remove(const string &key) {
    if(m_type!=json_object)
    {
        return;
    }
    if(has(key))
    {
        (*m_value.m_object)[key].clear();
        m_value.m_object->erase(key);
    }
}

/* json对象清空
 */
void Json::clear() {
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
        case json_string:
            delete m_value.m_string;
            m_value.m_string = nullptr; //是否需要置空
            break;
        case json_array:
            for(auto it=m_value.m_array->begin();it!=(m_value.m_array)->end();it++)
            {
                it->clear();
            }
            delete m_value.m_array;
            break;
        case json_object:
            for(auto it=m_value.m_object->begin();it!=(m_value.m_object)->end();it++)
            {
                (it->second).clear();
            }
            delete m_value.m_object;
            break;
    }
    m_type = json_null;
}


/* json对象转字符串(序列化)
 */
string Json::str() const {
    stringstream ss;
    switch (m_type) {
        case json_null:
            ss << "null";
            break;
        case json_bool:
            if(m_value.m_bool)
            {
                ss << "true";
            }else {
                ss << "false";
            }
            break;
        case json_int:
            ss << m_value.m_int;
            break;
        case json_double:
            ss << m_value.m_double;
            break;
        case json_string:
            ss << '\"' << *(m_value.m_string) << '\"';
            break;
        case json_array:
            ss << '[' ;
            for(auto it = m_value.m_array->begin();it!=m_value.m_array->end();it++){
                if(it != m_value.m_array->begin())
                {
                    ss << ',';
                }
                ss << it->str();
            }
            ss << ']';
            break;
        case json_object:
            ss << '{' ;
            for(auto it = m_value.m_object->begin();it!=m_value.m_object->end();it++){
                if(it != m_value.m_object->begin())
                {
                    ss << ',';
                }
                //object中key在first，value在second
                ss << '\"' << it->first << '\"' << ':' << it->second.str();
            }
            ss << '}';
            break;
    }
    return ss.str();
}


/* json对象解析(反序列化)
 */
void Json::parse(const string &str) {
    Parser p;
    p.load(str);
    *this = p.parse();
}





