//
// Created by liulei on 2023/3/28.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "json_obj.h"
#include "json_file.h"

void json_obj_print(cJSON *root){
    if(root==NULL) return;
    // 打印控制台查看
    char *cPrint = cJSON_Print(root);
    char *cPrintUnformatted = cJSON_PrintUnformatted(root);
    printf("cJSON_Print：%s\n", cPrint);		// cJSON_Print：有做格式调整
    printf("cJSON_PrintUnformatted：%s\n", cPrintUnformatted);	// cJSON_PrintUnformatted：没有做格式调整
    // 返回的字符串指针需要自己释放
    free(cPrint);
    free(cPrintUnformatted);
}

cJSON *json_obj_create(){
    // 定义对象 { }
    cJSON *interest = cJSON_CreateObject();
    // 插入元素，对当值是字符串时，需要使用函数cJSON_CreateString()创建
    cJSON_AddItemToObject(interest, "basketball", cJSON_CreateString("篮球"));
    cJSON_AddItemToObject(interest, "badminton", cJSON_CreateString("羽毛球"));
    cJSON_AddItemToObject(interest, "pingpang", cJSON_CreateString("乒乓球"));
    // 定义 [ ] 数组
    cJSON *color = cJSON_CreateArray();
    // 往数组中添加元素
    cJSON_AddItemToArray(color, cJSON_CreateString("black"));
    cJSON_AddItemToArray(color, cJSON_CreateString("white"));
    // 定义对象 { }
    cJSON *serialOne = cJSON_CreateObject();
    cJSON_AddItemToObject(serialOne, "language", cJSON_CreateString("汉语"));
    cJSON_AddItemToObject(serialOne, "grade", cJSON_CreateNumber(10));

    cJSON *serialTwo = cJSON_CreateObject();
    cJSON_AddItemToObject(serialTwo, "language", cJSON_CreateString("英语"));
    cJSON_AddItemToObject(serialTwo, "grade", cJSON_CreateNumber(6));

    // 定义对象 { }
    cJSON *languages = cJSON_CreateObject();
    cJSON_AddItemToObject(languages, "serialOne", serialOne);
    cJSON_AddItemToObject(languages, "serialTwo", serialTwo);
    // 定义 [ ] 数组
    cJSON *education1 = cJSON_CreateArray();
    cJSON_AddItemToArray(education1, cJSON_CreateString("小学"));
    cJSON_AddItemToArray(education1, cJSON_CreateString("初中"));

    cJSON *education2 = cJSON_CreateArray();
    cJSON_AddItemToArray(education2, cJSON_CreateString("高中"));
    cJSON_AddItemToArray(education2, cJSON_CreateString("大学"));

    // 定义 [ ] 数组
    cJSON *education = cJSON_CreateArray();
    cJSON_AddItemToArray(education, education1);
    cJSON_AddItemToArray(education, education2);


    // 定义 { } 对象
    cJSON *likeObject1 = cJSON_CreateObject();
    cJSON_AddItemToObject(likeObject1, "game", cJSON_CreateString("马里奥"));
    cJSON_AddItemToObject(likeObject1, "price", cJSON_CreateNumber(66.6));    // 当值是数字时，需要使用函数cJSON_CreateNumber()创建
    //cJSON_AddNumberToObject(likeObject1, "price", 66.6);  // 或者这样写

    cJSON *likeObject2 = cJSON_CreateObject();
    cJSON_AddItemToObject(likeObject2, "game", cJSON_CreateString("魂斗罗"));
    cJSON_AddItemToObject(likeObject2, "price", cJSON_CreateNumber(77.7));

    // 定义 [ ] 数组
    cJSON *like = cJSON_CreateArray();
    // 往数组中添加元素
    cJSON_AddItemToArray(like, likeObject1);
    cJSON_AddItemToArray(like, likeObject2);

    // 创建跟对象
    cJSON *root = cJSON_CreateObject();
    // 将子项插入根项中
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("小明"));  // "name":  "小明"
    cJSON_AddItemToObject(root, "age", cJSON_CreateNumber(23));      // "age":  23
    cJSON_AddItemToObject(root, "interest", interest);
    cJSON_AddItemToObject(root, "color", color);
    cJSON_AddItemToObject(root, "like", like);
    cJSON_AddItemToObject(root, "education", education);
    cJSON_AddItemToObject(root, "languages", languages);
    cJSON_AddItemToObject(root, "vip", cJSON_CreateTrue());  // "vip":  true    插入布尔类型数据需要使用cJSON_CreateBool函数
    cJSON_AddItemToObject(root, "address", cJSON_CreateNull());  // "address":  null  插入NULL值需要使用cJSON_CreateNull函数
    //cJSON_AddTrueToObject(root, "vip");
    //cJSON_AddNullToObject(root, "address");  // 或者这样写也是可以的
    return root;
}

cJSON *json_obj_read(){
    // 将读取到的json字符串转换成json变量指针
    char *jsonStr = open_file();
    if(!jsonStr) return NULL;
    cJSON *read_root = cJSON_Parse(jsonStr);
    if (!read_root) {
        const char *err = cJSON_GetErrorPtr();
        printf("Error before: [%s]", err);
        free((void *)err);
        free(jsonStr);
        return NULL;
    }
}


static void parse_key(cJSON *root){
    cJSON *item = NULL;
    char *v_str = NULL;
    int v_int = 0;
    // 解析："name":	"小明",
    item = cJSON_GetObjectItem(root, "name");
    if (item != NULL) {
        /* 写法一：*/
        // 判断是不是字符串类型
        //if (item->type == cJSON_String) {
        //	v_str = cJSON_Print(item);		// 通过函数获取值
        //	printf("name = %s", v_str);
        //	free(v_str);					// 通过函数返回的指针需要自行free，否则会导致内存泄漏
        //	v_str = NULL;
        //}
        /* 写法二： */
        // 判断是不是字符串类型
        if (item->type == cJSON_String) {
            v_str = item->valuestring;		// 此赋值是浅拷贝，不需要现在释放内存
            printf("name = %s\n", v_str);
        }
    }
    // 解析："age":	"23",
    item = cJSON_GetObjectItem(root, "age");
    if (item != NULL) {	// 合法性检查
        if (item->type == cJSON_Number) {		// 判断是不是数字
            v_int = item->valueint;			// 获取值
            printf("age = %d\n", v_int);
        }
    }
    // 解析："vip":	true,
    item = cJSON_GetObjectItem(root, "vip");
    if (item != NULL) {
        if (item->type == cJSON_True || item->type == cJSON_False) {
            v_str = cJSON_Print(item);		// 由于bool类型结构体中没有给出，所以使用字符串代替
            printf("vip = %s\n", v_str);
            free(v_str);
            v_str = NULL;
        }
    }


// 解析："address":	null
    item = cJSON_GetObjectItem(root, "address");
    if (item != NULL && item->type == cJSON_NULL) {
        v_str = cJSON_Print(item);		// 由于NULL类型结构体中没有给出，所以使用字符串代替
        printf("address = %s\n", v_str);
        free(v_str);
        v_str = NULL;
    }
}
static void parse_object(cJSON *root)
{
    cJSON *item = NULL;
    char *v_str = NULL;
    /*************** 方式一 ***************/
    item = cJSON_GetObjectItem(root, "interest");		// 获取object对象名
    if (item != NULL) {
        cJSON *val = NULL;

        val = cJSON_GetObjectItem(item, "basketball");	// 根据object对象名获得里面的basketball数据
        if (val != NULL && val->type == cJSON_String) {
            v_str = val->valuestring;
            printf("basketball = %s\n", v_str);
        }

        val = cJSON_GetObjectItem(item, "badminton");	// 根据object对象名获得里面的badminton数据
        if (val != NULL && val->type == cJSON_String) {
            v_str = val->valuestring;
            printf("badminton = %s\n", v_str);
        }
    }

    /*************** 方式二 ***************/
    item = cJSON_GetObjectItem(root, "interest");
    if (item != NULL) {
        cJSON *obj = item->child;	// 获得 "basketball":	"篮球"

        while (obj) {
            if (obj->type == cJSON_String) {
                char *v_str = obj->valuestring;
                printf("%s = %s\n", obj->string, v_str);	// 可以通过string获得键
            }
            // 获取下一个元素
            obj = obj->next;
        }
    }
}

static void parse_array(cJSON *root)
{
    cJSON *item = NULL;
    char *v_str = NULL;
    /*************** 方式一 ***************/
    item = cJSON_GetObjectItem(root, "color");
    if (item != NULL) {
        int size = cJSON_GetArraySize(item);	// 获得数组个数

        for (int i = 0; i < size; i++) {
            cJSON *arr = cJSON_GetArrayItem(item, i);	// 根据索引获得数组中的值

            if (arr != NULL && arr->type == cJSON_String) {
                v_str = arr->valuestring;
                printf("color = %s\n", v_str);
            }
        }
    }
    /*************** 方式二 ***************/
    item = cJSON_GetObjectItem(root, "color");
    if (item != NULL) {
        cJSON *arr = item->child;	// 获得 "black"

        while (arr) {
            if (arr->type == cJSON_String) {
                char *v_str = arr->valuestring;
                printf("color = %s\n", v_str);
            }
            // 获取下一个元素
            arr = arr->next;
        }
    }
}

static void parse_object_in_array(cJSON *root)
{
    cJSON *item = NULL;
    char *v_str = NULL;
    double v_double = 0.0;
    /*************** 方式一 ***************/
    item = cJSON_GetObjectItem(root, "like");
    if (item != NULL) {
        int size = cJSON_GetArraySize(item);	// 获取的数组大小

        for (int i = 0; i < size; i++) {
            cJSON *obj = cJSON_GetArrayItem(item, i);		// 获取的数组里的obj
            cJSON *val = NULL;

            if (obj != NULL && obj->type == cJSON_Object) {	// 判断数字内的元素是不是obj类型
                val = cJSON_GetObjectItem(obj, "game");		// 获得obj里的值

                if (val != NULL && val->type == cJSON_String) {
                    v_str = val->valuestring;
                    printf("game = %s\n", v_str);
                }

                val = cJSON_GetObjectItem(obj, "price");
                if (val != NULL && val->type == cJSON_Number) {
                    v_double = val->valuedouble;
                    printf("price = %.2f\n", v_double);
                }
            }
        }
    }


    /*************** 方式二 ***************/
    item = cJSON_GetObjectItem(root, "like");
    if (item != NULL) {
        cJSON *obj = item->child;	// 获得 { "game": "马里奥", "price": 66.6 }

        while (obj) {
            if (obj->type == cJSON_Object) {

                cJSON *objValue = obj->child;	// 获得 "game": "马里奥"
                while (objValue) {

                    // 再通过类型去区分
                    if (objValue->type == cJSON_String) {
                        char *v_str = objValue->valuestring;
                        printf("%s = %s\n", objValue->string, v_str);

                    } else if (objValue->type == cJSON_Number) {
                        double v_double = objValue->valuedouble;
                        printf("%s = %.2f\n", objValue->string, v_double);
                    }
                    // 获取下一个元素
                    objValue = objValue->next;
                }
            }
            // 获取下一组元素
            obj = obj->next;
        }
    }
}

static void parse_array_in_array(cJSON *root)
{
    cJSON *item = NULL;
    char *v_str = NULL;
    double v_double = 0.0;
    /*************** 方式一 ***************/
    item = cJSON_GetObjectItem(root, "education");
    if (item != NULL) {
        int size = cJSON_GetArraySize(item);	// 获取的数组大小

        for (int i = 0; i < size; i++) {
            cJSON *arr = cJSON_GetArrayItem(item, i);		// 解析获得	[ "小学", "初中" ]

            if (arr != NULL && arr->type == cJSON_Array) {
                int arrSize = cJSON_GetArraySize(arr);

                for (int j = 0; j < arrSize; j++) {
                    cJSON *arr2 = cJSON_GetArrayItem(arr, j);	// 再进一步解析就可以得到数组里面的元素了

                    if (arr2 != NULL && arr2->type == cJSON_String) {
                        v_str = arr2->valuestring;
                        printf("education = %s\n", v_str);
                    }
                }
            }
        }
    }

    /*************** 方式二 ***************/
    item = cJSON_GetObjectItem(root, "education");
    if (item != NULL) {
        cJSON *arr = item->child;	// 获得 [ "小学", "初中" ]

        while (arr) {
            if (arr->type == cJSON_Array) {

                cJSON *arrValue = arr->child;	// 获得 "小学"
                while (arrValue) {
                    if (arrValue->type == cJSON_String) {
                        char *v_str = arrValue->valuestring;
                        printf("education = %s\n", v_str);
                    }
                    arrValue = arrValue->next;	// 获取下一个元素
                }
            }
            // 获取下一组
            arr = arr->next;
        }
    }
}

static void parse_object_in_object(cJSON *root)
{
    cJSON *item = NULL;
    char *v_str = NULL;
    double v_double = 0.0;
    int v_int = 0;
    /*************** 方式一 ***************/
    char *arrStr[] = { "serialOne", "serialTwo" };		// 可以提前定义需要解析的对象键，这样就可以使用for循环进行解析了

    item = cJSON_GetObjectItem(root, "languages");
    if (item != NULL) {
        cJSON *val = NULL;
        int size = sizeof(arrStr) / sizeof(char *);

        // 通过遍历指针数组，获得每个对象的键，在进行解析操作（如果不使用for循环解析，那就老老实实的写代码将全部个数解析完毕）
        for (int i = 0; i < size; i++) {
            cJSON *obj1 = cJSON_GetObjectItem(item, arrStr[i]);

            if (obj1 != NULL && obj1->type == cJSON_Object) {

                val = cJSON_GetObjectItem(obj1, "language");
                if (val != NULL && val->type == cJSON_String) {
                    v_str = val->valuestring;
                    printf("language = %s\n", v_str);
                }

                val = cJSON_GetObjectItem(obj1, "grade");
                if (val != NULL && val->type == cJSON_Number) {
                    v_int = val->valueint;
                    printf("grade = %d\n", v_int);
                }
            }
        }
    }

    /*************** 方式二 ***************/
    // 在不知道键是什么的情况下 和 不知道有多少元素的情况下可用
    item = cJSON_GetObjectItem(root, "languages");
    if (item != NULL) {
        // 获取到languages里的第一个子元素
        cJSON *obj = item->child;	// 也就是："serialOne": { "language": "汉语", "grade": 10 }

        while (obj) {
            if (obj->type == cJSON_Object) {

                // 获取到子元素的子元素
                cJSON *value = obj->child;	// 也就是：{ "language": "汉语", "grade": 10 }

                while (value) {
                    if (value->type == cJSON_String) {
                        printf("%s = %s\n", value->string, value->valuestring);

                    } else if (value->type == cJSON_Number) {
                        printf("%s = %d\n", value->string, value->valueint);
                    }
                    // 通过next可以自由获取里面的元素了
                    value = value->next;
                }
            }

            // 获得下一组子元素
            obj = obj->next;
        }
    }
}


void json_obj_parse(cJSON *read_root){
    if(read_root==NULL) return;

    bool v_bool = false;
    parse_key(read_root);
    parse_object(read_root);
    parse_array(read_root);
    parse_object_in_array(read_root);
    parse_array_in_array(read_root);
    parse_object_in_object(read_root);
}