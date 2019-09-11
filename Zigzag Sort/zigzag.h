#include <stdio.h>
#include <stdlib.h>

// This is a node from our in class linked list example.
// Here I will reuse code to implement a linked list structure.
typedef struct node_t
{
   int value;

   struct node_t * next;
      
} node_t;


// I'll use a struct to keep track of a stack
// Here I do my stack linked list style.
typedef struct stack_t
{
   node_t * top;

} stack_t;


// Here are the stack functions. Notice that the functions
// are almost exactly the same but I'm using a linked list to store
// the data in the backend. This is what is meant by an abstract
// data type. The concept can be hidden from the underlying implementation.
//
// We make one extra distinction here. There is no capacity because
// such a notion makes no sense in a stack.
stack_t * stack_create();
void stack_destroy(stack_t * stack);
void stack_push(stack_t * stack, int data);
int stack_pop(stack_t * stack);
int stack_peek(stack_t * stack);
int stack_is_empty(stack_t * stack);
void stack_print(stack_t * stack);


// I'll use the queue's here linked list style.
// My code will read in the data as a queue and sort it.
typedef struct queue_t
{
   node_t *head, *tail;

} queue_t;


// Functions for creating and dealing with queues.
queue_t * queue_create();
void queue_destroy(queue_t * queue);
void queue_enqueue(queue_t * queue, int data);
int queue_dequeue(queue_t * queue);
int queue_peek(queue_t * queue);
int queue_is_empty(queue_t * queue);
int queue_size(queue_t * queue);
void queue_print(queue_t * queue);


// Here I make a queue of runs. I need two pieces:
//
// 1) A node to store the individual run and a pointer to the next run.
// 2) A list struct to group together all of the runs.
//
// This structure (in practice) is a linked list of linked lists.
//
// Another option to reduce redundant code is to use a (void *)
// to store the data in node. You are welcome to attempt that
// if you like. Then you will only have one queue implementation.
// 
// Another option is to make this structure a stack. But why would
// that be helpful? (Hint: there is a fast solution that makes this
// a stack.) You are of course allowed to make this part any structure
// you want.
typedef struct run_node_t
{
   queue_t * run;

   struct run_node_t * next;
   
} run_node_t;

typedef struct run_queue_t
{
   run_node_t *head, *tail;

} run_queue_t;

// Here are functions for dealing with our run queue.
// Notice the naming problems. We have to give different names
// for each function. Good grief! Other languages handle this much
// better. Hopefully this program will get you to appreciate other
// languages in the future.
run_queue_t * run_queue_create();
void run_queue_destroy(run_queue_t * queue);
void run_queue_enqueue(run_queue_t * queue, queue_t * run);
queue_t * run_queue_dequeue(run_queue_t * queue);
queue_t * run_queue_peek(run_queue_t * queue);
int run_queue_is_empty(run_queue_t * queue);
int run_queue_size(run_queue_t * queue);


// Other functions will go here for combining runs into a single (queue_t *).
// I'm not giving these to you as I want you to figure out combination.
queue_t * merge_sort(run_queue_t * sequence, int length);
queue_t * merge(queue_t * queue1, queue_t * queue2);
int read_file(run_queue_t * sequence);
int follows_pattern(queue_t * queue, int data);
void reverse_runs(run_queue_t * sequence);