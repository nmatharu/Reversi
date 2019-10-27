#include <iostream>
#include <cassert>
#include <string>
#include <vector>

// Solely used for providing a delay for UX
#include <chrono>
#include <thread>

using namespace std;

// constant variables
#include "constant.h"

// tile object
#include "tile.h"

// helper functions
#include "helper.h"

// classes
#include "board.h"
#include "abstract_player.h"
#include "human_player.h"
#include "computer_player.h"

void game_loop() {

    // Creates a Board object and sets it size to 8x8 (we encourage you to try any even-numbered
    // sizes up to 42x30, they're very interesting to look at and play with!)
    Board board(8, 8);

    // Sets the random seed
    srand(time(NULL));

    // Creates pointers to abstract Player objects which we use to
    // point to new Human and Computer player objects
    Player* p1 = new Human_player();
    Player* p2 = new Computer_player();

    // The current player tile starts with white (YELLOW in our graphic)
    Tile curr_player = Tile::white;

    // Game loop that repeats as long as the game can continue (there are legal moves that can be played)
    while(board.game_can_continue()) {

        // Update the legal moves and display it to the current player
        board.update_legal_moves(curr_player);
        board.display();

        // Delay the board so player's can see what the computer actually does and for a more
        // natural user experience
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MILLISECONDS));

        if(curr_player == Tile::white) {

            cout << yellow_bold << "\n   It is YEL's turn:\n" << reset_color;

            // Get the list of legal moves for the current player
            vector<Loc> legal_moves = board.get_legal_moves(
                board.get_player_tiles(curr_player), curr_player);

            // If they have at least one legal move...
            if(legal_moves.size() != 0) {

                // Get their move by calling their get_move method, and set their tile on the board
                // to the move they selected (which will call the flip method to handle the sequence
                // of flipping colors appropriately)
                Loc move = p1->get_move(board, curr_player);
                board.set(move.x, move.y, curr_player);

            } else {

                // Else, simply state that the player has not available moves
                cout << "   YEL has no available moves.\n";
            }

            // Switch the current player tile color
            curr_player = Tile::black;

        } else if(curr_player == Tile::black) {

            cout << red_bold << "\n   It is RED's turn:\n" << reset_color;

            // Get the list of legal moves for the current player
            vector<Loc> legal_moves = board.get_legal_moves(
                board.get_player_tiles(curr_player), curr_player);

            // If they have at least one legal move...
            if(legal_moves.size() != 0) {

                // Get their move by calling their get_move method, and set their tile on the board
                // to the move they selected (which will call the flip method to handle the sequence
                // of flipping colors appropriately)
                Loc move = p2->get_move(board, curr_player);
                board.set(move.x, move.y, curr_player);

            } else {

                // Else, simply state that the player has not available moves
                cout << "   RED has no available moves.\n";
            }

            // Switch the current player tile color
            curr_player = Tile::white;
        }
    }

    // --- The game has ended ---

    // Display the final board state
    board.display();

    // Count the number of final tiles for each player
    int p1_count = board.count_tile(Tile::white);
    int p2_count = board.count_tile(Tile::black);

    // If p1 beat p2, print out the winner with the appropriate color and counts,
    // vice versa if p2 beat p1, and if they were the same, print out that there was a tie
    if(p1_count > p2_count) {

        cout << yellow_bold << "\n   YEL won with " << p1_count <<
        " to " << red_bold << p2_count << yellow_bold << " tiles!\n" << reset_color;

    } else if(p2_count > p1_count) {

        cout << red_bold << "\n   RED won with " << p2_count <<
        " to " << yellow_bold << p1_count << red_bold << " tiles!\n" << reset_color;

    } else {

        cout << white_bold << "YEL and RED both tied with " << p1_count << " to "
            << p2_count << " points!\n" << reset_color;
    }

    cout << "\n\n";

    // Deallocate the memory used by the two Player objects
    delete p1;
    delete p2;
}


// Function that handles calling the game loop and allowing the player to play again
void play()
{
    bool play = true;
    string response;

    // Continually play games until the player doesn't want to play anymore
    while (play) {

        // Play through a game of Reversi
        game_loop();

        bool valid_response = false;

        // Response must be valid to decide if player wants to play again
        while (!valid_response) {

            // Get response from player and clean up their input
            cout << "Would you like to play again? Yes or No.\n";
            getline(cin, response);
            response = clean_input(response);

            // If they respond yes, "play" remains true and we exit the loop to play again
            if (response == "yes") {
                valid_response = true;
            } else if (response == "no") {

                // If they respond no, "play" is set to false, we exit the loop, and the play loop
                // does not iterate and we exit the program
                valid_response = true;
                play = false;
                cout << "Thanks for playing!\n\n";

            } else {

                // If they gave us an invalid response, the flag remains false to prompt them for
                // another response
                cout << "Invalid Response.\n";
                valid_response = false;
            }
        }
    }
}

int main() {

    // Play Reversi!
    play();
}
