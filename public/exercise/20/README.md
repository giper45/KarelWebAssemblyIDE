# Karel the calculator
In this exercise, Karel should implement several mathematical functions on collected information about beepers.



This exercise introduces you to the concept of `structs` in C, which allow you to group related data together. You will create a struct to hold the information about the beepers collected by Karel.

Here is a simple example of how to define a struct in C:

```c
struct BeeperInfo {
    int numBeepersFirstRow;
    int numBeepersSecondRow;
    int sumBeepers;
    double averageBeepers;
};
```

Through this syntax, you define a new type called `BeeperInfo` that contains four fields: `numBeepersFirstRow`, `numBeepersSecondRow`, `sumBeepers`, and `averageBeepers`. You can then create variables of this type to hold the information about the beepers collected by Karel.
The difference between a struct and an array is that a struct can hold different types of data, while an array holds only one type of data. In this case, the `BeeperInfo` struct holds integers and doubles, which is not possible with a simple array.

You can create a variable of this type like this:

```c
struct BeeperInfo beeperInfo;
```
You can access and modify the fields of the struct using the dot operator:

```c
beeperInfo.numBeepersFirstRow = 5;
beeperInfo.sumBeepers = 10.5;
```

You can also create a `typedef` for the struct to make it easier to use:

```c
typedef struct {
    int numBeepersFirstRow;
    int numBeepersSecondRow;
    double sumBeepers;
    double averageBeepers;
} BeeperInfo;
```

When you use this syntax, it is easier to create variables of this type:

```c
BeeperInfo beeperInfo;
```

## Goal 
Now comes to the main part of the exercise. 
Karel should collect the number of beepers in the first and second rows, calculate the sum and average of the beepers, and store this information in a `BeeperInfo` struct.






