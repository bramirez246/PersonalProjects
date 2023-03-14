/* 
 * File:   tictac.cpp
 * Author: Brian Ramirez
 *
 * Created on April 12, 2019, 2:20 PM
 */

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>
#include "tictac.h"
using namespace std;


// Initializes the board with blanks
void Board::initBoard(){
    // Initialize and resize board vector
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            board[i][j]= ' ';
        }
        
    }

}


/******************************************************************************
* displayBoard
* This function outputs the tic tac toe board including the tokens
* played in the proper format (as described below).
*
* 	 			   1 	    2 	     3
*				 [1][1] | [1][2] | [1][3]
* 					| 	 |
* 	 1 			        | 	 |
* 				        |        |
* 				 --------------------------
* 				 [2][1] | [2][2] | [2][3]
* 					|        |
* 	 2 			        |        |
* 				        |        |
* 				 --------------------------
* 				 [3][1] | [3][2] | [3][3]
* 				        |        |
* 	 3 				|        |
*					|        |
*
* RETURNS: nothing
* -> outputs the current state of the board
*****************************************************************************/

void Board::displayBoard(){
    //clear the screen
    clearScreen();
    
    cout << setw(10) << "1" << setw(8) << "2" << setw(9) << "3\n";
    for (int i=0; i < board.size(); i++) {
        cout << setw(7) << "[" << i + 1 << "][1] | " << "[" << i + 1;
        cout << "][2] | " << "[" << i + 1 << "][3]" << endl;
        cout << setw(14) << "|" << setw(9) << "|" << endl;

        for (int j = 0; j < board.size(); j++) {
            switch (j) {
                case 0: cout << i + 1 << setw(9) << board[i][j];
                    cout << setw(4) << "|";
                    break;

                case 1: cout << setw(4) << board[i][j];
                    cout << setw(5) << "|";
                    break;

                case 2: cout << setw(4) << board[i][j] << endl;
                    break;

                default: cout << "ERROR!\n\n";
            }
        }
        cout << setw(14) << "|" << setw(10) << "|\n";

        if (i != 2) {
            cout << setw(32) << "--------------------------\n";
        }
    }
    cout << endl << endl;
}

void Board::clearScreen(){
    #ifdef _WIN32
        system ("cls");
    #else
        // Assume POSIX
        system ("clear");
    #endif
}

/******************************************************************************
* outputInstruct
* This function outputs instructions to the users. There are no input
* or output parameters for this function as it only displays text to
* the screen.
*
* RETURNS: nothing
* -> Displays the instructions to the user
*****************************************************************************/
void Board::outputInstruct()
{
    cout << "*TIC-TAC-TOE" << endl << endl;
    cout << "*There are two players 'X' and 'O'. " << endl << endl;
    cout << "*X always goes first." << endl << endl;
    cout << "*Players alternate placing Xs and Os on the board until " << endl;
    cout <<	" either (a) one player has three in a row, horizontally, " << endl;
    cout << " vertically, or diagonally, or (b) all nine squares are " << endl;
    cout <<	" filled." << endl << endl;
    cout << "*If a player is able to draw three X's or three O's in a " << endl;
    cout <<	" row, that player wins." << endl << endl;
    cout << "*If all nine squares are filled and neither player has " << endl;
    cout <<	" three in a row, the game is a draw." << endl << endl;
}

void Board::getPlayers(){
    string playerName="\0";
    cin.ignore(100, '\n');
    cout << "\nEnter the first player's name:  ";
    getline(cin, playerName);
    player1.first='X';
    player1.second=playerName;

    cout << "\nEnter the second player's name: ";
    getline(cin, playerName);
    player2.first='O';
    player2.second=playerName;
}

void Board::getCheckInput() {
    // Declare variables
    bool retry;
    int column;
    int row;
    
    switch (token) {
        case 'X': cout << player1.second << " it's your turn." << endl;
            break;
        case 'O': cout << player2.second << " it's your turn." << endl;
            break;
    }
   

    do {
        cout << "Enter your move(row then col): "<< endl;
        cin >> row;
        cin >> column;
        if (row < 1 || row > 3 || column < 1 || column > 3){
             retry = true;
             cout << "Invalid move, try again.\n";
        }
           
        else if (board[row - 1][column - 1] != ' '){
            retry = true;
            cout << "Space is already filled.\n";
        }
        
        else{
            retry = false;
            board[row - 1][column - 1] = token; 
        }
    } while (retry == true);
}


char Board::checkWin(){
    int r = 0;  // Number for rows
    int c = 0;  // Number for columns
    char W;     // Winning

    // Check 3 rows of X
    if (board[r][c] == 'X' && board[r][c + 1] == 'X'
            && board[r][c + 2] == 'X')
        W = 'X';
    else if (board[r + 1][c] == 'X' && board[r + 1][c + 1] == 'X'
            && board[r + 1][c + 2] == 'X')
        W = 'X';
    else if (board[r + 2][c] == 'X' && board[r + 2][c + 1] == 'X'
            && board[r + 2][c + 2] == 'X')
        W = 'X';

    // Check 3 columns of X
    else if (board[r][c] == 'X' && board[r + 1][c] == 'X'
            && board[r + 2][c] == 'X')
        W = 'X';
    else if (board[r][c + 1] == 'X' && board[r + 1][c + 1] == 'X'
            && board[r + 2][c + 1] == 'X')
        W = 'X';
    else if (board[r][c + 2] == 'X' && board[r + 1][c + 2] == 'X'
            && board[r + 2][c + 2] == 'X')
        W = 'X';

    // Check diagonally for X
    else if (board[r][c] == 'X' && board[r + 1][c + 1] == 'X'
            && board[r + 2][c + 2] == 'X')
        W = 'X';
    else if (board[r + 2][c] == 'X' && board[r + 1][c + 1] == 'X'
            && board[r][c + 2] == 'X')
        W = 'X';
    
    // Check 3 rows for O
    else if (board[r][c] == 'O' && board[r][c + 1] == 'O'
            && board[r][c + 2] == 'O')
        W = 'O';
    else if (board[r + 1][c] == 'O' && board[r + 1][c + 1] == 'O'
            && board[r + 1][c + 2] == 'O')
        W = 'O';
    else if (board[r + 2][c] == 'O' && board[r + 2][c + 1] == 'O'
            && board[r + 2][c + 2] == 'O')
        W = 'O';
    
    // Check 3 columns for O
    else if (board[r][c] == 'O' && board[r + 1][c] == 'O'
            && board[r + 2][c] == 'O')
        W = 'O';
    else if (board[r][c + 1] == 'O' && board[r + 1][c + 1] == 'O'
            && board[r + 2][c + 1] == 'O')
        W = 'O';
    else if (board[r][c + 2] == 'O' && board[r + 1][c + 2] == 'O'
            && board[r + 2][c + 2] == 'O')
        W = 'O';
    
    // Check diagonally for O
    else if (board[r][c] == 'O' && board[r + 1][c + 1] == 'O'
            && board[r + 2][c + 2] == 'O')
        W = 'O';
    else if (board[r + 2][c] == 'O' && board[r + 1][c + 1] == 'O'
            && board[r][c + 2] == 'O')
        W = 'O';
    
    // Check if the game is a tie
    else if (board[r][c] != ' ' && board[r][c + 1] != ' '
            && board[r][c + 2] != ' ' && board[r + 1][c] != ' '
            && board[r + 1][c + 1] != ' ' && board[r + 1][c + 2] != ' '
            && board[r + 2][c] != ' ' && board[r + 2][c + 1] != ' '
            && board[r + 2][c + 2] != ' ')
        W = 'T';
    
    // Check if the game is still playing
    else
        W = 'N';

    return W;
}

char Board::switchTokens(){
    // If token is currently X, switch it to O
    if(token == 'X'){
        token = 'O';
    }

    // If token is currently O, switch it to X
    else{
        token = 'X';
    }
    return token;
}

void Board::outputWinner(char gameStatus){
    this->gameStatus=gameStatus;
    // 	Switch on winner
    switch (this->gameStatus) 
    {
        // Player X wins
        case 'X': cout << player1.second << " is the winner!" << endl;
            break;

        // Player O wins
        case 'O': cout << player2.second << " is the winner!" << endl;
            break;

        // Tie
        case 'T': cout << "The game is a tie, git gud." << endl;
            break;
    }
}

void Board::play_pvp(){
    // Declare and initialize variables
    char gameStatus = 'N';          // Character that determines the status of game
    char play;                      // Holds user's decision when prompted to play
    char changeN = 'Y';             // Holds user's decision when prompted to change name
    bool retry;                     // Holds value used for input validation
    Board ticTac;
    
    // Output instructions
    ticTac.outputInstruct();
    
    // Prompting players if they want to play
    do{
        cout << "Do you want to start the game (Y/N)? ";
        cin >> play;
        ticTac.setPlay(play);
        cout << endl;
        if(play == 'y' || play == 'Y' || play == 'n' || play == 'N')
            retry = false;
        else{
            retry = true;
            cout << "Invalid input, try again." << endl;
        }
    }while(retry==true);
    
    //While loop that runs the actual tic tac toe game
    while (play == 'Y' || play == 'y'){
        // Initializes board with blanks
        ticTac.initBoard();
        
        // Set the token
        ticTac.setToken();
        
        // Loop that runs if changeName is 'y' or 'Y'
        ticTac.setChangeName(changeN);
        if (ticTac.getChangeName() == 'Y' || ticTac.getChangeName() == 'y')
            // Calling on GetPlayers function
            ticTac.getPlayers();

        do{
            ticTac.displayBoard();
            ticTac.getCheckInput();
            ticTac.switchTokens();
            gameStatus = ticTac.checkWin();
        } while (gameStatus == 'N');

        ticTac.displayBoard();
        ticTac.setGameStatus(gameStatus);
        ticTac.outputWinner(gameStatus);

        // Prompt players to start a new game
        do{
            cout << "Do you want to play again (Y/N)? ";
            cin >> play;

            // Validate user input
            if (play == 'y' || play == 'Y' || play == 'n' || play == 'N'){
                retry = false;
                ticTac.setPlay(play);
                play = ticTac.getPlay();
                cout << endl;
            }
                
            else{
                retry = true;
                cout << "Invalid input, try again." << endl;
            }
        }while(retry==true);
        
        // Prompt players to change their names
        if(play == 'Y' || play == 'y'){
            // Prompt players to change their names and validate input
            do{
                cout << "Would you like to change your names (Y/N)? ";
                cin >> changeN;
                if(changeN=='y' || changeN=='Y' || changeN=='n' || changeN=='N'){
                    retry = false;
                    ticTac.setChangeName(changeN);
                }
                else{
                    retry = true;
                    cout << "Invalid input, try again." << endl;
                }
            }while(retry==true);
        }
    }
}
