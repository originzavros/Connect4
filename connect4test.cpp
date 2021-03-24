#include <iostream>
#include <string>
using namespace std;

//these are the main variables to change size of the connect 4 game
//NOTE there are no protections against putting negative numbers here or making both 0
constexpr int table_width = 7;
constexpr int table_height = 6;

//receives a width and height to create a 2d matrix as a single string array
//contains methods to print out the matrix, set values based on column depth, and check for matching values in straight lines
class MatrixManager
{
    const int m_width, m_height;
    string* matrix = 0;
    string blank = " ";
    
    private:
    //this returns the position in the single array related to normal 2d grid coordinates
    int index(int x, int y) const {return x * m_width + y;}
    
    //sets all of the values to 1 'space' which is mainly used when the matrix is created
    void clearMatrix()
    {
        for(int x = 0; x <  m_height; x++)
        {
            for(int y = 0; y < m_width; y++)
            {
                matrix[index(x,y)] = blank;
            }
        }
    }
    
    public:
    //the constructor just needs a width and height to put together a local matrix with those dimensions
    MatrixManager(int set_width,int set_height) : m_width(set_width), m_height(set_height), matrix(new string[set_width * set_height]){clearMatrix();}
    ~MatrixManager(){ delete[] matrix;}
    
    //for debug purposes, prints out the matrix with the x,y positions instead of the array values
    void printMatrixPositions()
    {
        for(int x = 0; x < m_height; x++)
        {
            for(int y = 0; y < m_width; y++)
            {
                cout << "[" << x << "," << y << "]";
            }
            cout << "\n";
        }
    }
    
    //print out the matrix values in an easy to read format
    void printMatrixValues()
    {
        for(int x = 0; x < m_height; x++)
        {
            for(int y = 0; y < m_width; y++)
            {
                cout << "[" << matrix[index(x,y)]  << "]";
            }
            cout << "\n";
        }
    }
    
    //very simple method to print the column numbers, generally used before printMatrixValues()
    void printColumnNumbers()
    {
        for(int y = 0; y < m_width; y++)
        {
            cout << " " << y + 1 << " ";
        }
        cout << "\n";
    }
    
    //checks the bottom of a column and works to the top until it finds a space to overwrite with the player token
    //returns the row position, otherwise -1
    int MatrixInsertAtColumn(int columnNum, string* XO)
    {
        for(int i=m_height -1; i >= 0; i--)
        {
            if(matrix[index(i,columnNum-1)].compare(blank) == 0)
            {
                matrix[index(i, columnNum-1)] = *XO;
                return i;
            }
        }
        return -1;
    }
    
    //looks for 4 in a row in 4 directions (vertical,horizontal,diagonal downward(\), diagonal upward(/)) based on the value in matrix[row,colum]
    int checkForXInARowFromPosition(int x, int y)
    {
        int adjustedY = y-1;
        int val_x = x;
        int val_y = adjustedY;
        string XO =  matrix[index(x,adjustedY)];
        int xInRowCount = 1;
        int totalXInRow = 0;
        
        //Grid Math to determine direction we are checking
        //[-1,-1] [-1,0] [-1,+1]
        //[ 0,-1] [ 0,0] [ 0,+1]
        //[+1,-1] [+1,0] [+1,+1]
        
        //check column
        for(val_x=(x-1); val_x >= 0;val_x--)
        {
            if((matrix[index(val_x, adjustedY)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
        }
        // << "after checking upward :" << xInRowCount << "\n";
        for(val_x=(x+1); val_x < m_height ;val_x++)
        {
            //cout << "compare x,y with xo :" << (matrix[index(val_x, y)] == XO) << "\n";
            if((matrix[index(val_x, adjustedY)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
        }
        //cout << "after checking downward :" << xInRowCount << "\n";
        if(xInRowCount > totalXInRow){totalXInRow = xInRowCount; xInRowCount = 1;}
        
        //check row
        for(val_y=(adjustedY-1); val_y >= 0;val_y--)
        {
             if((matrix[index(x, val_y)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
        }
        //cout << "after checking left :" << xInRowCount << "\n";
        for(val_y=(adjustedY+1); val_y < m_width ;val_y++)
        {
            if((matrix[index(x, val_y)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
        }
        //cout << "after checking right :" << xInRowCount << "\n";
        if(xInRowCount > totalXInRow){totalXInRow = xInRowCount; xInRowCount = 1;}
        
        //check diagonal direction top left to downright
        val_y=adjustedY;
        for(val_x=(x-1); val_x >= 0;val_x--)
        {
            val_y--;
            if((matrix[index(val_x, val_y)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
            
        }
        //cout << "after checking top left :" << xInRowCount << "\n";
        val_y=adjustedY;
        for(val_x=(x+1); val_x < m_height ;val_x++)
        {
            val_y++;
            if((matrix[index(val_x, val_y)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
        }
        //cout << "after checking downright diagonal :" << xInRowCount << "\n";
        if(xInRowCount > totalXInRow){totalXInRow = xInRowCount; xInRowCount = 1;}
        
        //check diagonal direction top right to down left
        val_y=adjustedY;
        for(val_x=(x-1); val_x >= 0;val_x--)
        {
            val_y++;
            if((matrix[index(val_x, val_y)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
            
        }
        //cout << "after checking top right :" << xInRowCount << "\n";
        val_y=adjustedY;
        for(val_x=(x+1); val_x < m_height ;val_x++)
        {
            val_y--;
            if((matrix[index(val_x, val_y)].compare(XO)) == 0)
            {
                xInRowCount++;
            }
            else{break;}
        }
        //cout << "after checking down left :" << xInRowCount << "\n";
        if(xInRowCount > totalXInRow){totalXInRow = xInRowCount; xInRowCount = 1;}
        
        return totalXInRow;
    }
};
//-----------------------------------------------------------------------------------------

//receives a matrix manager object and uses it to play connect 4
class Connect4GameController
{
    string Player1 = "X";
    string Player2 = "O";
    const int connect_number_to_win = 4;
    MatrixManager* mm = 0;
    
    private:
    //helper method to print the win state of the game
    void printWinState(int playerNum, string XO)
    {
        cout << "===== GAME OVER! ======" << "\n";
        printGameState();
        cout << "Player " << playerNum << "(" << XO << ")" << " is the winner!";
    }
        
    //a helper method to display the current gamestate through matrix manager
    void printGameState()
    {
        mm->printColumnNumbers();
        mm->printMatrixValues();
    }   
    
    //will filter player input until they input an int between 1 and 7
    int getPlayerInput()
    {
        int selection = -1;
        while(!(selection >= 1 && selection <= 7))
        {
            cin >> selection;
            if(cin.fail() || !(selection >= 1 && selection <= 7))
            {
                cout << "invalid column, please choose a column number" << endl;
                cout << "choose a slot: ";
                cin.clear();
                cin.ignore();
            }
        }
        return selection;
    }
    
    public:
    //needs a matrix manager object to do game operations with
    Connect4GameController(MatrixManager* m_mm): mm(m_mm){}
    
    //starts a connect4Game and manages the player turns and logic for manipulating MatrixManager
    void runGame()
    {
        cout << "-----Connect 4-----" << "\n";
        printGameState();
        bool playerTurnFlag = true; //player1 is true, player2 is false
        int selection = -1; //will hold what column the player selects
        int returnRow = -1; //holds what MatrixManager returns on MatrixInsertAtColumn
        while (true)
        {
            if(playerTurnFlag)
            {
                cout << "Player 1 (" << Player1 << ") choose a slot: ";
                selection = getPlayerInput(); //will give us filtered input from the player
                //have matrix manager drop the token in a column, making sure that column isn't full
                while((returnRow = mm->MatrixInsertAtColumn(selection, &Player1)) < 0) 
                {
                    cout << "column is full, choose another column: ";
                    selection = getPlayerInput();
                }
                //see if the player has won the game
                if(mm->checkForXInARowFromPosition(returnRow,selection) >= connect_number_to_win)
                {
                    printWinState(1, Player1);
                    break;
                }
                
            }
            else
            {
                cout << "Player 2 (" << Player2 << ") choose a slot: ";
                selection = getPlayerInput();
                while((returnRow = mm->MatrixInsertAtColumn(selection, &Player2)) < 0)
                {
                    cout << "column is full, choose another column: ";
                    selection = getPlayerInput();
                }
                if(mm->checkForXInARowFromPosition(returnRow,selection) >= connect_number_to_win)
                {
                    printWinState(2, Player2);
                    break;
                }
                
            }    
            playerTurnFlag = !playerTurnFlag;
            printGameState();
        }
    }
};
//-----------------------------------------------------------------------------------------

int main()
{
    MatrixManager *mm = new MatrixManager(table_width, table_height);
    //mm->printMatrixPositions();
    Connect4GameController *c4gc = new Connect4GameController(mm);
    c4gc->runGame();
    delete mm;
    delete c4gc;
}