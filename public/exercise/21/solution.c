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
    
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function

}