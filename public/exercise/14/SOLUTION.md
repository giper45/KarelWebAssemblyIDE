# Solution: Array of Positions

## Solution Explanation
This exercise demonstrates how to use arrays to store coordinate data and implement navigation logic. The solution combines array traversal with geometric navigation algorithms.

## Complete Solution
```c
void navigate_to_position(int target_x, int target_y) {
    // Move horizontally first
    while (karel_get_x() != target_x) {
        if (karel_get_x() < target_x) {
            // Need to move east
            while (karel_get_direction() != 0) { // 0 = East
                karel_turn_left();
            }
            karel_move();
        } else {
            // Need to move west
            while (karel_get_direction() != 2) { // 2 = West
                karel_turn_left();
            }
            karel_move();
        }
    }
    
    // Move vertically
    while (karel_get_y() != target_y) {
        if (karel_get_y() < target_y) {
            // Need to move north
            while (karel_get_direction() != 1) { // 1 = North
                karel_turn_left();
            }
            karel_move();
        } else {
            // Need to move south
            while (karel_get_direction() != 3) { // 3 = South
                karel_turn_left();
            }
            karel_move();
        }
    }
}

void visit_all_positions() {
    int x_positions[] = {3, 1, 5, 4, 2};
    int y_positions[] = {2, 4, 1, 3, 5};
    int num_positions = sizeof(x_positions) / sizeof(x_positions[0]);
    
    for (int i = 0; i < num_positions; i++) {
        printf("Moving to position (%d, %d)...\n", x_positions[i], y_positions[i]);
        navigate_to_position(x_positions[i], y_positions[i]);
        
        if (beepers_present()) {
            karel_pick_beeper();
            printf("Beeper collected at (%d, %d)\n", karel_get_x(), karel_get_y());
        }
    }
    printf("All positions visited!\n");
}

void studentCode() {
    visit_all_positions();
    printf("Karel has completed the mission!\n");
}
```


Explanation: 

This solution uses arrays to store the target x and y coordinates for Karel to visit. The `navigate_to_position` function moves Karel to the specified coordinates by first moving horizontally and then vertically, adjusting Karel's direction as needed. The `visit_all_positions` function iterates through the arrays of positions, calling the navigation function for each one and picking up any beepers present. Finally, the `studentCode` function initiates the visiting process and confirms mission completion.


The `navigate_to_position` function is crucial as it encapsulates the logic for moving Karel to a specific coordinate, ensuring that Karel always faces the correct direction before moving. The solution effectively demonstrates how to use arrays and control structures to navigate through a grid-like environment, making it a practical example of basic programming concepts in action.


The `visit_all_positions` function iterates through the predefined arrays of x and y coordinates, calling the navigation function for each position. If Karel encounters a beeper at any position, it picks it up and prints a confirmation message. The final print statement indicates that Karel has completed its mission after visiting all specified positions.

