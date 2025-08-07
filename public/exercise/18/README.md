# Grid Navigation with 2D Arrays

## Objective
Learn to use 2D arrays to represent a grid world and implement pathfinding algorithms to navigate through obstacles.


## Background
Two-dimensional arrays are essential for representing grid-based data like maps, game boards, and images. In this exercise, you'll create a map of Karel's world using a 2D array and implement intelligent navigation.

## Your Task
Karel needs to navigate through a 6x6 grid world with obstacles to collect all beepers. You'll:

1. **Create a 2D array** to represent the world state
2. **Map obstacles and beepers** in the array
3. **Implement pathfinding** to avoid obstacles
4. **Track visited cells** to avoid getting stuck
5. **Collect all beepers** efficiently

### World Layout
![World Map](/exercise/16/world.png)

```
Beepers in bag: 10
   1 2 3 4 5 6 7 8 9 10 
8: . . . . . . . . . . 
7: . . . . . . . . . . 
6: . . . . . . . . . . 
5: . B . . . . . . . . 
4: . . . . . . . . . . 
3: . . . . B . . . . . 
2: . . . . . . . . . . 
1: K . . . B . . . . . 

```

### Objectives
- Start at (1,1)
- Collect beepers at (5,1), (5,3), and (2,5)
- Reach the end goal at (6,6)
- Avoid all obstacles marked with #

## Programming Concepts You'll Learn

### 1. 2D Array Declaration
```c
#define GRID_SIZE 6
int world_map[GRID_SIZE][GRID_SIZE];
```

### 2. Cell Types
```c
enum CellType {
    EMPTY = 0,
    OBSTACLE = 1,
    BEEPER = 2,
    VISITED = 3,
    START = 4,
    GOAL = 5
};
```

### 3. 2D Array Initialization
```c
int world_map[6][6] = {
    {4, 0, 1, 0, 2, 0},
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 2, 0},
    {1, 0, 0, 0, 1, 0},
    {0, 2, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 5}
};
```

### 4. 2D Array Access
```c
// Access cell at row r, column c
int cell_value = world_map[r][c];
world_map[r][c] = new_value;
```

## Functions You'll Need to Implement

### 1. initialize_world_map()
```c
void initialize_world_map(int map[GRID_SIZE][GRID_SIZE]) {
    // Initialize the map with obstacles and beepers
}
```

### 2. is_valid_position()
```c
bool is_valid_position(int x, int y, int map[GRID_SIZE][GRID_SIZE]) {
    // Check if position is within bounds and not an obstacle
}
```

### 3. find_next_move()
```c
void find_next_move(int current_x, int current_y, int target_x, int target_y,
                   int map[GRID_SIZE][GRID_SIZE], int* next_x, int* next_y) {
    // Determine the best next move towards target
}
```

### 4. navigate_to_beepers()
```c
void navigate_to_beepers(int map[GRID_SIZE][GRID_SIZE]) {
    // Find and collect all beepers using the map
}
```

## Setup Information
- Karel starts at position (1,1)
- Karel has 0 beepers initially
- Obstacles are placed as vertical walls in the actual world
- Beepers are placed at the specified positions

## Success Criteria
- Karel collects all 3 beepers
- Karel avoids all obstacles
- Karel reaches the goal position (6,6)
- Your solution uses a 2D array to represent the world
- Your pathfinding algorithm successfully navigates around obstacles

## Code Structure Template
```c
#define GRID_SIZE 6

enum CellType {
    EMPTY = 0,
    OBSTACLE = 1,
    BEEPER = 2,
    VISITED = 3,
    START = 4,
    GOAL = 5
};

void initialize_world_map(int map[GRID_SIZE][GRID_SIZE]) {
    // Define the world layout
}

bool is_valid_position(int x, int y, int map[GRID_SIZE][GRID_SIZE]) {
    // Check bounds and obstacles
}

void print_map(int map[GRID_SIZE][GRID_SIZE]) {
    // Debug function to visualize the map
}

void navigate_to_beepers(int map[GRID_SIZE][GRID_SIZE]) {
    // Main navigation logic
}
```

## Algorithm Strategies

### 1. Breadth-First Search (BFS)
Find shortest path to each beeper:
```c
// Use a queue to explore positions level by level
// Guarantees shortest path in unweighted grids
```

### 2. A* Algorithm
More efficient pathfinding with heuristic:
```c
// Use Manhattan distance as heuristic
// Priority queue with f(n) = g(n) + h(n)
```

### 3. Simple Greedy Approach
Move towards target while avoiding obstacles:
```c
// Try to minimize distance to target
// Fall back if blocked
```

## Advanced Challenges

### 1. Dynamic Obstacles
```c
// Add moving obstacles that change position
void update_dynamic_obstacles(int map[GRID_SIZE][GRID_SIZE], int time_step);
```

### 2. Optimal Route Planning
```c
// Find the shortest route that visits all beepers
// This is a variant of the Traveling Salesman Problem
```

### 3. Multiple Goals
```c
// Prioritize beepers based on distance or value
int calculate_route_cost(int beeper_order[], int num_beepers);
```

## Why This Matters
2D arrays and grid navigation are fundamental in:
- **Game development** - Tile-based games, pathfinding for NPCs
- **Robotics** - SLAM (Simultaneous Localization and Mapping)
- **Image processing** - Pixel manipulation, computer vision
- **Geographic systems** - GPS navigation, route planning
- **Scientific computing** - Simulations on grids (weather, physics)

This exercise teaches spatial algorithms and data structures that are essential for many real-world applications involving 2D data representation and navigation.
