// Enumerated class for the types of Tiles
enum class Tile {
    white,  // Player
    black,  // Computer
    empty,
    legal
};
 
// Structure for two ints that represent to x and y coordinate points of a tile
struct Loc {
    int x;
    int y;
};
 
// Structure for a direction used in the legal move and board flipping algorithms
struct Direction {
    int dx;
    int dy;
};
 
// Constant global variable that holds all the 4 cardinal + 4 diagonal directions 
const vector<Direction> dirs = {
    {-1, 0},    // Left
    {-1, -1},   // Up-left
    {0, -1},    // Up
    {1, -1},    // Up-right
    {1, 0},     // Right
    {1, 1},     // Down-right
    {0, 1},     // Down
    {-1, 1}     // Down-left
};
 
// Structure that contains a target location and a direction to that location--
// Used for "segments" of tiles to be flipped to the opposite color in the flipping algorithm
struct Dir_To_Loc {
    Direction d;
    Loc loc;
};