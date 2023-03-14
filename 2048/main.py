import random
import numpy as np
import keyboard
#################################### 2048 Version 4.0! ####################################
# Init the board (function Outer calling the Board clearBoard and SpawnNewRandomTilex2)

# Board (Class)
    # DONE - BOARD = [[][][][]] -> List of a list that is 4x4 matrix
    # DONE - ClearBoard -> Empty the board 
    # DONE - SpawnNewRandomTile
    
    # DONE - MoveLeft()
    # DONE - MoveRight()
    # DONE - MoveUp()
    # DONE - MoveDown()
    # DONE - CheckWin():
        # BaseCase#0: 2048 -> WON
        # BaseCase#1: 0's on board -> continue
        # BaseCase#2: dups on board -> continue
    # DONE - run_game()
########################################################################################### 


class Main_Game:
    ########################################## CONSTRUCTOR ##########################################
    # myBoard = [[][][][]]
    # changedBoard = T/F
    #################################################################################################
    def __init__(self) -> None:
        self.myBoard = [[0,0,0,0],
                        [0,0,0,0],
                        [0,0,0,0],
                        [0,0,0,0]]
        
        self.changedBoard = False       # Marked if the board was changed during the move
    
    ########################################## PRINT BOARD ##########################################
    # PRINT board by getting each row, adding with | + display each row as texts
    #################################################################################################
    def printBoard(self):
        print("             2048             ")
        text1 = ""
        text2 = "   -----------------------  "

        print(text2)
        for eachRow in self.myBoard:
            text1 += "  |  "
            for eachTile in eachRow:
                if eachTile == 0:
                    text1 += str(" ") + "  |  "
                else:
                    text1 += str(eachTile) + "  |  "
                
            print(text1)
            print(text2)
            text1 = ""
    
    ########################################## CLEAR BOARD ##########################################
    # # CLEAR/EMPTY - the board  
    #################################################################################################
    def clearBoard(self):
        self.myBoard = [[0,0,0,0],
                        [0,0,0,0],
                        [0,0,0,0],
                        [0,0,0,0]]
    
    ########################################## SPAWN NEW TILES ##########################################
    # SPAWN - new titles randomly
    ##################################################################################################### 
    def spawnNewRandomTile(self):
        # randomize col and row
        row = random.randrange(0, 4)
        col = random.randrange(0, 4)

        # While new position is not 0 (empty)
        while(self.myBoard[row][col] != 0):
            row = random.randrange(0,4)
            col = random.randrange(0,4)
        
        # Initialize new tile with value of 2. Sometimes the game start with spawn values = (4,2) or (4,4) -> make it randomly chooses 4 
        if random.random() < 0.36:      self.myBoard[row][col] = 4
        else:                           self.myBoard[row][col] = 2
    
    ########################################## INIT BOARD ###############################################
    # SPAWN - new titles randomly
    ##################################################################################################### 
    # INIT - The Board with new 
    def InitBoard(self):
        self.clearBoard()
        self.spawnNewRandomTile()
        self.spawnNewRandomTile()
        self.printBoard()
    
    ########################################## SPAWN NEW TILES ##########################################
    # SHIFT - all tiles to the LEFT
    ##################################################################################################### 
    def ShiftAllLeft(self):
        # move everything to the left if there's exist a 0 on the left side
        for eachRow in self.myBoard:
            for i in range(len(eachRow)):
                if eachRow[i] == 0:
                    for n in range(i, len(eachRow)):
                        if eachRow[n] != 0:
                            eachRow[i] = eachRow[n]
                            eachRow[n] = 0
                            self.changedBoard = True
                            break
    
    ########################################## MOVE LEFT ################################################
    # Shift all tiles left
    # Merge any duplicates tiles
    # Shift all the tiles left again
    ##################################################################################################### 
    def moveLeft(self):
        self.changedBoard = False
        self.ShiftAllLeft()
        
        # Then MERGE dups
        for eachRow in self.myBoard:
            index1 = 0
            index2 = 1
            # if x = 4 and y = 4 or 2's --> merge y into x, set y = 0
            while index1 != 3 and index2 != 4:
                if eachRow[index1] == eachRow[index2] != 0:
                    eachRow[index1] += eachRow[index2]
                    eachRow[index2] = 0
                    self.changedBoard = True
                index1 += 1
                index2 += 1
                
        self.ShiftAllLeft()
    
    ########################################## MOVE RIGHT ################################################
    # Move right = Reversing matrix + moveLeft()
    ##################################################################################################### 
    def moveRight(self):
        self.changedBoard = False
        self.myBoard = np.fliplr(self.myBoard)
        self.moveLeft()
        self.myBoard = np.fliplr(self.myBoard)
        
    ########################################## MOVE UP ################################################
    # Move up = tranpose matrix + moveLeft()
    #####################################################################################################   
    def moveUp(self):
        self.changedBoard = False
        self.myBoard = np.transpose(self.myBoard)
        self.moveLeft() 
        self.myBoard = np.transpose(self.myBoard)
        
    ########################################## MOVE DOWN ################################################
    # Move down = tranpose matrix + moveRight()  
    ##################################################################################################### 
    def moveDown(self):
        self.changedBoard = False
        self.myBoard = np.transpose(self.myBoard)
        self.moveRight()
        self.myBoard = np.transpose(self.myBoard) 
        
    ########################################## CHECK WIN ################################################
    # Return the current state of the board/game
    # BaseCase#0: 2048 -> WON
    # BaseCase#1: 0's on board -> continue
    # BaseCase#2: dups on board -> continue
    #####################################################################################################  
    def checkWin(self):
        #if find 2048, return win
        for eachRow in self.myBoard:
            for eachTile in eachRow:
                if eachTile == 2048:
                    return 'W'
                
        # if 0 is on the board, continue the game
        for eachRow in self.myBoard:
            for eachTile in eachRow:
                if eachTile == 0:
                    return 'Y'
                
        # Check for dups tiles, continue if do
        for i in range(len(self.myBoard)):
            for j in range(len(self.myBoard)):
                if 0 <= i-1 <= 3:
                    if self.myBoard[i][j] == self.myBoard[i-1][j]:
                        return 'Y' 
                if 0 <= j-1 <= 3:
                    if self.myBoard[i][j] == self.myBoard[i][j-1]:
                        return 'Y' 
                if 0 <= i+1 <= 3:
                    if self.myBoard[i][j] == self.myBoard[i+1][j]:
                        return 'Y' 
                if 0 <= j+1 <= 3:
                    if self.myBoard[i][j] == self.myBoard[i][j+1]:
                        return 'Y'      
        return 'N'
    
    ########################################## RUN GAME #################################################
    # RUN THE GAME
    #####################################################################################################   
    def run_game(self):
        gameStart = 'Y'
        while gameStart.lower() == "y":
            gameStatus = 'Y'
            self.InitBoard()
            #self.setBoard()        # Testing Purposes
            #self.printBoard()      # Testing Purposes
                        
            while gameStatus == 'Y':
                # Get directional input, keep asking for input if not WASD
                key_pressed = input("Enter directional key (WASD): ")
                while key_pressed.lower() != 'a' and key_pressed.lower() != 'w' and key_pressed.lower() != 's' and key_pressed.lower() != 'd':
                    key_pressed = input("Enter directional key (WASD): ")

                if key_pressed.lower() == 'a':      self.moveLeft()
                elif key_pressed.lower() == 'd':    self.moveRight() 
                elif key_pressed.lower() == 'w':    self.moveUp()   
                elif key_pressed.lower() == 's':    self.moveDown()
                
                # Only spawn a new tile if the board moved/changed
                if self.changedBoard:               self.spawnNewRandomTile()
                    
                self.printBoard()
                gameStatus = self.checkWin()
        
            if gameStatus == "W":                   print("You've WON the game!")
            elif gameStatus == "N":                 print("You've LOST the game!")
            gameStart = input("Play again? (Y/N): ")

    ### FOR TESTING PURPOSES. Set the board to test diff scenerios 
    def setBoard(self):
       self.myBoard =  [[4,8,2048,16],
                        [16,32,16,32],
                        [32,16,32,16],
                        [16,32,16,32]]


############################################### MAIN GAME ###############################################
board = Main_Game()
board.run_game()
############################################### MAIN GAME ###############################################