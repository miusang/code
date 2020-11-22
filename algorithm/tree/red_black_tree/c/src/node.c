#include "node.h"
#include <stddef.h>

enum Color get_color(struct Node *node) {
    if (node == NULL) {
        return black;
    }
    return node->color;
}
