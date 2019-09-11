#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAME 0

typedef struct node_t
{
  int value, size, height;
  
  struct node_t *left, *right;

} node_t;

node_t * node_create(int value);
void node_destroy(node_t * cur);

node_t * tree_add_node(node_t * cur, int index, int value);
node_t * tree_delete_node(node_t * cur, int index);
int tree_value_at(node_t * cur, int index);

node_t * tree_meld(node_t * left, node_t * right);
node_t * tree_balance(node_t * cur);
node_t * tree_rotate_left(node_t * cur);
node_t * tree_rotate_right(node_t * cur);

int tree_size(node_t * cur);
int tree_height(node_t * cur);

// Update the height and size information based on that information in the subtree.
void update_values(node_t * cur);

void tree_print(node_t * cur);