# Solution: Check Every Box

With the while loop the solution is straightforward. Karel will move forward as long as there are no beepers present and the path is clear. When a beeper is found, it will be removed.
```c
void studentCode() {
    while(front_is_clear())
    {
        karel_move();
        if (beepers_present())
        {
            printf("Take a beeper\n");
            karel_pick_beeper();
        }
    }
 
}

```


For the loop solution, we will use a for loop to iterate through the squares. The loop will run a fixed number of times, checking each square for beepers and removing them if present.
We start using the following skeleton:

```c
#define WORLD_WIDTH 10

void studentCode() {
    static bool is_complete = false; 
    if (!is_complete) {
        for (int i = 0; i < WORLD_WIDTH; i++)
        {
            karel_move();
            
        }
        is_complete = true;
    }
    
}
```

We see Karel moving forward 10 times, but we need to add the logic to check for beepers and remove them. We can do this by adding an if statement inside the loop:

```c
#define WORLD_WIDTH 10
void studentCode() {
    static bool is_complete = false; 
    if (!is_complete) {
        for (int i = 0; i < WORLD_WIDTH; i++)
        {
            karel_move();
            if (beepers_present())
            {
                printf("Take a beeper\n");
                karel_pick_beeper();
            }
        }
        is_complete = true;
    }
    
}
```

Now Karel will move forward 10 times, checking each square for beepers and removing them if present. The `is_complete` flag ensures that the loop runs only once.
