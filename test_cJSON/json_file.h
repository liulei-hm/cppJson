//
// Created by liulei on 2023/3/28.
//

#ifndef CPPTHING_JSON_FILE_H
#define CPPTHING_JSON_FILE_H

#include "lib/cJSON.h"
#include <errno.h>
#include <string.h>
void wirte_file(cJSON *root);
char *open_file();
#endif //CPPTHING_JSON_FILE_H
