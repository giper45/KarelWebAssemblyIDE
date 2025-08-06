# Solution: Place Beepers

This exercise teaches inventory management and multiple exit conditions by requiring Karel to place beepers strategically while managing limited resources.
Here is the solution code:

### Solution with a loop and conditional
The easiest solution uses a loop that continues until Karel runs out of beepers. Inside the loop, Karel places a beeper and moves forward until he runs out of beepers.
```c
void studentCode()
{

    static bool missionComplete = false;
    static int beepersPlaced = 0;
        while (beepers_in_bag())
        {
            karel_put_beeper();
            beepersPlaced++;
            karel_move();

        }
        printf("Karel Completed!");

}

```


The simple solution starts with a while loop that continues as long as Karel has beepers in his bag. Inside the loop, Karel places a beeper and moves forward until he runs out of beepers.


## Introduce the if/else instruction
An alternative solution uses an if statement and a complete solution flag to check if Karel can place a beeper before doing so. This allows for more complex logic, such as checking if Karel is at a wall or has no beepers left.
```c
void studentCode()
{

    static bool missionComplete = false;
    static int beepersPlaced = 0;
        while (!missionComplete)
        {
            // Karel has beepers in bag 
            if (beepers_in_bag()) {
                karel_put_beeper();
                karel_move();
            }
            // Karel has completed beepers: stop and exit
            else {
                missionComplete = true; 
            }
        }
        printf("Karel Completed!");

}
``` 
This solution uses a while loop that continues until the `missionComplete` flag is set to true. Inside the loop, Karel checks if he has beepers in his bag before placing one and moving forward. If he runs out of beepers, the flag is set to true, ending the loop.

