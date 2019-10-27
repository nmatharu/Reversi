// Computer player class that extends abstract base Player class
class Computer_player : public Player {
public: 
 
    // Structure that holds a specific potential move and the "value" associated with that move--
    // that is, the number of tiles the player would have after playing that move
    struct Move_Value {
        Loc move;
        int value;
    };
 
 
    // Returns whether or not a location is a corner space on a given board, used for the Computer
    // player as it prioritizes corner moves
    bool is_corner_move(Loc& move, Board& board) {
        return  (move.x == 0 && move.y == 0) || // top left
                (move.x == board.width()-1 && move.y == 0) || // top right
                (move.x == 0 && move.y == board.height()-1) || // bottom left
                (move.x == board.width() && move.y == board.height()-1); // botom right
    }
 
 
    // Method that returns the Loc of the highest value move from the vector of moves values
    Loc get_highest_val_move(vector<Move_Value> moves_values) {
 
        int highest_val = 0;
 
        // Find the highest value in the vector
        for(Move_Value mv : moves_values) {
            if(mv.value > highest_val)   highest_val = mv.value;
        }
 
        // Add all the moves that have that value into a "best moves" vector
        vector<Loc> best_moves;
        for(Move_Value mv : moves_values) {
            if(mv.value == highest_val) best_moves.push_back(mv.move);
        }
 
        // Select one of these best moves at random
        return best_moves[rand() % best_moves.size()];
    }
 
 
    // Method to get move from computer
    Loc get_move(Board& board, Tile& player_tile) 
    {
 
        // Our AI works around picking the "highest value" moves. The "highest value" refers to the 
        // move which will end up flipping the highest number of tiles for that player. 
        // The AI first prioritizes the highest value corner move, then just any corner move,
        // then the highest value legal move. If there is ever a tie between highest value moves,
        // the AI just selects one of them randomly.
 
        // Get all the legal moves
        vector<Loc> legal_moves = board.get_legal_moves(
                board.get_player_tiles(player_tile), player_tile);
 
        // Vectors for the values of moves and the moves themselves
        vector<Move_Value> moves_values;
        vector<Move_Value> corner_moves;  // one specifically for corner moves
 
        // For each legal move...
        for(Loc legal_move : legal_moves) {
 
            // Copy the current board into a temporary variable and set the tile to this legal move 
            // to see what happens (this will also call the flip method on the copied board)
            Board temp = board;
            temp.set(legal_move.x, legal_move.y, player_tile);
 
            // Count the number of tiles that the player would have after that legal move and add
            // the value and the move to the vector of Move_Values 
            int value = temp.count_tile(player_tile);
            moves_values.push_back({legal_move, value});
 
            // If the move happens to be a corner move, add it to the corner moves vector
            if(is_corner_move(legal_move, temp)) {
                corner_moves.push_back({legal_move, value});
            }
        }
 
        // If any of the legal moves are corner moves, return the one with the highest tile value
        if(corner_moves.size() > 0) {
            return get_highest_val_move(corner_moves);
        }
 
        // Just return the move with the highest tile value
        return get_highest_val_move(moves_values);
    }
 
 
    // Computer player destructor
    ~Computer_player() {
        // cout << "Computer_player destroyed.\n";
    }
};