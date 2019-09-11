  #include "fancy.h"
  
  int main(void)
  {
    //Declare variables
    int operations = 0, index = 0, value = 0;
    char * action;
    node_t * tree = NULL;
    
    //Open the file pointer
    FILE * ifp = fopen("fancy.txt", "r");
    
    //Scan file for amount of operations to perform onto the fancy array
    fscanf(ifp, "%d", &operations);

    //Loop through file for ever operation
    for (int c = 0; c < operations; c++)
    {
      //Scan the file for the action that is to be taken at what index
      fscanf(ifp, "%s %d", action, &index);
      
      //Check if the action is an insert
      if (strcmp(action, "insert") == SAME)
      {
        //scan the file for the value to be inserted
        fscanf(ifp, "%d", &value);
        //Insert the value at the index
        tree = tree_add_node(tree, index, value);
      }
      else if (strcmp(action, "delete") == SAME)
      {
        //Delete the value at the index
        tree = tree_delete_node(tree, index);
      }
      else if (strcmp(action, "valueat") == SAME)
      {
        //Print the value at the index
        printf("%d\n", tree_value_at(tree, index));
      }
      else
      {
        //If the action does not match any of those, then it was typed incorreclty
        printf("\nINVALID OPERATION\n");
        return 1;
      }
    }
    
    //Free memory allocated to pointers
    fclose(ifp);
    node_destroy(tree);
    
    //Successfully end program
    return 0;
  }
  
  
  
  //Returns a new node pointer with the expected values and pointers of a single node
  node_t * node_create(int value)
  {
    //Allocate memory for the node
    node_t * new_node = malloc(sizeof(node_t));
    
    //Initialize values and pointers
    new_node->value = value;
    new_node->size = 1;
    new_node->height = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    
    //Return the new node
    return new_node;
  }
  
  
  
  //Destroys nodes of a tree through post-order traversal
  void node_destroy(node_t * cur)
  {
    //Check if there exists a current left subtree
    if (cur->left != NULL)
    {
      //Traverse the current left subtree
      node_destroy(cur->left);
    }
    
    //Check if there exists a current right subtree
    if (cur->right != NULL)
    {
      //Traverse the current right subtree
      node_destroy(cur->right);
    }
    
    //Free the memory allocated to the current node pointer
    free(cur);
  }
  
  
  
  //Adds a node pointer to the tree in the spot that coresponds with its index in the fancy array
  node_t * tree_add_node(node_t * cur, int index, int value)
  {
    //Check if the current node is NULL
    if (cur == NULL)
    {
      //Create and return a new node pointer with the passed-in value
      node_t * new_node = node_create(value);
      return new_node;
    }

    //Check if the index is in the left subtree
    if (tree_size(cur->left) >= index)
    {
      //Recurisvely call this function and set it equal to the current left subtree
      cur->left = tree_add_node(cur->left, index, value);
    }
    else
    {
      //Recurisvely call this function and set it equal to the current left subtree
      //Change the index to not include the indices in the current left subtree
      cur->right = tree_add_node(cur->right, index - (tree_size(cur->left) + 1), value);
    }
    
    //Balance the current tree
    cur = tree_balance(cur);
    
    //Update the values of the node pointer
    update_values(cur);
    
    //Return the current subtree
    return cur;
  }
  
  
  
  //Deletes and frees the memory a node from the fancy array at a specified index
  node_t * tree_delete_node(node_t * cur, int index)
  {
    //Check if the current node is NULL
    if (tree_size(cur->left) == index)
    {
      //Save the current node pointer temporarily
      node_t * to_delete = cur;
      
      //Meld the left and right subtrees and save the new root
      node_t * new_root = tree_meld(cur->left, cur->right);
      
      //Free the memory allocate to the deleted node pointer
      free(to_delete);
      
      //Return the new root of the subtree
      return new_root;
    }
    
    //Check if the index is in the left subtree
    if (tree_size(cur->left) > index)
    {
      //Recurisvely call this function and set it equal to the current left subtree
      cur->left = tree_delete_node(cur->left, index);
    }
    else
    {
      //Recurisvely call this function and set it equal to the current left subtree
      //Change the index to not include the indices in the current left subtree
      cur->right = tree_delete_node(cur->right, index - (tree_size(cur->left) + 1));
    }
    
    //Balance the current tree
    cur = tree_balance(cur);
    
    //Update the values of the node pointer
    update_values(cur);
    
    //Return the current subtree
    return cur;
  }
  
  
  
  //Returns the value at an index of the fancy array
  int tree_value_at(node_t * cur, int index)
  {
    //Initalize a value integer
    int value = 0;
    
    //Check if the current left subtree's size is equal to the index
    if (tree_size(cur->left) == index)
    {
      //Print the value at the current node pointer
      return cur->value;
    }
    else if (tree_size(cur->left) > index)
    {
      //Recurisvely call this function and set it equal to the current left subtree
      value = tree_value_at(cur->left, index);
    }
    else
    {
      //Recurisvely call this function and set it equal to the current left subtree
      //Change the index to not include the indices in the current left subtree
      value = tree_value_at(cur->right, index - (tree_size(cur->left) + 1));
    }
    
    //Return the value at the index
    return value;
  }
  
  
  
  //Melds two subtrees together and returns their product
  node_t * tree_meld(node_t * left, node_t * right)
  {
    //Check if the left subtree is NULL
    if (left == NULL)
    {
      //Reurn the right subtree so that it can be melded onto the left
      return right;
    }
    
    //Meld the right tree onto the most right-side node of the left subtree
    left->right = tree_meld(left->right, right);

    //Return the melded tree
    return left;
  }
  
  
  
  //Balances the tree so that the left and right subtree's are as similar as possible
  node_t * tree_balance(node_t * cur)
  {
    //Loop until the left subtree's height is greater than or equal to the right subtree's height
    while (tree_height(cur->left) < tree_height(cur->right))
    {
      //Rotate the tree to the left
      cur = tree_rotate_left(cur);
    }
    
    //Loop until the right subtree's height is greater than or equal to the left subtree's height
    while (tree_height(cur->right) < tree_height(cur->left))
    {
      //Rotate the tree to the right
      cur = tree_rotate_right(cur);
    }
    
    //Return the current balanced tree
    return cur;
  }
  
  
  
  //Rotates the tree to the left to make it more balanced with same in-order traversal
  node_t * tree_rotate_left(node_t * cur)
  {
    //Check if the current node pointer is NULL
    if(cur == NULL)
    {
      //Return the unchanged tree
      return cur;
    }

    //Save a place-holding node pointer as the current right subtree
    node_t * pivot = cur->right;
    
    //Make the new root's left subtree be the right subtree of the current node
    cur->right = pivot->left;
    
    //Make the current node be the new root's left subtree
    pivot->left = cur;
    
    //Update the values of the nodes that changed values
    update_values(cur);
    update_values(pivot);
    
    //Return the new root of the current subtree
    return pivot;
  }
  
  
  
  //Rotates the tree to the right to make it more balanced with same in-order traversal
  node_t * tree_rotate_right(node_t * cur)
  {
    //Check if the current node pointer is NULL
    if (cur == NULL)
    {
      //Retrun the unchanged tree
      return cur;
    }

    //Save a place-holding node pointer as the current left subtree
    node_t * pivot = cur->left;
    
    //Make the new root's right subtree be the left subtree of the current node
    cur->left = pivot->right;
    
    //Make the current node be the new root's right subtree
    pivot->right = cur;
    
    //Update the values of the nodes that changed values
    update_values(cur);
    update_values(pivot);
    
    //Return the new root of the current subtree
    return pivot;
  }
  
  
  
  //Returns the size of a tree without a segmentation fault
  int tree_size(node_t * cur)
  {
    //Declare a size integer, NULL nodes have 0 size
    int size = 0;
    
    //Check if the current node is not NULL
    if (cur != NULL)
    {
      //Save the size of the current subtree
      size = cur->size;
    }
    
    //Return the size of the current tree
    return size;
  }
  
  
  
  //Retruns the height of a tree without a segmentation fault
  int tree_height(node_t * cur)
  {
    //Declare a height integer, NULL nodes have -1 height
    int height = -1;
    
    //Check if the current node is not NULL
    if (cur != NULL)
    {
      //Save the height of the current subtree
      height = cur->height;
    }
    
    //Return the size of the current tree
    return height;
  }
  
  
  
  //Updates the height and size information based on that information in the subtree
  void update_values(node_t * cur)
  {    
    //Add the sizes of the left and right subtrees together and set it to the current size, including itself
    cur->size = tree_size(cur->left) + tree_size(cur->right) + 1;

    //Check which subtree's height is larger
    if (tree_height(cur->left) >= tree_height(cur->right))
    {
      //Update the height to include itself and the height of its left subtree
      cur->height = tree_height(cur->left) + 1;
    }
    else
    {
      //Update the height to include itself and the height of its right subtree
      cur->height = tree_height(cur->right) + 1;
    }
  }