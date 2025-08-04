# Karel Binary Search Algorithm

## Objective
Implement the binary search algorithm using Karel to efficiently find specific beeper arrangements in a sorted world layout.

## Background
Binary search is an efficient algorithm for finding items in sorted data:
- **Prerequisite**: Data must be sorted
- **Time Complexity**: O(log n) - much faster than linear search
- **Strategy**: Repeatedly divide search space in half
- **Karel Application**: Search for beepers arranged in sorted patterns

## Your Task
1. Understand how binary search works with Karel's coordinate system
2. Implement binary search to find specific beeper positions
3. Compare efficiency with linear search from previous exercise
4. Handle edge cases and boundary conditions
5. Visualize the search process as Karel moves

## Key Concepts
- **Sorted Data**: Beepers arranged in ascending order by coordinate
- **Search Space**: Current range being examined (left, right bounds)
- **Midpoint Calculation**: `mid = (left + right) / 2`
- **Comparison**: Compare target with middle element
- **Space Reduction**: Eliminate half the search space each iteration

## Algorithm Steps
1. Set left boundary to start position, right boundary to end
2. Calculate midpoint position
3. Move Karel to midpoint and check for target
4. If found: return success
5. If target is smaller: search left half
6. If target is larger: search right half
7. Repeat until found or search space exhausted

## Karel Binary Search Applications
- Find specific beeper in sorted row/column
- Locate optimal pickup points
- Search for gaps in beeper patterns
- Navigate efficiently through organized world layouts

## Efficiency Comparison
- **Linear Search**: Checks every position (up to n steps)
- **Binary Search**: Halves search space each time (up to log n steps)
- **Example**: Finding item in 1000 positions: Linear=1000 steps, Binary=10 steps

## Tips
- Ensure data is sorted before applying binary search
- Handle integer division carefully for midpoint calculation
- Test with both even and odd-sized search spaces
- Visualize Karel's movement to understand the algorithm
- Compare step counts with linear search to see efficiency gains
