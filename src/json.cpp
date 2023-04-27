//
// Created by liulei on 2023/3/28.
//

#include "../include/json.h"
#include "../include/paser.h"
#include <sstream>
#include "log.h"
using namespace liulei;


/* ���캯��
 * 1����������int��double��bool��string���캯��
 * 2������ָ�����͵Ĺ��캯��������Json::json_int
 * 3���������캯��  ǳ����
 * 4���ƶ����캯��
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
    LOG_INFO("��������");
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
            //ǳ����
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
    LOG_INFO("�ƶ�����");
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

/* ����������
 * 1���ƶ���ֵ������
 * 2��������ֵ������
 * 3������ת����������Json::operator bool()���� bool b = j1ʱ������
 * 4�����Ʋ��������أ�bool b = j1.asbool()��������Ͳ�ƥ�䱨��
 * 5������ȡ�±������ []
 * 6������mapȡ�±� []
 * 7��json����Ƚ� ==  !=
 */
Json &Json::operator=(Json &&other) noexcept {
    LOG_INFO("�ƶ���ֵ");
    //�ƶ���ֵע������
    //1�����ܺ�ԭ�����ַһ�£��ᵼ������ɾ�����¶�ʧ������ Json l1; l1 = l1;
    //2����ֹ�ڴ�й©���ͷ�ԭָ��ָ����ڴ�ռ䡣��Ϊʹ���������壬һ��Ҫ���ж�������delete
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
    LOG_INFO("������ֵ");
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

//c++�е�����ת��operator - ����
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
    //return m_value.m_array[index]; //ָ��vector��ָ�����Բ���ͨ��[]��ȡԪ�ص�ֵ
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
            //����Ƕ�ף�ֻ�ж�ָ���Ƿ����
            return m_value.m_array == other.m_value.m_array;
        case json_object:
            //����Ƕ�ף�ֻ�ж�ָ���Ƿ����
            return m_value.m_object == other.m_value.m_object;
    }
    return false;
}

bool Json::operator!=(const Json &other) {
    return !(*(this)==other);
}


/* ����׷��
 */
void Json::append(const Json &other) {
    if(m_type != json_array){
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(other);
}

/* �ж��Ƿ����
 * 1�����������Ƿ����
 * 2������map��key�Ƿ����
 * 3��ɾ������
 * 4��ɾ��key
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

/* json�������
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
            m_value.m_string = nullptr; //�Ƿ���Ҫ�ÿ�
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


/* json����ת�ַ���(���л�)
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
                //object��key��first��value��second
                ss << '\"' << it->first << '\"' << ':' << it->second.str();
            }
            ss << '}';
            break;
    }
    return ss.str();
}


/* json�������(�����л�)
 */
void Json::parse(const string &str) {
    Parser p;
    p.load(str);
    *this = p.parse();
}





