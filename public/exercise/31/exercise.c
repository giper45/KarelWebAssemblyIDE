#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Stack implementation using column at x=2
int stack_top = 1;      // y-coordinate of stack top
const int STACK_X = 2;  // x-coordinate for stack
const int MAX_STACK_SIZE = 7;

// Queue implementation using row at y=2  
int queue_front = 4;    // x-coordinate of queue front
int queue_rear = 4;     // x-coordinate of queue rear
const int QUEUE_Y = 2;  // y-coordinate for queue
const int MAX_QUEUE_SIZE = 6;

// TODO: Implement stack operations

// TODO: Function to push element onto stack
// int stack_push() - returns 1 if successful, 0 if stack full

// TODO: Function to pop element from stack  
// int stack_pop() - returns 1 if successful, 0 if stack empty

// TODO: Function to check if stack is empty
// int stack_is_empty()

// TODO: Function to check if stack is full
// int stack_is_full()

// TODO: Implement queue operations

// TODO: Function to enqueue element
// int queue_enqueue() - returns 1 if successful, 0 if queue full

// TODO: Function to dequeue element
// int queue_dequeue() - returns 1 if successful, 0 if queue empty

// TODO: Function to check if queue is empty
// int queue_is_empty()

// TODO: Function to check if queue is full
// int queue_is_full()

void setup() {
    karel_init();
    
    printf("Karel Stack & Queue Operations\n");
    printf("==============================\n");
    printf("Stack: Column at x=%d (bottom to top)\n", STACK_X);
    printf("Queue: Row at y=%d (front to rear)\n", QUEUE_Y);
    
    // Add visual markers for data structure boundaries
    // Mark stack area
    for(int y = 1; y <= MAX_STACK_SIZE; y++) {
        if(y == 1 || y == MAX_STACK_SIZE) {
            // Add boundary markers (you can add walls or special indicators)
        }
    }
    
    // Mark queue area  
    for(int x = 4; x <= 4 + MAX_QUEUE_SIZE - 1; x++) {
        if(x == 4 || x == 4 + MAX_QUEUE_SIZE - 1) {
            // Add boundary markers
        }
    }
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    printf("Stack Top: %d | Queue Front: %d | Queue Rear: %d\n", 
           stack_top, queue_front, queue_rear);
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastActionTime = 0;
    static int demo_phase = 0;
    
    if (timeSec - lastActionTime > 2.0) {
        
        switch(demo_phase % 8) {
            case 0:
                printf("Demo: Push to stack\n");
                // TODO: Implement stack push operation
                // Move Karel to stack position and push element
                break;
                
            case 1:
                printf("Demo: Push another to stack\n");
                // TODO: Push second element
                break;
                
            case 2:
                printf("Demo: Enqueue to queue\n");  
                // TODO: Implement queue enqueue operation
                break;
                
            case 3:
                printf("Demo: Enqueue another to queue\n");
                // TODO: Enqueue second element
                break;
                
            case 4:
                printf("Demo: Pop from stack (LIFO)\n");
                // TODO: Pop from stack - should get last pushed element
                break;
                
            case 5:
                printf("Demo: Dequeue from queue (FIFO)\n");
                // TODO: Dequeue from queue - should get first enqueued element
                break;
                
            case 6:
                printf("Demo: Check empty conditions\n");
                // TODO: Demonstrate empty checking
                break;
                
            case 7:
                printf("Demo: Test full conditions\n");
                // TODO: Fill structures to capacity and test limits
                break;
        }
        
        demo_phase++;
        lastActionTime = timeSec;
    }
}

// TODO: Implement all the stack and queue functions here

// Example starter:
// int stack_push() {
//     if (stack_is_full()) return 0;
//     
//     // Move Karel to stack position
//     // Put beeper at stack top
//     // Update stack_top
//     return 1;
// }
