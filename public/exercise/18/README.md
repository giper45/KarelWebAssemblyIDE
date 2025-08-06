# Karel the adder
In this exercise, you should navigate on a squared path and take all the beepers you find along the way.

![World Map](/exercise/18/world.png)

For each beeper you find, you should add one to a bidimensional array that represents the grid (10x8). The value at each position in the array should be the sum of all beepers found at that position.


For example, if you find a beeper at position (2,3), the value at `array[2][3]` should be 1. 

When you collect all the beepers, you should: 
* print the array to visualize the total number of beepers collected at each position.
* do the sum of the values in the first row and print it.
* do the sum of the values in the first column and print it.

Then, you should take these sums and should place a beeper at that position in the grid.

For example, if the sum of the first row is 5 and the sum of the first column is 3, you should place a beeper at position (3,5) in the grid.


### Steps:
1. Define and initialize a 2D array to store the counts of beepers at each position.
2. Traverse the grid, collecting beepers and updating the array.
3. After collecting all beepers, print the array.
4. Calculate the sum of the first row and first column.
5. Place a beeper at the position corresponding to the sums of the first row and column
6. Print the final position where the beeper was placed.