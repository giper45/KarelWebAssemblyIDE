# Karel First Steps: Learning C and Karel's World

In this first exercise, let's discover how to control Karel using basic C programming concepts. We'll see how to move Karel, use variables, print information, and interact with the world.

## Moving Karel and Using printf

The `studentCode()` function is where you write your solution. Let's start with a simple example:

```c
void studentCode() {
    karel_move();           // Move forward one step
    karel_move();           // Move forward another step
    karel_turn_left();      // Turn 90 degrees left
    karel_move();           // Move forward in new direction
    printf("Karel moved and turned!\n"); // Print a message
}
```

Notice how we use `printf` to display messages. In C, `printf` is used to print text and variable values. For example:

```c
void studentCode() {
    int steps = 0;
    if (front_is_clear()) {
        karel_move();
        steps++;
        printf("Karel moved! Steps: %d\n", steps);
    }
}
```

Here, we declare an integer variable `steps`, increment it, and print its value using `%d`.

## Checking Conditions and Using Variables

Karel can check if the path ahead is clear or if there are beepers at the current position. You can use `if` statements to make decisions:

```c
void studentCode() {
    if (front_is_clear()) {
        karel_move();
    } else {
        karel_turn_left();
        printf("Turned left because path was blocked.\n");
    }
}
```

You can also use variables to store information about Karel's position:

```c
void studentCode() {
    karel_move();
    int x = karel_get_x();
    int y = karel_get_y();
    printf("Karel is now at (%d, %d)\n", x, y);
}
```

## Working with Beepers

Karel can pick up and put down beepers. Let's see how to use these functions and print the result:

```c
void studentCode() {
    karel_move();
    if (beepers_present()) {
        karel_pick_beeper();
        printf("Picked up a beeper!\n");
    }
    if (beepers_in_bag()) {
        karel_put_beeper();
        printf("Placed a beeper!\n");
    }
}
```

## Putting It All Together

You can combine movement, conditions, and variables to create more complex behaviors. Try experimenting with different commands and see how Karel responds in the world. For example:

```c
void studentCode() {
    int moves = 0;
    while (front_is_clear()) {
        karel_move();
        moves++;
    }
    printf("Karel moved %d times until hitting a wall.\n", moves);
}
```

This code uses a variable and a loop to count how many times Karel moves forward before reaching a wall.

## Summary of Useful Functions

- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees left
- `karel_pick_beeper()` - Pick up a beeper at current position
- `karel_put_beeper()` - Place a beeper at current position
- `front_is_clear()` - Check if Karel can move forward
- `beepers_present()` - Check if there's a beeper at current position
- `beepers_in_bag()` - Check if Karel has beepers in bag
- `karel_get_x()`, `karel_get_y()` - Get current position coordinates

Try changing the code and observe the results. This is the best way to learn both C and how to control Karel!


## Using Conditionals: if, else if, else

In C, you can use `if`, `else if`, and `else` to perform different actions depending on the value of a variable. Here is a practical example with Karel:

```c
void studentCode() {
    int i = 2;
    if (i == 2) {
        karel_move();
        karel_move();
        printf("i is 2, Karel moved two times.\n");
    } else if (i == 3) {
        karel_move();
        karel_move();
        karel_move();
        printf("i is 3, Karel moved three times.\n");
    } else {
        karel_turn_left();
        printf("i is not 2 or 3, Karel turned left.\n");
    }
}
```

Try changing the value of `i` and see how Karel's behavior changes. This helps you understand how conditionals work in C!

The conditional statements allow you to control the flow of your program based on certain conditions. This is a fundamental concept in programming that lets you make decisions in your code.

The `else` statement is optional and can be used to define a default action if none of the previous conditions are met.

It is also possible to combine multiple conditions using logical operators like `&&` (and) and `||` (or). For example:

```c
void studentCode() {
    int i = 2;
    if (i == 2 || i == 3) {
        karel_move();
        printf("i is either 2 or 3, Karel moved once.\n");
    } else {
        karel_turn_left();
        printf("i is neither 2 nor 3, Karel turned left.\n");
    }
}
```

Try chaning the value of `i` to see how Karel's actions change based on the conditions.
### Switch Statement
In C, you can also use a `switch` statement to handle multiple conditions based on the value of a variable. This is useful when you have many specific cases to handle. Here's an example:
```c
void studentCode() {
    int i = 2;
    switch (i) {
        case 1:
            karel_move();
            printf("i is 1, Karel moved once.\n");
            break;
        case 2:     
            karel_move();
            karel_move();
            printf("i is 2, Karel moved twice.\n");
            break;
        case 3:
            karel_move();
            karel_move();
            karel_move();
            printf("i is 3, Karel moved three times.\n");
            break;
        default:
            karel_turn_left();
            printf("i is not 1, 2, or 3, Karel turned left.\n");
            break;
    }
}
```
In this example, Karel will perform different actions based on the value of `i`. The `switch` statement checks the value of `i` and executes the corresponding case block. The `break` statement is used to exit the switch block after executing a case. If none of the cases match, the `default` case is executed.  

