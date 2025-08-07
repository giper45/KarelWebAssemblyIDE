# Solution Karel Pointer Beeper

In this exercise, Karel should track the number of beepers along a straight path and update a variable through an `updateCounter` function.
The variable is defined in the `studentCode()` function.

We try to implement a function that updates a counter based on the number of beepers at Karel's current position.

```c
// NOT VALID SOMETING WRONG
void updateCounter(int counter)
{
    printf("In update counter\n");
    counter++;
}

void studentCode()
{
    int localCounter = 0;
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function
    for (int i = 0; i < 9; i++)
    {
        karel_move();
        if (beepers_present())
            updateCounter(localCounter);
    }

    printf("The number of beepers should be 4, localCounter=%d\n", localCounter);
}
```
Something strange happens here ... the `localCounter` variable is not updated as we expect. Do you know why?

### Passing Variables in C
This is because in C, when we pass a variable to a function, it is passed by value, meaning that the function receives a copy of the variable, not the original one.

Therefore, we need to use pointers. Pointers are variables that store the memory address of another variable. By passing a pointer to a function, we can modify the original variable.

```c
void updateCounter(int *counter)
{
    printf("In update counter\n");
    (*counter)++;
}   

```
Now you should modify the `studentCode()` function to pass the address of the `localCounter` variable to the `updateCounter` function. This is done using the `&` operator, which returns the address of a variable.

```c
void updateCounter(int *counter)
{
    printf("In update counter\n");
    (*counter)++;
}   


void studentCode()
{
    int localCounter = 0;
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function
    for (int i = 0; i < 9; i++)
    {
        karel_move();
        if (beepers_present())
            updateCounter(&localCounter);
    }

    printf("The number of beepers should be 4, localCounter=%d\n", localCounter);
}
```

### Print the addresses of the variables
The %p format specifier is used to print the address of a pointer variable in C. It is commonly used to display the memory address of a variable or a pointer.

You can use to verify the differences between the wrong and the correct implementation.
Try to run the following code:
```c
// NOT VALID SOMETING WRONG
void updateCounterWrong(int counter)
{
    printf("In update counter wrong\n");
    printf("Counter variable in the wrong function: %p\n", &counter);

    counter++;
}
// VALID 
void updateCounter(int *counter)
{
    printf("In update counter\n");
    printf("Counter variable in function: %p\n", counter);
    (*counter)++;
}   


void studentCode()
{
    int localCounter = 0;
    
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function
    for (int i = 0; i < 9; i++)
    {
        karel_move();
        if (beepers_present())
        {
            printf("Counter variable: %p\n", &localCounter);
            updateCounter(&localCounter);
            updateCounterWrong(localCounter);
        }
    }

    printf("The number of beepers should be 4, localCounter=%d\n", localCounter);
}
```

You can observe that while the localCounter address is the same of that of the `updateCounter` function, it is different in the `updateCounterWrong` function. This is because the `updateCounterWrong` function receives a **copy** )of the variable (passing variables by value), while the `updateCounter` function receives a pointer to the variable (passing variables by reference).

## Final Code
```c
// NOT VALID SOMETING WRONG
void updateCounterWrong(int counter)
{
    printf("In update counter wrong\n");
    printf("Counter variable in the wrong function: %p\n", &counter);

    counter++;
}
// VALID 
void updateCounter(int *counter)
{
    printf("In update counter\n");
    printf("Counter variable in function: %p\n", counter);
    (*counter)++;
}   


void studentCode()
{
    int localCounter = 0;
    
    // Update the local counter based on the number of beepers at Karel's current position
    // use a function
    for (int i = 0; i < 9; i++)
    {
        karel_move();
        if (beepers_present())
        {
            printf("Counter variable: %p\n", &localCounter);
            updateCounter(&localCounter);
            updateCounterWrong(localCounter);
        }
    }

    printf("The number of beepers should be 4, localCounter=%d\n", localCounter);
}
```
