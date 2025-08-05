# Solution: Grid Navigation with 2D Arrays

## Solution Explanation
This exercise demonstrates how to use 2D arrays for spatial representation and implement pathfinding algorithms. The solution combines grid representation with navigation logic to solve a complex routing problem.

## Complete Solution
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
    // Initialize all cells to EMPTY
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            map[i][j] = EMPTY;
        }
    }
    
    // Set up the world layout (row = y-1, col = x-1)
    map[0][0] = START;     // (1,1) - Start position
    map[0][2] = OBSTACLE;  // (3,1) - Obstacle
    map[0][4] = BEEPER;    // (5,1) - Beeper
    
    map[1][1] = OBSTACLE;  // (2,2) - Obstacle
    map[1][2] = OBSTACLE;  // (3,2) - Obstacle
    
    map[2][3] = OBSTACLE;  // (4,3) - Obstacle
    map[2][4] = BEEPER;    // (5,3) - Beeper
    
    map[3][0] = OBSTACLE;  // (1,4) - Obstacle
    map[3][4] = OBSTACLE;  // (5,4) - Obstacle
    
    map[4][1] = BEEPER;    // (2,5) - Beeper
    
    map[5][2] = OBSTACLE;  // (3,6) - Obstacle
    map[5][3] = OBSTACLE;  // (4,6) - Obstacle
    map[5][5] = GOAL;      // (6,6) - Goal
}

bool is_valid_position(int x, int y, int map[GRID_SIZE][GRID_SIZE]) {
    // Convert Karel coordinates (1-based) to array indices (0-based)
    int row = y - 1;
    int col = x - 1;
    
    // Check bounds
    if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
        return false;
    }
    
    // Check if position is not an obstacle
    return map[row][col] != OBSTACLE;
}

void turn_to_direction(int target_direction) {
    while (karel_get_direction() != target_direction) {
        karel_turn_left();
    }
}

void move_towards_target(int target_x, int target_y, int map[GRID_SIZE][GRID_SIZE]) {
    int current_x = karel_get_x();
    int current_y = karel_get_y();
    
    // If we're already at the target, do nothing
    if (current_x == target_x && current_y == target_y) {
        return;
    }
    
    // Try to move horizontally first
    if (current_x != target_x) {
        if (current_x < target_x) {
            // Need to move east
            if (is_valid_position(current_x + 1, current_y, map)) {
                turn_to_direction(0); // Face east
                karel_move();
                return;
            }
        } else {
            // Need to move west
            if (is_valid_position(current_x - 1, current_y, map)) {
                turn_to_direction(2); // Face west
                karel_move();
                return;
            }
        }
    }
    
    // Try to move vertically
    if (current_y != target_y) {
        if (current_y < target_y) {
            // Need to move north
            if (is_valid_position(current_x, current_y + 1, map)) {
                turn_to_direction(1); // Face north
                karel_move();
                return;
            }
        } else {
            // Need to move south
            if (is_valid_position(current_x, current_y - 1, map)) {
                turn_to_direction(3); // Face south
                karel_move();
                return;
            }
        }
    }
    
    // If direct movement is blocked, try alternative routes
    // This is a simple fallback - in real applications, use A* or BFS
    printf("Direct path blocked, trying alternative route...\n");
    
    // Try moving in other directions to get around obstacles
    int directions[] = {0, 1, 2, 3}; // East, North, West, South
    for (int i = 0; i < 4; i++) {
        int next_x = current_x;
        int next_y = current_y;
        
        switch (directions[i]) {
            case 0: next_x++; break; // East
            case 1: next_y++; break; // North
            case 2: next_x--; break; // West
            case 3: next_y--; break; // South
        }
        
        if (is_valid_position(next_x, next_y, map)) {
            turn_to_direction(directions[i]);
            karel_move();
            return;
        }
    }
    
    printf("Warning: No valid moves available!\n");
}

void navigate_to_beepers(int map[GRID_SIZE][GRID_SIZE]) {
    // Beeper positions: (5,1), (5,3), (2,5)
    int beeper_positions[][2] = {{5, 1}, {5, 3}, {2, 5}};
    int num_beepers = 3;
    
    // Visit each beeper position
    for (int i = 0; i < num_beepers; i++) {
        int target_x = beeper_positions[i][0];
        int target_y = beeper_positions[i][1];
        
        printf("Navigating to beeper at (%d, %d)\n", target_x, target_y);
        
        // Navigate to position
        int max_steps = 50; // Prevent infinite loops
        int steps = 0;
        while ((karel_get_x() != target_x || karel_get_y() != target_y) && steps < max_steps) {
            move_towards_target(target_x, target_y, map);
            steps++;
        }
        
        // Pick up beeper if present
        if (beepers_present()) {
            karel_pick_beeper();
            printf("Collected beeper at (%d, %d)!\n", karel_get_x(), karel_get_y());
            
            // Mark as visited in the map
            map[karel_get_y() - 1][karel_get_x() - 1] = VISITED;
        }
    }
    
    // Finally navigate to goal position (6, 6)
    printf("Navigating to goal position (6, 6)\n");
    int max_steps = 50;
    int steps = 0;
    while ((karel_get_x() != 6 || karel_get_y() != 6) && steps < max_steps) {
        move_towards_target(6, 6, map);
        steps++;
    }
    
    printf("Mission completed! Karel reached goal at (%d, %d)\n", karel_get_x(), karel_get_y());
}

void studentCode() {
    static bool missionComplete = false;
    static int world_map[GRID_SIZE][GRID_SIZE];
    static bool mapInitialized = false;
    
    if (!mapInitialized) {
        initialize_world_map(world_map);
        mapInitialized = true;
        printf("World map initialized!\n");
        print_map(world_map, karel_get_x(), karel_get_y());
    }
    
    if (!missionComplete) {
        navigate_to_beepers(world_map);
        missionComplete = true;
    }
}
```

## Advanced Solution: A* Pathfinding
For more sophisticated pathfinding:

```c
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
    int g_cost; // Distance from start
    int h_cost; // Heuristic distance to goal
    int f_cost; // g_cost + h_cost
    struct Node* parent;
} Node;

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool find_path_astar(int start_x, int start_y, int goal_x, int goal_y, 
                     int map[GRID_SIZE][GRID_SIZE], int path[][2], int* path_length) {
    // A* implementation
    Node open_set[GRID_SIZE * GRID_SIZE];
    Node closed_set[GRID_SIZE * GRID_SIZE];
    int open_count = 0, closed_count = 0;
    
    // Initialize start node
    Node start = {start_x, start_y, 0, 
                  manhattan_distance(start_x, start_y, goal_x, goal_y), 0, NULL};
    start.f_cost = start.g_cost + start.h_cost;
    open_set[open_count++] = start;
    
    while (open_count > 0) {
        // Find node with lowest f_cost
        int current_index = 0;
        for (int i = 1; i < open_count; i++) {
            if (open_set[i].f_cost < open_set[current_index].f_cost) {
                current_index = i;
            }
        }
        
        Node current = open_set[current_index];
        
        // Remove current from open set
        for (int i = current_index; i < open_count - 1; i++) {
            open_set[i] = open_set[i + 1];
        }
        open_count--;
        
        // Add to closed set
        closed_set[closed_count++] = current;
        
        // Check if we reached the goal
        if (current.x == goal_x && current.y == goal_y) {
            // Reconstruct path
            *path_length = 0;
            Node* node = &current;
            while (node != NULL) {
                path[*path_length][0] = node->x;
                path[*path_length][1] = node->y;
                (*path_length)++;
                node = node->parent;
            }
            
            // Reverse path to get start-to-goal order
            for (int i = 0; i < *path_length / 2; i++) {
                int temp_x = path[i][0];
                int temp_y = path[i][1];
                path[i][0] = path[*path_length - 1 - i][0];
                path[i][1] = path[*path_length - 1 - i][1];
                path[*path_length - 1 - i][0] = temp_x;
                path[*path_length - 1 - i][1] = temp_y;
            }
            
            return true;
        }
        
        // Check neighbors
        int neighbors[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int neighbor_x = current.x + neighbors[i][0];
            int neighbor_y = current.y + neighbors[i][1];
            
            if (!is_valid_position(neighbor_x, neighbor_y, map)) {
                continue;
            }
            
            // Check if in closed set
            bool in_closed = false;
            for (int j = 0; j < closed_count; j++) {
                if (closed_set[j].x == neighbor_x && closed_set[j].y == neighbor_y) {
                    in_closed = true;
                    break;
                }
            }
            if (in_closed) continue;
            
            int tentative_g = current.g_cost + 1;
            
            // Check if in open set
            int open_index = -1;
            for (int j = 0; j < open_count; j++) {
                if (open_set[j].x == neighbor_x && open_set[j].y == neighbor_y) {
                    open_index = j;
                    break;
                }
            }
            
            if (open_index == -1 || tentative_g < open_set[open_index].g_cost) {
                Node neighbor_node = {
                    neighbor_x, neighbor_y, tentative_g,
                    manhattan_distance(neighbor_x, neighbor_y, goal_x, goal_y),
                    0, &closed_set[closed_count - 1]
                };
                neighbor_node.f_cost = neighbor_node.g_cost + neighbor_node.h_cost;
                
                if (open_index == -1) {
                    open_set[open_count++] = neighbor_node;
                } else {
                    open_set[open_index] = neighbor_node;
                }
            }
        }
    }
    
    return false; // No path found
}
```

## Key Programming Concepts Demonstrated

### 1. 2D Array Declaration and Initialization
```c
int map[GRID_SIZE][GRID_SIZE];                    // Declaration
int map[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};    // Initialization
```

### 2. Row-Major Order Access
```c
// map[row][column] or map[y-1][x-1] for Karel coordinates
map[2][3] = 5;  // Row 2, Column 3
```

### 3. 2D Array as Function Parameter
```c
void process_map(int map[GRID_SIZE][GRID_SIZE]) {
    // Function receives a pointer to the first element
}
```

### 4. Coordinate System Conversion
```c
// Karel uses 1-based coordinates, arrays use 0-based
int array_row = karel_y - 1;
int array_col = karel_x - 1;
```

### 5. Nested Loops for 2D Traversal
```c
for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
        process_cell(map[row][col]);
    }
}
```

## Real-World Applications

### Game Development
```c
// Tile-based games
int game_map[MAP_HEIGHT][MAP_WIDTH];
// 0 = empty, 1 = wall, 2 = collectible, 3 = enemy
```

### Image Processing
```c
// Pixel manipulation
unsigned char image[HEIGHT][WIDTH][3]; // RGB values
// image[y][x][0] = red, image[y][x][1] = green, image[y][x][2] = blue
```

### Scientific Computing
```c
// Heat distribution simulation
double temperature[GRID_SIZE][GRID_SIZE];
// Calculate heat transfer between adjacent cells
```

### Geographic Information Systems
```c
// Elevation map
float elevation[MAP_HEIGHT][MAP_WIDTH];
// Calculate slope, watershed, visibility
```

This exercise provides a foundation for understanding spatial data structures and algorithms that are essential in many fields of computer science and engineering.
