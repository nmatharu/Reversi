// Abstract base class for players
class Player {
public: 
 
    // Method that gets the next move of the player
    virtual Loc get_move(Board& board, Tile& player_tile) = 0;
 
    // Virtual destructor
    virtual ~Player() { }
};