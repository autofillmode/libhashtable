#include "structs.h"

#ifndef COMPARE_H
#define COMPARE_H

int compare_key(HT_Node *, HT_TYPE, void *);
HT_TYPE infer_type(void *value);

#endif