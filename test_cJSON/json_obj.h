//
// Created by liulei on 2023/3/28.
//

#ifndef CPPTHING_JSON_OBJ_H
#define CPPTHING_JSON_OBJ_H

#include "lib/cJSON.h"

void json_obj_print(cJSON *root);
cJSON *json_obj_create();
cJSON *json_obj_read();
void json_obj_parse(cJSON *read_root);
#endif //CPPTHING_JSON_OBJ_H
