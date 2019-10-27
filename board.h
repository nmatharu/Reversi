// Class for Reversi board
class Board {
private: 
 
    // 2D vector that represents the columns and rows of the board
    vector<vector<Tile>> board;
 
public: 
    Board(int w, int h) :
    board(h) {
 
        // Make sure that the board's width/height is at least 2 and are even numbers 
        // to allow for proper placement of the Othello configuration 
        assert(w > 1 && h > 1 && (w % 2 == 0) && (h % 2 == 0));
 
        // max width 42, max height 30
        // (could be arbitrarily large, but these are the limits for the character labels
        // on the x and y axes)
        assert(w <= 42 && h <= 30);
 
        // Set all tiles to empty spaces
        for(int i = 0; i < board.size(); i++) {
            board[i] = vector<Tile>(w, Tile::empty);
        }
 
        // Set middle spaces to Othello configuration
        board[h/2-1][w/2-1] = Tile::white;
        board[h/2][w/2] = Tile::white;
        board[h/2][w/2-1] = Tile::black;
        board[h/2-1][w/2] = Tile::black;
    }
 
 
    // Getters for width and height of board
    int width() const { return board[0].size(); }
    int height() const { return board.size(); }
 
 
    // Check if entered values are on the board
    bool on_board(int x, int y) const
    {
        return (x >= 0 && x < width() &&
                y >= 0 && y < height());
    }
 
 
    // Method that flips the pieces given an input location (x and y ints), and the type
    // of tile that pieces on the board will be flipped to
    void flip_pieces(int x, int y, const Tile& t) {
 
        // Vector that holds the aforementioned Dir_To_Loc objects that will hold segments
        // of the board that will be flipped to the appropriate tile color
        vector<Dir_To_Loc> flip_segments;
 
        // Loop through all the 8 directions
        for(Direction d : dirs) {
 
            // Get the 1st position right after the position itself (we don't need to check itself)
            Loc pos = {x + d.dx, y + d.dy};
 
            // Loop through will moving the pos in the direction specified and remaining on the board
            while(on_board(pos.x, pos.y)) {
 
                Tile curr = board[pos.y][pos.x];
 
                // If we find the player's own tile, that means there is a segment of tiles between
                // the current pos and the starting position that will end up being flipped to ALL
                // of that player's tile color-- this is regardless of whether or not an enemy tile
                // was found inbetween those pieces; they will end up being the same color anyways
                if(curr == t) {
                    flip_segments.push_back({d, pos});
                }
 
                // If we run into an empty/legal tile, no flip segment can be made and we break this
                // iteration of the loop
                if(curr == Tile::empty || curr == Tile::legal) {
                    break;
                }
 
                // Update the position given the direction
                pos.x += d.dx;
                pos.y += d.dy;
            }
        }
 
        // Once we have found all the segments, we iterate through all the objects and flip
        // all of pieces within all of the segments to the player's color
        for(Dir_To_Loc flip_seg : flip_segments) {
 
            Direction d = flip_seg.d;
 
            // Location to flip TO
            Loc loc = flip_seg.loc;
 
            // Location to flip FROM
            Loc pos = {x, y};
 
            // Reached end of segment
            bool reached_eos = false;
 
            // Loop through in the direction of that segment until the ending segment point is
            // reached, changing the tile color along the way
            while(!reached_eos) {
 
                board[pos.y][pos.x] = t;
 
                if(pos.x == loc.x && pos.y == loc.y)    reached_eos = true;
 
                pos.x += d.dx;
                pos.y += d.dy;
            }
        }
    }
 
 
    // Get a specific tile on the board
    Tile get_tile(int x, int y) const
    {
        assert(on_board(x,y));
        return board[y][x];
    }
 
 
    // Setter for a specific tile
    void set(int x, int y, const Tile& t)
    {
        assert(on_board(x, y));
        board[y][x] = t;
 
        // If the tile that is being set is either white/back (a player tile), we want
        // to call the flip method to handle all the pieces that will be flipped from the set tile
        if(t == Tile::white || t == Tile::black)    flip_pieces(x, y, t);
    }
 
 
    // Displays all of the board graphics
    void display_board() {
        cout << "\n\n    ";
 
        // Print x-axis labels across the top
        for(int i = 0; i < width(); i++) {
            cout << " " << x_to_label(i);
        }
 
        // Print horizontal bars and top-left/top-right corners across the top
        cout << "\n   " << tl_corner;
        for(int i = 0; i < width(); i++) {
            cout << horz_bar << horz_bar;
        }
        cout << horz_bar << tr_corner;
 
        cout << "\n";
 
        // Print vertical bars, y-axis labels, and the tiles of the board itself
        //  with different symbols for the 4 different types of tiles
        for(int i = 0; i < height(); i++) {
            cout << " " << y_to_label(i) << " " << vert_bar;
            for(int j = 0; j < width(); j++) {
                cout << " ";
                switch(board[i][j]) {
                    case Tile::white:   cout << yellow_bold << "■" << reset_color;
                                        break;
                    case Tile::black:   cout << red_bold << "■" << reset_color;
                                        break;
                    case Tile::empty:   cout << cyan << "•" << reset_color;
                                        break;
                    case Tile::legal:   cout << white_bold << "○" << reset_color;
                                        break;
                }   
            }
            cout << " " << vert_bar << " " << y_to_label(i) << "\n";
        }
 
        // Print horizontal bars and bottom-left/bottom-right corners across the bottom
        cout << "   " << bl_corner;
        for(int i = 0; i < width(); i++) {
            cout << horz_bar << horz_bar;
        }
        cout << horz_bar << br_corner;
 
        // Print x-axis labels across the bottom
        cout << "\n    ";
        for(int i = 0; i < width(); i++) {
            cout << " " << x_to_label(i);
        }
        cout << "\n\n";
    }
 
 
    // Method that counts the number of tiles of a certain type on the board
    int count_tile(const Tile& t) {
        int count = 0;
        for(int i = 0; i < height(); i++) {
            for(int j = 0; j < width(); j++) {
                if(board[i][j] == t)    count++;
            }
        }
        return count;
    } 
 
 
    // Method that prints the score for each of the players
    void display_scores() {
        cout << yellow_bold << "   YEL has " << count_tile(Tile::white) << " tiles.\n" << reset_color;
        cout << red_bold << "   RED has " << count_tile(Tile::black) << " tiles.\n" << reset_color;
    }
 
 
    // Calls the two specific display methods
    void display() {
        display_board();
        display_scores();
    }
 
 
    // Method that returns the list of Locations of legal moves for a certain player
    vector<Loc> get_legal_moves(vector<Loc> locs, Tile player_tile) {
 
        vector<Loc> legal_moves;
 
        // Specifies the enemy tile type
        Tile enemy_tile;
        if(player_tile == Tile::white) {
            enemy_tile = Tile::black;   
        } else if (player_tile == Tile::black) {
            enemy_tile = Tile::white;
        }
 
        // For all the current tiles that that player has on the board..
        for(Loc loc : locs) {
 
            // Iterate through the 8 directions
            for(Direction d : dirs) {
 
                // Flag that is set to true once an enemy tile has been seen (stays true once we see
                // at least one enemy)
                bool has_seen_enemy = false;
 
                // Flag that is set to true when an enemy tile was immediately seen (is only true
                // if an enemy is seen in this iteration or the previous iteration)
                bool was_enemy = false;
 
                Loc pos = loc;
 
                // Iterate the position with the current direction while it remains on the board
                while(on_board(pos.x, pos.y)) {
 
                    Tile curr = board[pos.y][pos.x];
 
                    // If the current tile is an enemy tile, set both flags to true
                    if(curr == enemy_tile) {
                        was_enemy = true;
                        has_seen_enemy = true;
 
                    } else if (curr == player_tile) {
 
                        // If we see a player tile, the immediate enemy flag is set to false
                        was_enemy = false;
 
                    } else {
 
                        // If we see an empty/legal move tile, that means this is a possibility
                        // for a legal move tile:
 
                        // If we haven't already seen an enemy tile, that means that there is no 
                        // way to sandwich two player pieces around an enemy piece so this cannot
                        // be a legal move and we break this iteration
                        if(!has_seen_enemy) {
                            break;
                        } else if(was_enemy) {
 
                            // If we HAVE just seen an enemy in the previous iteration, then that means
                            // we can sandwich two player pieces between this enemy piece and it is
                            // a legal move, so add it to the vector and break
                            legal_moves.push_back({pos.x, pos.y});
                            break;
                        } else {
 
                            // Else, set the immediate enemy seen flag to false
                            was_enemy = false;
                        }
                    }
 
                    // Update the position given the direction
                    pos.x += d.dx;
                    pos.y += d.dy;
                }
            }
        }
 
        return legal_moves;
    }
 
 
    // Gets the list of Locations of player tiles on the board
    vector<Loc> get_player_tiles(Tile player_tile) {
 
        vector<Loc> locs;
        for(int i = 0; i < height(); i++) {
            for(int j = 0; j < width(); j++) {
                if(board[i][j] == player_tile) {
 
                    // If the current tile is a player tile, add it to the vector
                    // {j, i} because the first index in the 2D vector is for the column
                    // but i and j represent the x and y coordinates, respectively
                    locs.push_back({j, i});
                } 
            }
        }
        return locs;
    }
 
 
    // Method which updates the legal move tiles on the board given the current player
    void update_legal_moves(Tile player_tile) {
 
        assert(player_tile == Tile::white || player_tile == Tile::black);
 
        // Gets the list of player tiles which we use to calculate the list of legal moves 
        // that are possible from each of these starting positions
        vector<Loc> locs = get_player_tiles(player_tile);
 
        // Clear the board of any currently legal tiles
        for(int i = 0; i < height(); i++) {
            for(int j = 0; j < width(); j++) {
                if(board[i][j] ==  Tile::legal) {
                    board[i][j] = Tile::empty;
                }
            }
        }
 
        // Get the list of legal tiles given the current tile locations of the player and their tile color
        vector<Loc> legal_moves = get_legal_moves(locs, player_tile);
 
        // Set the returned list of legal moves to the legal move tile
        for(Loc loc : legal_moves) {
            board[loc.y][loc.x] = Tile::legal;
        }
    }
 
 
    // Method that returns whether or not the game can continue, which only returns false when
    // the sum of legal moves for both players is 0 or less-- both players can't do anything
    bool game_can_continue() {
        int total_legal_moves = 0;
        total_legal_moves += get_legal_moves(get_player_tiles(Tile::white), Tile::white).size();
        total_legal_moves += get_legal_moves(get_player_tiles(Tile::black), Tile::black).size();
        return total_legal_moves > 0;
    }
 
 
    // Board destructor
    ~Board()
    {
        // cout << "Board destroyed.\n";
    }
 
};