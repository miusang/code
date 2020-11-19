#ifndef _BALANCED_BINARY_TREE_H_
#define _BALANCED_BINARY_TREE_H_
#include "node.h"
#include <stdbool.h>
#include <stddef.h>

bool insert(struct Node **root, int val);
bool delete(struct Node **root, int val);

#endif
