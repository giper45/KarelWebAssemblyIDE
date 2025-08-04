# Karel Pointer Navigation

## Objective
Learn pointers and memory addresses while controlling Karel through pointer-based functions and coordinate tracking.

## Background
Pointers are essential for advanced C programming. In this Karel exercise, you'll use pointers to:
- **Track Karel's position** using coordinate pointers
- **Pass position data** by reference to functions
- **Manipulate arrays** of coordinates using pointer arithmetic
- **Implement navigation algorithms** that modify position data directly
- **Understand memory addresses** in the context of Karel's world

## Your Task
1. Use pointers to track and modify Karel's position coordinates
2. Create functions that take position pointers as parameters
3. Implement navigation functions using pointer arithmetic
4. Build a waypoint system using arrays and pointers
5. Practice pointer safety and null pointer checking

## Key Concepts
- **Position Pointers**: `int *x_pos, *y_pos` for coordinates
- **Address-of Operator**: `&karel.x` to get position addresses
- **Dereference Operator**: `*x_pos` to access/modify values
- **Function Parameters**: Passing pointers to modify original data
- **Array-Pointer Relationship**: Navigate coordinate arrays
- **Pointer Arithmetic**: Moving through waypoint arrays

## Pointer Applications You'll Implement
- Position tracking functions using coordinate pointers
- Waypoint navigation using pointer arrays
- Distance calculations with position references
- Path recording using dynamic coordinate storage

## Karel Functions Enhanced with Pointers
- `karel_move()` - Track position changes via pointers
- `karel_turn_left()` - Update direction through pointer reference
- Navigation functions that modify coordinates directly
- Boundary checking using position pointers

## Tips
- Always initialize pointers before using them
- Check for NULL pointers in functions
- Use meaningful names: `int *x_coord` not just `int *p`
- Remember: modifying `*pointer` changes the original variable
- Be careful with pointer arithmetic and array bounds
