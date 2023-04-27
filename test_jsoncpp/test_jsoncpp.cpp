//
// Created by liulei on 2023/3/28.
//
#include "lib/myjson.h"
#include <iostream>
#include <fstream>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

using namespace std;

int createjson()
{
    Json::Value root;
    Json::Value language;
    Json::Value mail;
    Json::StyledWriter writer;
    // Json::FastWriter writer;

    root["Name"] = "pikashu";
    root["Age"] = 18;

    language[0] = "C++";
    language[1] = "Python";
    root["Language"] = language;

    mail["QQ"] = "789123456@qq.com";
    mail["Google"] = "789123456@gmail.com";
    root["E-mail"] = mail;

    string json_file = writer.write(root);

    ofstream ofs;
    ofs.open("test1.json");
    if (!ofs.is_open())
    {
        cout << "open file error." << endl;
        return -1;
    }
    ofs << json_file;
    ofs.close();
    return 0;
}

int readjson()
{
    Json::Reader reader;
    Json::Value root;
    Json::Value language;
    Json::Value mail;

    ifstream ifs;
    ifs.open("test1.json");
    if (!ifs.is_open())
    {
        cout << "open file error." << endl;
        return -1;
    }

    if (!reader.parse(ifs, root))
    {
        cout << "parse error" << endl;
        return -1;
    }

    string Name = root["Name"].asString();
    int Age = root["Age"].asInt();  // jsoncpp中获取int类型数据
    cout << "Name: " << Name << endl;
    cout << "Age: " << Age << endl;

    if (root["language"].isArray())
    {
        Json::Value array_l = root["language"];
        cout << "Language: ";
        for (int i = 0; i < array_l.size(); i++)
        {
            cout << array_l[i] << " ";
        }
        cout << endl;
    }

    cout << "Google: " << root["E-mail"].get("Google", "").asString() << endl;
    cout << "QQ: " << root["E-mail"].get("QQ", "").asString() << endl;

    return 1;
}
int main()
{
    createjson();
    readjson();
    return 0;
}
