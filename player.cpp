// Julian's small change!

#include "player.hpp"
#include <iostream>
#include <string>

/* This is a tiny change committed by Ashima :)) */

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

    // Create a board
    board = new Board();
    // Sets my_side to the input side
    my_side = side;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // Holds side of the opponent
    Side other_side;
    // Calculate side of the opponent
    if (my_side == BLACK) {
        other_side = WHITE;
    }
    else {
        other_side = BLACK;
    }
    // Now perform the opponent's move on the board
    this->board->Board::doMove(opponentsMove, other_side);
    if (testingMinimax) {
        // If there are valid moves for our side to make...
        if (this->board->Board::hasMoves(my_side)) {
            // Initialize the best_score as an arbitrary negative score so that
            // the first legal move definitely becomes the best
            int best_score = -3000;
            // Create a placeholder for the best move
            Move *best = nullptr;
            // Create a placeholder for our current score
            int our_score;
            // Cycle through the squares on the board
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    // Create a move for our side to possibly make at square i,j
                    Move *possible1 = new Move(i, j);
                    // Check if this move is legal on the current board
                    if (this->board->Board::checkMove(possible1, my_side)) {
                        // Calculate the score of this move on the current board
                        our_score = this->board->Board::score(possible1, my_side);
                        // We need to create a copy of the board that represents
                        // the board after this possible move. We will check the
                        // opponent's response move on this board
                        Board *copy = this->board->Board::copy();
                        copy->Board::doMove(possible1, my_side);
                        // We will keep track of the opponent's optimal score
                        // in response to ours according to our heuristic
                        int their_score = -3000;
                        // Cycle through to find a possible move for other_side
                        for (int k = 0; k < 8; k++) {
                            for (int l = 0; l < 8; l++) {
                                // Create a move at this square
                                Move *possible2 = new Move(k, l);
                                // If this move is possible for the other side on
                                // the copy board..
                                if (copy->Board::checkMove(possible2,
                                    other_side)) {
                                    // Check if this move for the other side is
                                    // better than any other that we have calculated
                                    // in response to our i,j move.
                                    if (copy->Board::score(possible2,
                                        other_side) > their_score) {
                                        // If it is, we set their_score to their new
                                        // optimal score, and same for optimal move
                                        their_score = copy->Board::score(possible2,
                                            other_side);
                                    }
                                }
                                delete possible2;
                            }
                        }
                        delete copy;

                        // Now we have computed their best move in response to our
                        // move at i,j. In order to mamximize our minimum gain, we
                        // should compute the largest difference between our score
                        // increase and opponent's most optimal score increase.
                        if (our_score - their_score > best_score) {
                            // Set best score to the best difference so far
                            best_score = our_score - their_score;
                            // The move associated with this best score is saved in
                            // possible1, so we assign it to Move *best
                            best = possible1;
                        }
                    }
                    // If the move is not possible, delete it
                    else {
                        delete possible1;
                    }
                }
            }
            // Do the best move
            this->board->Board::doMove(best, my_side);
            return best;
        }

        return nullptr;
    }
    // when testingMinimax is false:
    else {
        // If there are valid moves for our side to make...
        if (this->board->Board::hasMoves(my_side)) {
            // Initialize the best_score as an arbitrary negative score so that
            // the first legal move definitely becomes the best
            int best_score = -3000;
            // Create a placeholder for the best move
            Move *best = nullptr;
            // Cycle through the squares on the board
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    // Create a move for our side to possibly make at square i,j
                    Move *possible = new Move(i , j);
                    // If this move is legal for our side to make, let's make it
                    if (this->board->Board::checkMove(possible, my_side)) {
                        if (this->board->Board::score(possible, my_side)
                        > best_score) {
                            best_score = this->board->Board::score(possible, my_side);
                            best = possible;
                        }
                    }
                    else {
                        delete possible;
                    }
                }
            }
            this->board->Board::doMove(best, my_side);
            return best;
        }

        return nullptr;
    }
}
