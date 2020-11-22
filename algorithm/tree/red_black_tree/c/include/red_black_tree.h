#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
#include "node.h"
#include <stdbool.h>

bool insert(struct Node **root, int val);
bool delete(struct Node **root, int val);

#endif
