# Karel Stack & Queue Operations

## Objective
Implement stack (LIFO) and queue (FIFO) data structures using Karel's beeper operations to understand fundamental data structure concepts.

## Background
Stacks and queues are fundamental data structures with different access patterns:
- **Stack (LIFO)**: Last In, First Out - like a stack of plates
- **Queue (FIFO)**: First In, First Out - like a line of people
- **Karel Implementation**: Use beeper positions to represent data elements
- **Visual Learning**: See data structure operations in Karel's world

## Your Task
1. Implement a stack using a column of beepers
2. Implement a queue using a row of beepers
3. Create push/pop operations for the stack
4. Create enqueue/dequeue operations for the queue
5. Demonstrate both data structures working together

## Key Concepts
- **Stack Operations**: `push()` adds to top, `pop()` removes from top
- **Queue Operations**: `enqueue()` adds to rear, `dequeue()` removes from front
- **Empty Conditions**: Check if data structure is empty
- **Full Conditions**: Handle capacity limits
- **Data Structure Invariants**: Maintain proper structure rules

## Data Structure Applications in Karel
- **Stack**: Undo operations, backtracking paths, nested operations
- **Queue**: Breadth-first search, task scheduling, buffer management
- **Combined Usage**: Use both structures for complex algorithms

## Karel Functions for Data Structures
- `karel_put_beeper()` - Add element (push/enqueue)
- `karel_pick_beeper()` - Remove element (pop/dequeue)
- `beepers_present()` - Check if position has data
- Navigation functions to move between data positions

## Tips
- Use consistent positions for stack top and queue front/rear
- Always check for empty conditions before pop/dequeue
- Maintain clear visual representation of data structure state
- Test edge cases: empty structures, single elements, full capacity
- Consider error handling for invalid operations
