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
    testingMinimax = false;

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
    std::cerr << "ehllo!" << std::endl;

    // Updates the board with the opponent's move depending on their side
    if (my_side == BLACK) {
        this->board->Board::doMove(opponentsMove, WHITE);
    }
    else {
        this->board->Board::doMove(opponentsMove, BLACK);
    }
    // If there are valid moves for our side to make...
    if (this->board->Board::hasMoves(my_side)) {
        std::cerr << "ehllo!" << std::endl;
        // Cycle through the squares on the board
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::cerr << i << " " << j << std::endl;
                // Create a move for our side to possibly make at square i,j
                Move *possible = new Move(i , j);
                // If this move is legal for our side to make, let's make it
                if (this->board->Board::checkMove(possible, my_side)) {
                    this->board->Board::doMove(possible, my_side);
                    // return this move
                    return possible;
                }
                else {
                    delete possible;
                }
            }
        }
    }

    return nullptr;
}
