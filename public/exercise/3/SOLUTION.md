# Solution: Karel Square Path
This exercise demonstrates how to create precise geometric patterns using counting and state management within the existing `studentCode()` structure.
## Simple approach
The most simple solution is to use a static variable to track the current side of the square and the number of steps taken on that side. This allows Karel to move in a square pattern without needing complex loops or additional functions.
```c
void studentCode() {
    static int step = 0;      // Steps taken on current side
    static int side = 0;      // Which side of square (0-3)
    
    
    karel_move();
    karel_move();
    karel_move();
    karel_turn_left();
    karel_move();
    karel_move();
    karel_move();
    karel_turn_left();
    karel_move();
    karel_move();
    karel_move();
    karel_turn_left();
    karel_move();
    karel_move();
    karel_move();

   
}
```

Obviously, this solution is not very flexible, and it is boring to write. A developer does not like repetitive code, so we can improve it by using a loop and a counter to make it more elegant and maintainable.

We introduce a simple counter to track the number of steps and sides, allowing Karel to move in a square pattern without hardcoding each step.
## Approach with while loop
The `while` loop allows Karel to repeat the movement pattern until all four sides of the square are completed. The `step` variable tracks how many steps Karel has taken on the current side, and the `side` variable tracks which side of the square Karel is currently on.
Try on the next code snippet:

```c
void studentCode() 
{
    static int step = 0;      // Steps taken on current side
    static int side = 0;      // Which side of square (0-3)
    while (side < 4) { // Loop until all 4 sides are completed
        if (step < 3) {
            karel_move();      // Move forward one step
            step++;
        } else {
            karel_turn_left(); // Turn left if blocked
            step = 0;          // Reset step count for new side
            side++;            // Move to next side
        }
    }
}  
```

This solution is more flexible and allows Karel to adapt to different square sizes by changing the number of steps per side. The `while` loop continues until all four sides are completed, making it easy to adjust the square size by modifying the `step` variable.
In particular, the `while` loop structure checks the `side` variable to determine when all four sides have been completed. The `step` variable is reset to 0 each time Karel turns left, allowing Karel to move forward three steps on each side of the square before turning left again.


## Approach with for loop
Alternatively, we can use a `for` loop to achieve the same result. The `for` loop iterates through each side of the square, moving Karel forward three steps and then turning left to face the next side.
```c
void studentCode()
{
    for (int side = 0; side < 4; side++) { // Loop through each side of the square
        for (int step = 0; step < 3; step++) { // Move forward 3 steps on each side
            karel_move();
        }
        karel_turn_left(); // Turn left to face the next side
    }
}
```



## Too complicated? Continue with next exercises!
If you find the above solutions too complicated, you can always use the simple approach with hardcoded steps for now. We will cover loops in future exercises, and you can come back to this exercise later to implement a more elegant solution.
