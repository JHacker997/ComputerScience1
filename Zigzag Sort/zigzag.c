  //Declare header
  #include "zigzag.h"
  
  int main(void){
    //Create a queue of runs to save the sequence
    run_queue_t * sequence = run_queue_create();
    
    //Fill the queue of runs by reading in the text file and check if it was successful
    if (read_file(sequence))
    {
      //Reverse the direction for runsin the wrong direction
      reverse_runs(sequence);
  
      //Create a queue for the sorted integers of the sequence
      queue_t * sorted = queue_create();
      
      //Use O(n log n) merge sort to save the runs as a single sorted queue
      sorted = merge_sort(sequence, run_queue_size(sequence));
      
      //Print the sorted queue
      queue_print(sorted);
      
      //Free the memory allocated to the sorted queue
      queue_destroy(sorted);
    }
    
    //Free memory allocated to the queue of runs
    run_queue_destroy(sequence);
    
    //Successfully terminates the program
    return 0;
  }
  
  
  //STACK FUNCTIONS
  //
  //Creates an empty stack and returns it
  stack_t * stack_create(){
    //Allocate memory for a new stack
    stack_t * stack = malloc(sizeof(stack_t));
    
    //Point the top of the stack to NULL
    stack->top = NULL;
    
    //Return the new, empty stack
    return stack;
  }
  
  
  //Frees memory allocated to a stack
  void stack_destroy(stack_t * stack){
    //Loop so long that the stack is not empty
    while (!stack_is_empty(stack))
    {
      //Remove the top node from the stack, freeing its memory
      stack_pop(stack);
    }
    
    //Plug memory leak of the stack pointer
    free(stack);
  }
  
  
  //Puts new node on top of stack
  void stack_push(stack_t * stack, int data){
    //Allocate memory to a new node
    node_t * new_node = malloc(sizeof(node_t));
    
    //Save the value of the new node
    new_node->value = data;
    
    //Make the next node after the new node equal to the node on top of the stack
    new_node->next = stack->top;
    
    //Make the new node the new top of the stack
    stack->top = new_node;
    
  }
  
  
  //Removes top node from the stack and return its value
  int stack_pop(stack_t * stack){
    //Save the top node as a current node pointer to return its value after it is popped
    node_t * to_pop = stack->top;
    
    //Save the value of the top node so that it can be returned
    int data  = stack_peek(stack);
    
    //Make the second-to-top node the top node
    stack->top = stack->top->next;
    
    //Free the memory allocated to the popped node
    free(to_pop);
    
    //Return the value stored in the node that was just popped off the stack
    return data;
  }
  
  
  //Returns value of top-most element wthout removing it
  int stack_peek(stack_t * stack){
    //Return value of the top node
    return stack->top->value;    
  }
  
  
  //Checks if stack is empty
  int stack_is_empty(stack_t * stack){
    //If the top of the stack is pointed to NULL, then it is empty
    return stack->top == NULL;   
  }
  
  
  //Prints all the values in a stack to the screen
  void stack_print(stack_t * stack){//Does not work properly, erases the imported stack
    //Create a temporary node pointer to move across the stack
    node_t * current = stack->top;
    
    //Loop until the temporary node pointer is pointing to NULL
    while(current != NULL){
      //Print the current value of the run_node
      printf("%d ", current->value);
      
      //Move the current node pointer to the next node in the stack
      current = current->next;
    }
    
    //Print a new line after all the values in the stack are printed
    printf("\n");
    
    //Free memory allocated for the current run_node pointer
    free(current);
  }
  
  
  //QUEUE FUNCTIONS
  //
  //Creates an empty queue and returns it
  queue_t * queue_create(){
    //Allocate memory for the queue
    queue_t * queue = malloc(sizeof(queue_t));
    
    //Point the head and tail of the queue to NULL
    queue->head = NULL;
    queue->tail = NULL;
    
    //Return the new queue pointer
    return queue;
  }
  
  
  //Frees memory allocated to a queue
  void queue_destroy(queue_t * queue){
    //Loop until the queue is empty
    while (!queue_is_empty(queue))
    {
      //Dequeue the front node, freeing its memory
      queue_dequeue(queue);
    }
    
    //Free the memory allocated for the queue
    free(queue);
  }
  
  
  //Puts a node at the end of the queue
  void queue_enqueue(queue_t * queue, int data){
    //Allocate memory for the new node
    node_t * new_node = malloc(sizeof(node_t));
    
    //Save the value of the node and make it point to NULL
    new_node->value = data;
    new_node->next = NULL;
    
    //Check if the queue is empty
    if (queue_is_empty(queue))
    {
      //Make the head and tail of the queue point to the new node if the queue was empty
      queue->head = new_node;
      queue->tail = new_node;
    }
    else
    {
      //Make the last node in the queue and the tail of the queue point to the new node
      queue->tail->next = new_node;
      queue->tail = new_node;
    }
  }
  
  
  //Removes a node from the front of the queue and returns its value
  int queue_dequeue(queue_t * queue){
    //Check if the queue is empty
    if (queue_is_empty(queue)){
      //Inform that the queue is problematically empty
      printf("Queue is empty on dequeue!!\n\n");
      
      //Return a value that is out of range
      return 0;
    }
    
    //Save the front node so that it can be freed after being dequeued
    node_t * to_dequeue = queue->head;
    
    //Save the value of the node that is being dequeued
    int data = queue_peek(queue);
    
    //Make the second-from-front node the new head of the queue
    queue->head = to_dequeue->next;
    
    //Check if the queue is empty after the dequeue
    if (queue_is_empty(queue))
    {
      //Make the tail of the queue also equal to NULL
      queue->tail = NULL;
    }
    
    //Free memory allocated to the dequeued node
    free(to_dequeue);
    
    //Return the value of the dequeued node
    return data;
  }
  
  
  //Returns the value of the front of the queue
  int queue_peek(queue_t * queue){
    //Return the value of the front node
    return queue->head->value;
  }
  
  
  //Checks if the queue is empty
  int queue_is_empty(queue_t * queue){
    //If the head is pointed to NULL, then the tail also is => the queue is empty
    return queue->head == NULL;
  }
  
  
  //Returns the size of the queue
  int queue_size(queue_t * queue){
    //Create an integer to save the size of the queue
    int size = 0;
    
    //Create a temporary node pointer to move across the queue
    node_t * current = queue->head;
    
    //Loop until the temporary node pointer is pointing to NULL
    while(current != NULL){
      //Move the current node pointer to the next node in the queue
      current = current->next;
      
      //Add 1 to the size of the queue every time the node pointer is moved
      size++;
    }
    
    //Free memory allocated for the current run_node pointer
    free(current);
    
    //Return the size of the queue
    return size;
  }
  
  
  //Print all the values of the nodes in a queue to the screen
  void queue_print(queue_t * queue){
    //Create a temporary node pointer to move across the queue
    node_t * current = queue->head;
    
    //Loop until the temporary node pointer is pointing to NULL
    while(current != NULL){
      //Print the current value of the run_node
      printf("%d ", current->value);
      
      //Move the current node pointer to the next node in the queue
      current = current->next;
    }
    
    //Free memory allocated for the current run_node pointer
    free(current);
    
    //Print a new line after all the values in the queue are printed
    printf("\n");
  }
    
  
  //RUN_QUEUE FUNCTIONS
  //
  //Creates a new queue of runs
  run_queue_t * run_queue_create(){
    //Allocate memory for the queue of runs
    run_queue_t * run_queue = malloc(sizeof(run_queue_t));
    
    //Point the head and tail of the queue of runs to NULL
    run_queue->head = NULL;
    run_queue->tail = NULL;
    
    //Return the new queue of runs pointer
    return run_queue;
  }
  
  
  //Frees the memory allocated to the queue of runs
  void run_queue_destroy(run_queue_t * queue){
    //Loop until the queue of runs is empty
    while (!run_queue_is_empty(queue))
    {
      //Dequeue the front queue, freeing its memory
      run_queue_dequeue(queue);
    }
    
    //Free the memory allocated for the queue
    free(queue);
  }
  
  
  //Adds a new queue to the end of the queue of runs
  void run_queue_enqueue(run_queue_t * queue, queue_t * run){
    //Allocate memory for the new node
    run_node_t * new_node = malloc(sizeof(run_node_t));
    
    //Save the value of the node and make it point to NULL
    new_node->run = run;
    new_node->next = NULL;
    
    //Check if the queue is empty
    if (run_queue_is_empty(queue))
    {
      //Make the head and tail of the queue point to the new node if the queue was empty
      queue->head = new_node;
      queue->tail = new_node;
    }
    else
    {
      //Make the last node in the queue and the tail of the queue point to the new node
      queue->tail->next = new_node;
      queue->tail = new_node;
    }
  }
  
  
  //Removes the front queue from the queue of runs and returns the pointer to the removed queue
  queue_t * run_queue_dequeue(run_queue_t * queue){
    //Check if the queue is empty
    if (run_queue_is_empty(queue)){
      //Inform that the queue is problematically empty
      printf("Run_queue is empty on dequeue!!\n\n");
      
      //Return NULL when run_queue is empty
      return NULL;
    }
    
    //Save the front node so that it can be freed after being dequeued
    run_node_t * to_dequeue = queue->head;
    
    //Save the value of the node that is being dequeued
    queue_t * dequeued = queue->head->run;
    
    //Make the second-from-front node the new head of the queue
    queue->head = to_dequeue->next;
    
    //Check if the queue is empty after the dequeue
    if (run_queue_is_empty(queue))
    {
      //Make the tail of the queue also equal to NULL
      queue->tail = NULL;
    }
    
    //Free memory allocated to the dequeued node
    free(to_dequeue);
    
    //Return the value of the dequeued node
    return dequeued;
  }
  
  
  //Returns the pointer to the front queue of the queue of runs
  queue_t * run_queue_peek(run_queue_t * queue){
    //Return the run that the head of the run_queue points to
    return queue->head->run;
  }
  
  
  //Returns a value representing if the queue of runs is empty of queues
  int run_queue_is_empty(run_queue_t * queue){
    //If the head is pointed to NULL, then the tail also is => the queue is empty
    return queue->head == NULL;
  }
  
  
  //Returns the amount of runs in the queue of runs
  int run_queue_size(run_queue_t * queue){
    //Create an integer to save the size of the queue
    int size = 0;
    
    //Create a temporary node pointer to move across the queue
    run_node_t * current = queue->head;
    
    //Loop until the temporary node pointer is pointing to NULL
    while(current != NULL){
      //Move the current node pointer to the next node in the queue
      current = current->next;
      
      //Add 1 to the size of the queue every time the node pointer is moved
      size++;
    }
    
    //Free memory allocated for the current run_node pointer
    free(current);
    
    //Return the size of the queue
    return size;
  }
  
  
  //SORTING FUNCTIONS
  //
  //O(n log n) sort that merges the runs from a run_queue and returns them as a single queue
  queue_t * merge_sort(run_queue_t * sequence, int length){
    //Check if the length of the run_queue is 1 or less
    if (length <= 1)
    {
      //Exit the recursive calls of this function
      return sequence->head->run;
    }
    
    //Create a queue for the sorted runs to be stored in and returned
    queue_t * queue = queue_create();
    
    //Find the midpoint of the queue of runs
    int mid = length / 2;
    
    //Create lengths for a left and right lengths for new queues of runs
    int left_length = mid;
    int right_length = length - mid;
    
    //Create run_queues for the left and right halves of the imported queue of runs
    run_queue_t * left_run_queue = run_queue_create();
    run_queue_t * right_run_queue = run_queue_create();
    
    //Create queues to for the left and right halves of the imported queue of runs
    queue_t * left_queue = queue_create();
    queue_t * right_queue = queue_create();
    
    //Loop through the left half of the sequence
    for (int i = 0; i < left_length; i++)
    {
      //Add the run from the front of the queue of runs to the left-half run_queue
      run_queue_enqueue(left_run_queue, run_queue_dequeue(sequence));
    }
    
    //Loop through the right half of the sequence
    for (int i = 0; i < right_length; i++)
    {
      //Add the run from the front of the queue of runs to the right-half run_queue
      run_queue_enqueue(right_run_queue, run_queue_dequeue(sequence));
    }
    
    //Recall this function on each half of the queue of runs
    left_queue = merge_sort(left_run_queue, run_queue_size(left_run_queue));
    right_queue = merge_sort(right_run_queue, run_queue_size(right_run_queue));
    
    //Merge the left and right halves of the queue of runs
    queue = merge(left_queue, right_queue);
    
    //Free the memory allocated for the queues for each halg of the queue of runs
    run_queue_destroy(left_run_queue);
    run_queue_destroy(right_run_queue);
    queue_destroy(left_queue);
    queue_destroy(right_queue);
    
    //Return the sorted queue of all the elements in the imported sequence
    return queue;
  }
  
  
  //Merges two sorted queues into one sorted queue
  queue_t * merge(queue_t * queue_left, queue_t * queue_right){
    //Make node temporary pointers for each of the queues to be merged
    node_t * current_left = queue_left->head, * current_right = queue_right->head;

    //Create a new queue that the queues will be merged in to
    queue_t * result = queue_create();

    //Loop until either of the temoprary pointers are NULL
    while (current_left != NULL && current_right != NULL)
    {
      //Check if the current left value is lower than the right or the right pointer is NULL
      if (current_left->value <= current_right->value)
      {
        //Adds the left current value to the end of the total queue
        queue_enqueue(result, current_left->value);

        //Move the pointer of the left queue
        current_left = current_left->next;
      }
      //Acts if the current right value is lower than the left or the right pointer is NULL
      else
      {
        //Adds the right current value to the end of the total queue
        queue_enqueue(result, current_right->value);

        //Move the pointer of the right queue
        current_right = current_right->next;
      }
    }
    
    //Loop until the current left pointer is NULL
    while (current_left != NULL)
    {
      //Adds the left current value to the end of the total queue
      queue_enqueue(result, current_left->value);
      
      //Move the pointer of the left queue
      current_left = current_left->next;
    }
    
    //Loop until the current right pointer is NULL
    while (current_right != NULL)
    {
      //Adds the right current value to the end of the total queue
      queue_enqueue(result, current_right->value);
        
      //Move the pointer of the right queue
      current_right = current_right->next;
    }
    
    //Free the memory allocated to the temporary pointers
    free(current_left);
    free(current_right);

    //Return the queue of merged queues
    return result;
  }
  
  
  //Reads the zigzag.txt file and appropriately fill the queue of runs
  int read_file(run_queue_t * sequence){
    //Declare variables
    int length = 0;
    int data = 0;
    
    //Create a file pointer
    FILE * ifp = NULL;
    
    //Assign the file pointer to the zigzag.txt to be read
    ifp = fopen("zigzag.txt", "r");
    
    //Scan the file for the amount of values in the sequence of data
    fscanf(ifp, "%d", &length);  
    
    //Check if the length of the sequence is 0
    if (length < 1){
      //Exit the function by returning false
      return 0;
    }
    
    //Create a temporary run_queue node
    queue_t * current = queue_create();
    
    //Loop an amount of times equal to the length of the sequence
    for (int i = 0; i < length; i++)
    {
      //Scan the file for the data of the next node on the sequence
      fscanf(ifp, "%d", &data);
      
      //Check for a new run or if the new data follows the pattern of the current run
      if (follows_pattern(current, data) || queue_is_empty(current))
      {
        //Enqueue the new data into the current run
        queue_enqueue(current, data);
      }
      else
      {
        //Enqueue the current run into the queue of runs
        run_queue_enqueue(sequence, current);

        //Allocate memory for a new run
        queue_t * temp = malloc(sizeof(queue_t));
        current = temp;
        
        //Allocate memory for the current run
        current = queue_create();
        
        //Enqueue the new data into the current run
        queue_enqueue(current, data);
      }
    }
    
    //Close the file pointer
    fclose(ifp);
    
    //Enqueue the current run into the queue of runs
    run_queue_enqueue(sequence, current);
    
    //Return true for a successful creation of the sequence from the file datum
    return 1;
  }
  
  
  //Check if the data can be added to the current queue
  int follows_pattern(queue_t * queue, int data){
    //True if 0 or 1 elements in the queue
    if (queue->head == queue->tail)
      return 1;
      
    //True if the pattern is increasing and the new data is increasing
    if (queue->head->value <= queue->tail->value && queue->tail->value <= data)
      return 1;
      
    //True if the pattern is decreasing and the new data is decreasing
    if (queue->head->value >= queue->tail->value && queue->tail->value >= data)
      return 1;
      
    //False if none of the previous were true
    return 0;
  }
  
  
  //Reverse the direction of runs that have numbers in decreasing order
  void reverse_runs(run_queue_t * sequence){
    //Create a temporary run_node pointer to move across the run_queue
    run_node_t * current = sequence->head;

    //Loop until the temporary run_node pointer is NULL
    while(current != NULL)
    {
      //Check if the run is in decreasing order
      if (current->run->head->value > current->run->tail->value)
      {
        //Create a temporary stack help reverse the queue
        stack_t * temp = stack_create();
        
        //Loop while the current run is not empty
        while(!queue_is_empty(current->run))
        {
          //Fill the stack with all the values of the queue
          stack_push(temp, queue_dequeue(current->run));
        }
        
        //Loop while the stack is not empty
        while (!stack_is_empty(temp))
        {
          //Put the values back from the stack into the queue, it will now be reveresed
          queue_enqueue(current->run, stack_pop(temp));
        }
        
        //Free the memory allocated to the temporary stack
        stack_destroy(temp);
      }

      //Move the current node pointer to the next node in the queue
      current = current->next;
    }

    //Free memory allocated for the current run_node pointer
    free(current);
  }