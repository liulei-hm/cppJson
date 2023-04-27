//
// Created by liulei on 2023/3/28.
//
#include "json_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char *FILE_NAME = "test.json";
void wirte_file(cJSON *root){
    if(root==NULL) return;
    // 打开文件
    FILE *file = NULL;

    file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("open fail errno = %d,reason = %s \n", errno, strerror(errno));
        // 释放指针内存
        cJSON_Delete(root);
        return;
    }
    char *cjValue = cJSON_Print(root);
    // 写入文件
    //int ret = fwrite(cjValue, sizeof(char), strlen(cjValue), file);
    int ret = fputs(cjValue, file);
    if (ret == EOF) {
        printf("写入文件失败！");
    }
    fclose(file);
    free(cjValue);
}

char *open_file(){
    // 打开文件
    FILE *file = NULL;
    file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("open fail errno = %d,reason = %s \n", errno, strerror(errno));
        return NULL;
    }
    // 获得文件大小
    struct stat statbuf;
    stat(FILE_NAME, &statbuf);
    int fileSize = statbuf.st_size;
    printf("文件大小：%d\n", fileSize);

    // 分配符合文件大小的内存
    char *jsonStr = (char *)malloc(sizeof(char) * fileSize + 1);
    memset(jsonStr, 0, fileSize + 1);

    // 读取文件中的json字符串
    int size = fread(jsonStr, sizeof(char), fileSize, file);
    if (size == 0) {
        printf("open fail errno = %d,reason = %s \n", errno, strerror(errno));
        return NULL;
    }
    fclose(file);
    return jsonStr;
}