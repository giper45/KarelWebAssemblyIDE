# Karel linked-list beeper
In this exercise, Karel should track the number of beepers along a straight line and save positions in a linked list.

Traverse the rows and columns of the world to collect beeper positions and store them in a linked list.
You should define a struct that represents the linked list node, which contains the position of the beeper and a pointer to the next node in the list.

Then, you should implement a function that prints the linked list, showing the positions of the beepers collected by Karel.


## Additional Tasks
In this exercise, you have several new concepts like linked lists and dynamic memory allocation. You can try to implement the following variants:

#### Variant 1 - Dynamic array
Instead of using a linked list, you can use a dynamic array to store the positions of the beepers. You can use `malloc` to allocate memory for the array. Try to navigate the path, count the number of beepers to obtain the size of the array, and come back to collect the beeper positions in the array.
You can define a dynamic array of integers with the following syntax:

```c
int* beeperPositions = (int*)malloc(NO_BEEPERS * sizeof(int));
``` 

You can also define an array of structs to hold more complex data, like the position and the number of beepers at that position.
You can define a struct like this:
```c
typedef struct {
    int position;
    int numBeepers;
} BeeperPosition;
BeeperPosition* beeperPositions = (BeeperPosition*)malloc(NO_BEEPERS * sizeof(BeeperPosition));
``` 





### Variant 2 - FIFO Queue
You can implement a FIFO (First In, First Out) queue using a linked list. In this case, you would maintain two pointers: one for the head (front) of the queue and one for the tail (back) of the queue. When you add a new beeper position, you would add it to the tail of the queue, and when you process a beeper position, you would remove it from the head of the queue. This allows you to process beeper positions in the order they were added.

```c
typedef struct element {
    int value; // This could represent the position of a beeper
    struct element* next; // Pointer to the next node
} Node;
Node* enqueue(Node* tail, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    if (tail != NULL) {
        tail->next = newNode; // Link the new node to the end of the queue
    }
    return newNode; // Return the new tail of the queue
}
Node* dequeue(Node** head) {
    if (*head == NULL) {
        return NULL; // Queue is empty
    }
    Node* temp = *head;
    *head = (*head)->next; // Move the head to the next node
    temp->next = NULL; // Clear the next pointer of the dequeued node
    return temp; // Return the dequeued node
}
```
You can use the `enqueue` function to add new beeper positions to the queue and the `dequeue` function to process them in the order they were added.

Try to implement the Karel exercise using the FIFO queue.
You can first navigate the environment and collect the beeper positions by adding them to the queue.
Then, you can print the positions of the beepers in the order they were added by dequeuing them from the queue.


### Variant 3 - Using stack 
Another option is to implement a stack using a linked list. In this case, you would maintain a pointer to the top of the stack. When you add a new beeper position, you would push it onto the top of the stack, and when you process a beeper position, you would pop it from the top of the stack. This allows you to process beeper positions in reverse order.

```c
typedef struct element {
    int value; // This could represent the position of a beeper
    struct element* next; // Pointer to the next node
} Node;
Node* push(Node* top, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = top; // Link the new node to the top of the stack
    return newNode; // Return the new top of the stack
}
Node* pop(Node** top) {
    if (*top == NULL) {
        return NULL; // Stack is empty
    }
    Node* temp = *top;  
    *top = (*top)->next; // Move the top to the next node
    temp->next = NULL; // Clear the next pointer of the popped node
    return temp; // Return the popped node
}
```
You can use the `push` function to add new beeper positions to the stack and the `pop` function to process them in reverse order.
You can implement the Karel exercise using the stack by first navigating the environment and collecting the beeper positions by pushing them onto the stack.
Then, you can print the positions of the beepers in reverse order by popping them from the stack.




## Background concept - linked lists
A linked list is a data structure that consists of a sequence of elements, where each element points to the next one. Each element in a linked list is called a node, and it contains data and a pointer to the next node in the list.  

A simple example of a linked list node in C could look like this:

```c
struct element {
    int value; // This could represent the position of a beeper
    struct element* next; // Pointer to the next node
};
```

You can also use a `typedef` to simplify the usage of the struct:

```c
typedef struct element {
    int value; // This could represent the position of a beeper
    struct element* next; // Pointer to the next node
} Node;
``` 

To use this struct, you can create a variable of type `Node`:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int value; // This could represent the position of a beeper
    struct element* next; // Pointer to the next node
} Node;

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main()
{
        Node node_first;
        Node node_second;
        node_first.value = 1;
        node_second.value = 2;

        node_first.next = &node_second;
        node_second.next = NULL;
        printList(&node_first);
        return 0;

}
```
The simple example above creates a linked list with two nodes, where the first node has a value of 1 and points to the second node, which has a value of 2. The `printList` function traverses the linked list and prints the values of each node.


## Dynamic memory allocation
The difference between a linked list and an array is that a linked list can grow and shrink dynamically, while an array has a fixed size. In a linked list, you can easily add or remove nodes without needing to resize the entire structure, which is not possible with arrays.

For this reason, usually linked lists use dynamic memory allocation to create new nodes. In C, you can use the `malloc` function to allocate memory for a new node:

```c
Node* newNode = (Node*)malloc(sizeof(Node));
```

The `malloc` function allocates a block of memory of the specified size (in this case, the size of the `Node` struct) and returns a pointer to the allocated memory. You can then set the values of the new node and link it to the rest of the list.
You should also remember to free the memory allocated for the nodes when you are done with the linked list to avoid memory leaks:

```c
free(newNode);
```


Show the previous example with dynamic memory allocation:

```c
#include <stdio.h>
#include <stdlib.h> 
typedef struct element {
    int value; // This could represent the position of a beeper
    struct element* next; // Pointer to the next node
} Node;
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}
int main()
{
    Node* head = (Node*)malloc(sizeof(Node));
    Node* second = (Node*)malloc(sizeof(Node));
    head->value = 1;
    second->value = 2;
    head->next = second;
    second->next = NULL;
    printList(head);
    free(head);
    free(second);
    return 0;
}
```

Now you have all the necessary background to implement the Karel exercise with linked lists.


