/* 
 * File:   AI.cpp
 * Author: Brian Ramirez
 *
 * Created on May 29, 2019, 11:51 AM
 */

// Include libraries
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include "AI.h"
using namespace std;

/*
 * This function takes in the board and 
 * looks for empty spaces or the available
 * moves.
 *  
 * @param b -> the 2d board vector
 * @return 
 */
bool AI::movesLeft(vector<vector <char>> &b){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(b[i][j]==' ')
                return true;
        }
    }
    return false;
}

/*
 * The evaluation function that returns +10 or -10
 * to score the board. If the AI wins the function returns
 * +10 and -10 for the human player.
 *  
 * @param b -> the 2d board vector
 * @return 
 */
int AI::evaluation(vector<vector <char>> &b){
    // Check rows for X or O
    for(int row=0; row<3; row++){
        if(b[row][0]==b[row][1] && b[row][1]==b[row][2]){
            if(b[row][0] == ai_player)
                return +10;
            else if(b[row][0] == human)
                return -10; 
        }
    }
    
    //Check columns for X or O
    for(int col=0;col<3;col++){
        if(b[0][col]==b[1][col] && b[1][col]==b[2][col]){
            if(b[0][col] == ai_player)
                return +10;
            else if(b[0][col] == human)
                return -10;
        }
            
    }
    // Check diagonals for X or O 
    if(b[0][0]==b[1][1] && b[1][1]==b[2][2]){
        if(b[0][0] == ai_player)
            return +10;
        else if(b[0][0] == human)
            return -10;
    }
    if(b[0][2]==b[1][1] && b[1][1]==b[2][0]){
        if(b[0][2] == ai_player)
            return +10;
        else if(b[0][2] == human)
            return -10;
    }
    
    return 0;
}

/*
 * The minimax algorithm that recursively calls itself
 * for each player's move until the computer has
 * seen all possible moves.
 *  
 * @param b      -> the 2d board vector
 * @param depth  -> the current depth level of recursive calls
 * @param isMax  -> boolean to decide whether it is the maximizing player
 * @return       -> returns the value of the board
 */
int AI::minimax(vector<vector <char>> &b, int depth, bool isMax){
    int score = evaluation(b);
  
    // If Maximizer has won the game return his/her 
    // evaluated score 
    if (score == 10) 
        return (score-depth); 
  
    // If Minimizer has won the game return his/her 
    // evaluated score 
    if (score == -10) 
        return (score+depth); 
  
    // If there are no more moves and no winner then 
    // it is a tie 
    if (movesLeft(b)==false) 
        return 0; 
  
    // If this maximizer's move 
    if (isMax){ 
        int best = -1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) { 
            for (int j = 0; j<3; j++) { 
                // Check if cell is empty 
                if (b[i][j]==' '){
                    // Make the move 
                    b[i][j] = ai_player; 
  
                    // Call minimax recursively and choose 
                    // the maximum value 
                    best = max( best, minimax(b, depth+1, !isMax) ); 
  
                    // Undo the move 
                    b[i][j] = ' '; 
                }
            }
        }
        return best; 
    }
  
    // If this minimizer's move 
    else{
        int best = 1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++){ 
            for (int j = 0; j<3; j++){ 
                // Check if cell is empty 
                if (b[i][j]==' '){ 
                    // Make the move 
                    b[i][j] = human; 
  
                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best, minimax(b, depth+1, !isMax)); 
  
                    // Undo the move 
                    b[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } 
}

/* 
 * The bestMove function takes in the current board state
 * and evaluates the best possible move for the AI using
 * the minimax algorithm.
 * 
 * @param b -> holds 2d board vector
 * @return  -> returns a Move which holds a row and column variable
 */
AI::Move AI::bestMove(vector<vector <char>> &b){
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
    // Traverse all cells, evaluate minimax function for 
    // all empty cells. And return the cell with optimal 
    // value. 
    for (int i = 0; i<3; i++){ 
        for (int j = 0; j<3; j++){ 
            // Check if cell is empty 
            if (b[i][j]==' '){ 
                // Make the move 
                b[i][j] = ai_player; 
  
                // compute evaluation function for this 
                // move.
                int moveVal = minimax(b, 0, false); 
  
                // Undo the move 
                b[i][j] = ' '; 
  
                // If the value of the current move is 
                // more than the best value, then update 
                // best/ 
                if (moveVal > bestVal){ 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                }
            }
        }
    }
    
    return bestMove; 
}

/*
 * This function gets the human's move.
 * The user is prompted to input a row and column
 * then it will validate the user input.
 *  
 */
void AI::getHumanMove(){
    bool retry;
    Move hMove;
    
    do{
        cout << "Enter your move (row then column): " << endl;
        cin >> hMove.row;
        cin >> hMove.col;
        cout << endl;
        if(hMove.row < 1 || hMove.row > 3 || hMove.col < 1 || hMove.col > 3){
            retry = true;
            cout << "Invalid move, try again.\n";
        }
        else if(board[hMove.row-1][hMove.col-1] != ' '){
            retry = true;
            cout << "Space is already filled, try again.\n";
        }
        else{
            retry = false;
            board[hMove.row-1][hMove.col-1] = human;
        }
           
    }while(retry==true);
    
}

/* 
 * This function outputs the winner using the gameStatus variable.
 * In the play_cpu function gameStatus is set to the value returned by
 * Board::checkWin function. Then using a switch statement a winner is 
 * confirmed or it displays it is a tie game.
 * 
 * @param gameStatus -> holds the current game status
 */
void AI::outputWinner(char gameStatus){
    
    switch(gameStatus){
        case human: cout << "You are the winner!\n";
            break;
        case ai_player: cout << "The computer is the winner!\n";
            break;
        case 'T': cout << "The game is a tie!\n";
            break;
    }
}

/*
 * The main function to run the actual human vs. cpu 
 * game mode. This function is called in main if user
 * selects to go against the computer.
 * 
 */
void AI::play_AI(){
    // Declare and initialize variables
    char gameStatus = 'N';          // Int that determines the status of game
    int turn = 0;                   // Holds int to determine who's turn it is
    char play;                      // Holds user's decision when prompted to play
    bool retry;                     // Holds value used for input validation
    Move AImove;                    // Holds coordinates for the AI's move
    
    // Output tic tac toe instructions
    outputInstruct();
    
    // Prompt player to start the game
    do{
        cout << "Do you want to start a game (Y/N)? ";
        cin >> play;
        
        // If user enters y or n then we break out of the loop
        if(play=='y' || play=='Y' || play =='n' || play=='N')
            retry = false;
        // Else we keep looping until we get desired input
        else{
            retry = true;
            cout << "Invalid input, try again." << endl;
        }
    }while(retry==true);
    
    // Loop that runs the actual game
    while(play=='y' || play=='Y'){
        // Initialize the board
        initBoard();
        
        do{
            // Display the updated board
            displayBoard();
            
            // Human's move
            if(turn % 2 == 0){
                getHumanMove();
                turn++;
            }
            
            // Computer's turn
            else{
                AImove = bestMove(board);
                board[AImove.row][AImove.col] = ai_player;
                turn++;
            }
            
            // Set gameStatus to X or O victory or a tie
            gameStatus = checkWin();
        }while(gameStatus == 'N');
        
        displayBoard();
        outputWinner(gameStatus);
        
        // Prompt players to start a new game
        do{
            cout << "Do you want to play again (Y/N)? ";
            cin >> play;

            // Validate user input
            if (play == 'y' || play == 'Y' || play == 'n' || play == 'N')
                retry = false;
                
            else{
                retry = true;
                cout << "Invalid input, try again." << endl;
            }
        }while(retry==true);
        
        turn = 0;
    }
}

void AI::AI_mode(){
    // Declare and initialize variables
    char gameStatus = 'N';          // Int that determines the status of game
    int turn = 0;                   // Holds int to determine who's turn it is
    char play;                      // Holds user's decision when prompted to play
    bool retry;                     // Holds value used for input validation
    Move AImove;                    // Holds coordinates for the AI's move
    
    // Output tic tac toe instructions
    outputInstruct();
    
    // Prompt player to start the game
    do{
        cout << "Do you want to start the AI game (Y/N)? ";
        cin >> play;
        
        // If user enters y or n then we break out of the loop
        if(play=='y' || play=='Y' || play =='n' || play=='N')
            retry = false;
        // Else we keep looping until we get desired input
        else{
            retry = true;
            cout << "Invalid input, try again." << endl;
        }
    }while(retry==true);
    
    // Loop that runs the actual game
    while(play=='y' || play=='Y'){
        // Initialize the board
        initBoard();
        
        do{
            // Display the updated board
            displayBoard();
            
            // First AI's move
            if(turn % 2 == 0){
                AImove = bestMove(board);
                board[AImove.row][AImove.col] = human;
                turn++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            // Second AI's move
            else{
                AImove = bestMove(board);
                board[AImove.row][AImove.col] = ai_player;
                turn++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            
            // Set gameStatus to X or O victory or a tie
            gameStatus = checkWin();
        }while(gameStatus == 'N');
        
        displayBoard();
        outputWinner(gameStatus);
        
        // Prompt players to start a new game
        do{
            cout << "Do you want to play again (Y/N)? ";
            cin >> play;

            // Validate user input
            if (play == 'y' || play == 'Y' || play == 'n' || play == 'N')
                retry = false;
                
            else{
                retry = true;
                cout << "Invalid input, try again." << endl;
            }
        }while(retry==true);
        
        turn = 0;
    }
}