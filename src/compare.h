#include "structs.h"

#ifndef COMPARE_H
#define COMPARE_H

int compare_key(HT_Node *node, void *value);
HT_TYPE infer_type(void *value);

#endif