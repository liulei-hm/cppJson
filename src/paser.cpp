//
// Created by liulei on 2023/4/12.
//

#include "paser.h"

using namespace liulei;


/* 解析器构造函数
 */
Parser::Parser() : m_str(""),m_idx(0) {

}

/* 把要解析的序列化字符串存入成员保存
 */
void Parser::load(const string &str) {
    m_str = str; //保存要解析的串
    m_idx = 0;
}

/* 递归解析主体
 */
Json Parser::parse() {
    char ch = get_token();
    switch (ch) {
        case  'n':
            m_idx--;
            return parse_null();
        case 't':
        case 'f':
            m_idx--;
            return parse_bool();
        case '-':
        case '0' ... '9':
            m_idx--;
            return parse_number();
        case '"':
            return Json(parse_string());
        case '[':
            return  parse_array();
        case '{':
            return parse_object();
        default:
            break;
    }
    throw std::logic_error("unexpected_type");
    return nullptr;
}

Json Parser::parse_null() {
    if(m_str.compare(m_idx,4,"null")==0)
    {
        m_idx+=4;
        return Json();
    }
    throw std::logic_error("parse_null error");
}

Json Parser::parse_bool() {
    if(m_str.compare(m_idx,4,"true")==0)
    {
        m_idx += 4;
        return Json(true);
    }else if(m_str.compare(m_idx,5,"false")==0){
        m_idx += 5;
        return Json(false);
    }else{
        throw std::logic_error("parse_bool error");
    }
}

Json Parser::parse_number() {
    int pos = m_idx;
    if(m_str[m_idx] == '-')
    {
        m_idx++;
    }
    if(m_str[m_idx] < '0' || m_str[m_idx] > '9')
    {
        throw std::logic_error("parse number_1 error");
    }
    while(m_str[m_idx] >= '0' && m_str[m_idx] <= '9' && m_idx<m_str.size())
    {
        m_idx++;
    }

    if(m_str[m_idx] != '.')
    {
        int i = std::atoi(m_str.c_str()+pos);
        return  Json(i);
    }
    m_idx++;
    if(m_str[m_idx] < '0' || m_str[m_idx] > '9')
    {
        throw std::logic_error("parse number_3 error");
    }
    while(m_str[m_idx] >= '0' && m_str[m_idx] <= '9' && m_idx<m_str.size())
    {
        m_idx++;
    }
    double  f = std::atof(m_str.c_str()+pos);
    return Json(f);
}

string Parser::parse_string() {
    string out;
    while(1)
    {
        char ch = m_str[m_idx++];
        if(ch=='"')
        {
            break;
        }
        if(ch == '\\') //转义字符
        {
            //TODO:需要测试
            ch  = m_str[m_idx++];
            switch (ch) {
                case '\n':
                case '\r':
                case '\t':
                case '\b':
                case '\f':
                    out += ch;
                    break;
                case '"':
                    out += "\\\"";
                    break;
                case '\\':
                    out += "\\\\";
                    break;
                case 'u':
                    out += "\\u";
                    for(int i=0;i<4;i++)
                    {
                        out += m_str[m_idx++];
                    }
                    break;
                default:
                    throw std::logic_error("parse_string error");
            }
        }else{
            out += ch;
        }
    }
    return out;
}

Json Parser::parse_array() {
    Json arr(Json::json_array);
    char ch = get_token();
    if(ch == ']')
    {
        return arr;
    }
    m_idx--;
    while(true)
    {
        arr.append(parse());
        ch = get_token();
        if(ch == ']')
        {
            break;
        }
        if(ch != ',')
        {
            throw std::logic_error("parse_array error");
        }
        //m_idx++;
        //skip_space();
    }
    return arr;
}

Json Parser::parse_object() {
    Json obj(Json::json_object);
    char ch = get_token();
    if(ch == '}')
    {
        return obj;
    }
    m_idx--;
    while(1)
    {
        ch = get_token();
        if(ch != '"')
        {
            throw logic_error("parse_object_1 error");
        }
        string key = parse_string();
        ch = get_token();
        if(ch != ':')
        {
            throw std::logic_error("parse_object_2 error");
        }
        obj[key] = parse();
        ch = get_token();
        if(ch == '}'){
            break;
        }
        if(ch != ',')
        {
            throw std::logic_error("parse_object_3 error");
        }
        //m_idx++;
    }
    return obj;
}

/* 跳过空格
 */
void Parser::skip_space() {
    while(m_str[m_idx] == ' ' || m_str[m_idx] == '\n' \
    || m_str[m_idx] == '\r' || m_str[m_idx] == '\t')
    {
        m_idx++;
    }
}

/* 取token
 */
char Parser::get_token() {
    skip_space();
    return m_str[m_idx++];
}

