// Human player class that extends the abstract base class
class Human_player : public Player {
public: 
 
    // Re-use of Navpreet's method from his Assignment 3 to clean up strings
    // Cleans up the trailing and leading whitespace from a string
    string clean_up_string(const string& s) {
 
        // Uses the .find_first_not_of and .find_last_not_of methods to get the first and last positions of the
        // string that is not a space and puts those positions into size_t objects
        size_t first_non_space_pos = s.find_first_not_of(" ");
        size_t last_non_space_pos = s.find_last_not_of(" ");
 
        // If the first position size_t object is a string::npos, that means it didn't find a whitespace and that
        // we should start our "clean" string from the start, or at index 0
        // The same is true for the last position being string::npos-- it should be the index of the last character
        if(first_non_space_pos == string::npos) first_non_space_pos = 0;
        if(last_non_space_pos == string::npos)  last_non_space_pos = s.length() - 1;
 
        // size_t object that will hold our substring length because .substr takes the first position and num of 
        // characters rather than the first and last position. We need to add 1 because it is the number of characters
        // rather than the index
        size_t substr_length = last_non_space_pos - first_non_space_pos + 1;
 
        // Get's the substring "clean string" from the input string and returns it
        return s.substr(first_non_space_pos, substr_length);
    }
 
 
    // Method that checks whether or not a user's input is valid given the list of legal moves
    bool valid_input(const string& s, const vector<Loc>& legal_moves) {
 
        // If the user's input is not exactly 2 characters, it is not valid
        if(s.size() != 2)   {
            cout << "   Inputs must be in the format <letter><number> (ex. \"a4\").\n";
            return false;
        }
 
        // Get the first and second characters which equate to the row and column number
        char c1 = s.at(0);
        char c2 = s.at(1);
 
        // If their inputted move is one that is on the list of legal moves, return true
        for(Loc loc : legal_moves) {
            if(loc.x == label_to_x(c2) && loc.y == label_to_y(c1))  return true;
        }
 
        // Else prompt them that their move need to be one of the legal moves.
        cout << "   Your move needs to be one of the legal moves.\n";
        return false;
    }
 
 
    // Method to get move from user
    Loc get_move(Board& board, Tile& player_tile) {
     
        // Gets the player's list of legal moves
        vector<Loc> legal_moves = board.get_legal_moves(
                board.get_player_tiles(player_tile), player_tile);
 
        string s;
 
        // Prompts them to enter a move, getting the input and cleaning it up,
        // and asks them for another input if their entered move was not valid
        do {
            cout << "   Please enter a move:\n";
            getline(cin, s);
            s = clean_up_string(s);
        } while (!valid_input(s, legal_moves));
 
        // Return their entered move as a Location object
        return {label_to_x(s.at(1)), label_to_y(s.at(0))};
    }
 
 
    // Human player destructor
    ~Human_player() {
        // cout << "Human_player destroyed.\n";
    }
};