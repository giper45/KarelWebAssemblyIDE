# Solution Karel Linked List Beepers
The goal is to track the number of beepers along a straight line and save positions in a linked list.

We start by defining a struct that represents the linked list node, which contains the position of the beeper and a pointer to the next node in the list.

```c
typedef struct element {
    int position;
    struct element* next;
    
} BeeperNode;


```c
void studentCode()
{
    BeeperNode* head = NULL; // Variable that holds the head of the linked list
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function

}
```
We define a global variable `head` to hold the head of the linked list. The `BeeperNode` struct contains an integer `position` to store the position of the beeper and a pointer `next` to point to the next node in the list.

Now create a function to add a new node to the linked list. This function will create a new node, set its position, and link it to the previous node.

```c
BeeperNode* addBeeperNode(BeeperNode* head, int position)
{
    BeeperNode* newNode = (BeeperNode*)malloc(sizeof(BeeperNode));
    newNode->position = position;
    newNode->next = NULL;
    if (head == NULL) {
        return newNode; // If the list is empty, return the new node as the head
    }
    BeeperNode* current = head;
    while (current->next != NULL) {
        current = current->next; // Traverse to the end of the list
    }
    current->next = newNode; // Link the new node to the end of the list
    return head; // Return the head of the list
}
```


We also need a function to print the linked list, showing the positions of the beepers collected by Karel.

```c
void printBeeperList(BeeperNode* head)
{
    BeeperNode* current = head;
    while (current != NULL) {
        printf("Beeper at position: %d\n", current->position);
        current = current->next; // Move to the next node
    }
}
```

Let's look at the code:
```c
typedef struct element {
    int position;
    struct element* next;
    
} BeeperNode;

BeeperNode* addBeeperNode(BeeperNode* head, int position)
{
    BeeperNode* newNode = (BeeperNode*)malloc(sizeof(BeeperNode));
    newNode->position = position;
    newNode->next = NULL;
    if (head == NULL) {
        return newNode; // If the list is empty, return the new node as the head
    }
    BeeperNode* current = head;
    while (current->next != NULL) {
        current = current->next; // Traverse to the end of the list
    }
    current->next = newNode; // Link the new node to the end of the list
    return head; // Return the head of the list
}

void printBeeperList(BeeperNode* head)
{
    BeeperNode* current = head;
    while (current != NULL) {
        printf("Beeper at position: %d\n", current->position);
        current = current->next; // Move to the next node
    }
}

void studentCode()
{
    BeeperNode* head = NULL; // Variable that holds the head of the linked list
    int localCounter = 0;
    head = addBeeperNode(head, 3);
    head = addBeeperNode(head, 6);
    head = addBeeperNode(head, 9);
    printBeeperList(head);
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function

}
```

### Add Beeper Node
The `addBeeperNode` function creates a new node, sets its position, and links it to the previous node in the linked list. If the list is empty, it returns the new node as the head. Otherwise, it traverses to the end of the list and links the new node. The function always returns the head of the list (that is, basically the pointer to the first node).

A simple image to represent the linked list before and after adding a new node:

```
Before adding a new node:
head -> [3] -> [6] -> NULL
After adding a new node with position 9:
head -> [3] -> [6] -> [9] -> NULL
```

Now we are ready to implement the `studentCode` function, which will use the `addBeeperNode` function to add beepers at specific positions and print the linked list.


```c
#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(9, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(7, 1);
    karel_add_beeper(2, 1);
}

static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}
typedef struct element {
    int position;
    struct element* next;
    
} BeeperNode;

BeeperNode* addBeeperNode(BeeperNode* head, int position)
{
    BeeperNode* newNode = (BeeperNode*)malloc(sizeof(BeeperNode));
    newNode->position = position;
    newNode->next = NULL;
    if (head == NULL) {
        return newNode; // If the list is empty, return the new node as the head
    }
    BeeperNode* current = head;
    while (current->next != NULL) {
        current = current->next; // Traverse to the end of the list
    }
    current->next = newNode; // Link the new node to the end of the list
    return head; // Return the head of the list
}

void printBeeperList(BeeperNode* head)
{
    BeeperNode* current = head;
    while (current != NULL) {
        printf("Beeper at position %d\n", current->position);
        current = current->next; // Move to the next node
    }
}

void studentCode()
{
    BeeperNode* head = NULL; // Variable that holds the head of the linked list
    int localCounter = 0;
/*    head = addBeeperNode(head, 3);
    head = addBeeperNode(head, 6);
    head = addBeeperNode(head, 9);
    printBeeperList(head);    
    */
    while (front_is_clear())
    {
        if (beepers_present())
        {
            int position = karel_get_x();
            printf("Beeper found at position %d\n", position);
            head = addBeeperNode(head, position);
        }
        karel_move();
    }
    printBeeperList(head);
    
    // It is important to free the memory, now it is not doing anything
    //freeBeeperList(head);
}
```

### What misses? 
In the previous solution, you are not freeing the allocated memory for the linked list nodes after you are done using them. 
never forget to free the allocated memory for the linked list nodes after you are done using them to avoid memory leaks. A memory leak is a situation where memory that is no longer needed is not released, leading to increased memory usage over time. This is a typical issue in  programming, especially when using dynamic memory allocation, and it is the cause of many bugs in C programs.

You can create a function to free the linked list:

```c
void freeBeeperList(BeeperNode* head)
{
    BeeperNode* current = head;
    while (current != NULL) {
        BeeperNode* next = current->next;
        free(current);
        current = next;
    }
}
```
You can call this function at the end of the `studentCode` function to free the memory allocated for the linked list nodes.

```c
void studentCode()
{
    BeeperNode* head = NULL; // Variable that holds the head of the linked list
    int localCounter = 0;
/*    head = addBeeperNode(head, 3);
    head = addBeeperNode(head, 6);
    head = addBeeperNode(head, 9);
    printBeeperList(head);    
    */
    while (front_is_clear())
    {
        if (beepers_present())
        {
            int position = karel_get_x();
            printf("Beeper found at position %d\n", position);
            head = addBeeperNode(head, position);
        }
        karel_move();
    }
    printBeeperList(head);
    
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function
    freeBeeperList(head);
}
```


### Variant solutions 

#### Variant 1 - Dynamic array
We first need to find the number of beepers in the environment to allocate the dynamic array. We can do this by navigating the path and counting the beepers.

```c
void studentCode()
{
    int num_beepers = 0;
    int *beeperPositions; 
    
    while (front_is_clear())
    {
        if (beepers_present())
        {
            printf("Beeper found at position %d\n", karel_get_x());
            num_beepers++;

        }
    karel_move();
    }
    
    beeperPositions = (int *)malloc(num_beepers * sizeof(int));
}
```

Now we can turn Karel around and navigate back to collect the beeper positions in the array.

```c
#include "karel.h"
#define REFRESH_RATE 0.01 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(7, 1);
    karel_add_beeper(2, 1);
}

static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}

void printArray(int *positions, int num_beepers)
{
    for (int i = 0; i < num_beepers; i++)
    {
        printf("array[%d]=%d\n", i, positions[i]);
    }
}

void studentCode()
{
    int num_beepers = 0;
    int *beeperPositions; 
    
    while (front_is_clear())
    {
        if (beepers_present())
        {
            printf("Beeper found at position %d\n", karel_get_x());
            num_beepers++;

        }
    karel_move();
    }
    printf("Allocate an array of %d beepers\n", num_beepers);
    beeperPositions = (int *)malloc(num_beepers * sizeof(int));
    karel_turn_left();
    karel_turn_left();
    
    int i = 0;
    while (front_is_clear())
    {
         if (beepers_present())
         {
             beeperPositions[i++] = karel_get_x();
             
         }
        karel_move();
    }
    
    printArray(beeperPositions, num_beepers); 
    free(beeperPositions);

}
```
We also need to free the allocated memory after we are done using the array to avoid memory leaks. 

```c
free(beeperPositions);
```

## Variant two - FIFO Queue
In this variant, we can use a FIFO queue to store the beeper positions. We can define a struct for the queue and implement functions to enqueue and dequeue elements.

We start by defining the queue structure and the functions to enqueue and dequeue elements.

```c
typedef struct QueueNode {
    int position;
    struct QueueNode* next;
} QueueNode;  

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
void enqueue(Queue* queue, int position) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->position = position;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}
QueueNode* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL; // Queue is empty
    }
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL; // If the queue is now empty, set rear to NULL
    }
    return temp; // Return the dequeued node
}
void printQueue(Queue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {   
        printf("Beeper at position: %d\n", current->position);
        current = current->next; // Move to the next node
    }
}
```

Let's try to use the queue in the `studentCode` function with fake beeper positions.

```c
void studentCode() {
    Queue* queue = createQueue();

    // Simulate finding beepers at positions 2, 4, and 6
    enqueue(queue, 2);
    enqueue(queue, 4);
    enqueue(queue, 6);

    printQueue(queue);

    // Clean up
    while ((node = dequeue(queue)) != NULL) {
        free(node);
    }

    free(queue);
}

```c

Now we need to navigate the environment and collect the beeper positions by adding them to the queue.

```c
void studentCode() {
    Queue* queue = createQueue();
    QueueNode* node = NULL;
    // Simulate finding beepers at positions 2, 4, and 6
 /*   enqueue(queue, 2);
    enqueue(queue, 4);
    enqueue(queue, 6);
*/
    while(front_is_clear())
    {
        if (beepers_present())
        {
            printf("Found a beeper at position%d\n", karel_get_x());
            enqueue(queue, karel_get_x());
        }
        karel_move();
    }


    free(queue);
}
```
Now we can print the positions of the beepers in the order they were added by dequeuing them from the queue.
Let's write a function `printBeepers()` to print the beeper positions in the same order they were added to the queue.

```c
#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(7, 1);
    karel_add_beeper(2, 1);
}

static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}

typedef struct QueueNode {
    int position;
    struct QueueNode* next;
} QueueNode;  

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
void enqueue(Queue* queue, int position) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->position = position;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}
QueueNode* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL; // Queue is empty
    }
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL; // If the queue is now empty, set rear to NULL
    }
    return temp; // Return the dequeued node
}
void printQueue(Queue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {   
        printf("Beeper at position: %d\n", current->position);
        current = current->next; // Move to the next node
    }
}


void printBeepers(Queue* queue)
{
    QueueNode* node = NULL;

     // Clean up
    while ((node = dequeue(queue)) != NULL) {
        printf("Beeper at position %d\n", node->position);
        free(node);
    }
    
}

void studentCode() {
    Queue* queue = createQueue();
    // Simulate finding beepers at positions 2, 4, and 6
 /*   enqueue(queue, 2);
    enqueue(queue, 4);
    enqueue(queue, 6);
*/
    while(front_is_clear())
    {
        if (beepers_present())
        {
            printf("Found a beeper at position %d\n", karel_get_x());
            enqueue(queue, karel_get_x());
        }
        karel_move();
    }
    printBeepers(queue);


    free(queue);
}
```

### Variant Three - using stack
The approach is similar to the FIFO queue, but we will use a stack to store the beeper positions. We can define a struct for the stack and implement functions to push and pop elements. Here the solution:

```c
#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(7, 1);
    karel_add_beeper(2, 1);
}

static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}

typedef struct StackNode {
    int position;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, int position) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->position = position;
    newNode->next = stack->top;
    stack->top = newNode;
}

StackNode* pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL; // Stack is empty
    }
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    return temp; // Return the popped node
}

void printStack(Stack* stack) {
    StackNode* current = stack->top;
    while (current != NULL) {
        printf("Beeper at position: %d\n", current->position);
        current = current->next;
    }
}

void printBeepers(Stack* stack)
{
    StackNode* node = NULL;

    // Clean up
    while ((node = pop(stack)) != NULL) {
        printf("Beeper at position %d\n", node->position);
        free(node);
    }

}

void studentCode() {
    Stack* stack = createStack();
    // Simulate finding beepers at positions 2, 4, and 6
    /*   enqueue(queue, 2);
       enqueue(queue, 4);
       enqueue(queue, 6);
   */
    while(front_is_clear())
    {
        if (beepers_present())
        {
            printf("Found a beeper at position %d\n", karel_get_x());
            push(stack, karel_get_x());
        }
        karel_move();
    }
    printBeepers(stack);

    free(stack);
}