/* 
 * File:   AI.h
 * Author: Brian Ramirez
 * minimax algorithm modified from -> https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
 * 
 * Created on May 15, 2019, 11:10 AM
 */

#ifndef AI_H
#define AI_H

// Include libraries
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>
#include <algorithm>
#include "tictac.h"
using namespace std;

// Constant global chars for each player
const char ai_player = 'O', human = 'X';

class AI:Board{
    private:
        struct Move 
        { 
            int row, col; 
        };
    public:
        bool movesLeft(vector<vector <char>> &);
        int evaluation(vector<vector <char>> &);
        int minimax(vector<vector <char>> &, int, bool);
        Move bestMove(vector<vector <char>> &);
        void getHumanMove();
        void outputWinner(char);
        void play_AI();
        void AI_mode();
};

#endif /* AI_H */