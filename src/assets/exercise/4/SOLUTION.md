# Solution: Collect All Beepers

## Solution Explanation
This exercise requires systematic world exploration combined with beeper detection and collection.

## Complete Solution
```c
void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    static int beepersCollected = 0;
    const int totalBeepers = 6;
    
    if (beepersCollected >= totalBeepers) {
        printf("Mission Complete! All beepers collected!");
        return;
    }
    
    if (timeSec - lastMoveTime > 0.6) {
        // Always check for beepers first
        if (beepers_present()) {
            karel_pick_beeper();
            beepersCollected++;
            printf("Found beeper! Total: %d/%d", beepersCollected, totalBeepers);
        }
        
        // Row-by-row sweep pattern
        if (facing_east() && front_is_clear()) {
            karel_move();
        } else if (facing_east() && !front_is_clear()) {
            // End of eastward row
            karel_turn_left(); // Face north
            if (front_is_clear()) {
                karel_move(); // Move up one row
                karel_turn_left(); // Now face west
            }
        } else if (facing_west() && front_is_clear()) {
            karel_move();
        } else if (facing_west() && !front_is_clear()) {
            // End of westward row
            while (!facing_north()) karel_turn_left();
            if (front_is_clear()) {
                karel_move(); // Move up one row
                while (!facing_east()) karel_turn_left(); // Face east
            }
        } else {
            // Reset to eastward direction
            while (!facing_east()) karel_turn_left();
        }
        
        lastMoveTime = timeSec;
    }
}
```

## Strategy: Row-by-Row Sweep
1. **Eastward Movement**: Move east across each row
2. **Row Transition**: When hitting east wall, move north and face west
3. **Westward Movement**: Move west across the row
4. **Row Transition**: When hitting west wall, move north and face east
5. **Beeper Collection**: Always check for beepers at each position

## Key Concepts
- **Systematic Search**: Complete coverage using a predictable pattern
- **State Tracking**: Count collected beepers to know when finished
- **Conditional Collection**: Check `beepers_present()` before pickup
- **Direction Management**: Use facing functions to maintain search pattern

## Alternative Patterns
- **Spiral Pattern**: Start from outside and spiral inward
- **Column-by-Column**: Vertical sweeps instead of horizontal
- **Random Walk**: Less efficient but simpler to implement

## Efficiency Considerations
The row-by-row pattern ensures every location is visited exactly once, making it optimal for complete world coverage.
