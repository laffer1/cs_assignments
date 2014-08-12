//  name: Lucas Holt 
//  asg#: Lab06 
//  lab section: 10:00 AM, Thursday lab
//  instructor: Yan Lu 
//  due date: 10:00 AM Nov 6, 2003

/*
    Too Many Queens
    
    How many queens can you place on the board so that no two of them are attacking each other?
    
    This program attacks this question by allocating a board of a user supplied size, placing
    one queen per row, and checking wheither or not the queens can attack each other over
    1 million iterations.  When a non attacking setup is found, the program prints the
    solution and exits.
*/
 
#include <iostream> 
#include <cmath>     // for rand()
#include <ctime>     // for time()
using namespace std;

void placement( int ); 
bool testAttack( int ); 
void printOut( int );

char board[15][15];  // must be a character array since we will place Q and - in cells.

int main() 
{ 

    int num_placements = 1;
    int size; 
    bool test;

    srand( time(0) );   // make rand() return "random" numbers

    // Get user input
    do 
    { 
        cout << "Enter the board size (< 15): "; 
        cin >> size;
    } while ( size < 4 || size > 14 );

    // generate boards and check the queen placement.
    while( num_placements <= 1000000 ) 
    {
        placement( size ); 
        test = testAttack( size );   // true means non attacking
        
        if ( test == true ) 
        { 
            cout << "Number of tries: " << num_placements << endl << endl;
        
            cout << "The board configuration is: " << endl << endl; 
            printOut( size ); 
            
            break; // we found a match
        } 
        
        num_placements++;
    }

    if ( test == false )
    { 
        cout << "You were unlucky.  You did not find a non-attacking configuration in 1 million tries." << endl; 
    }    
 
    return 0; 
}

/*
    placement( int boardsize )
    
    Sets up the board by randomly adding a queen
    one per row.  Cells not containing a queen
    are reset with a '-' character.
    
    PRECONDITIONS:
    
    Global multidimensional array named board allocated.    
    @param boardsize  Size of the current board (length and width).
                      Must be smaller than array dimensions and larger
                      than 0.
                      
    POSTCONDITIONS:
    
    board array is altered.
    @returns nothing
*/
void placement( int boardsize ) 
{ 
    int randCol, i, j;

    for ( i = 0; i < boardsize; i++ ) 
    { 
        // get a random number representing a column
        randCol = rand() % boardsize;
        
        for ( j = 0; j < boardsize; j++ ) 
        { 
            // the random column == the current column
	    if ( randCol == j ) 
                board[i][j] = 'Q';  // place a queen here
            else 
                board[i][j] = '-';  // no queen
        } 
    }
 
    return; 
}

/*
    testAttack( int boardsize ) 
    
    Tests the current board for non attacking queen
    configurations.  If one is found, testAttack
    is true.  A non attacking queen setup requires
    that no queens are found directly above
    or below the queen or at diagnals.  It is
    impossible to have two queens in the same
    row.
    
    PRECONDITIONS:
    
    Global multidimensional array named board allocated.    
    @param boardsize  Size of the current board (length and width).
                      Must be smaller than array dimensions and larger
                      than 0.
                      
    POSTCONDITIONS
    
    @returns   boolean representing a non attacking queen was found (true) or (false)
               if no non attacking queen setup was found.
*/
bool testAttack( int boardsize ) 
{ 
    int j;  // colomns.  
    
    // we start at one so that we don't go off the board
    // also checking the second row will ensure that
    // the first row is ok.
    // likewise we can skip the last row.
    for ( int i = 1; i < boardsize - 1; i++ ) 
    { 
        // find the queen in the current row
        for ( j = 0; j < boardsize; j++ )
            if ( board[i][j] == 'Q' )
                break;

       // check all around her for queens
       // TODO: there could be a problem here with the array index j
       // the array is one larger to prevent problems for now.
       if ( board[i-1][j] == 'Q' || board[i+1][j] == 'Q' ||
            board[i-1][j-1] == 'Q' || board[i-1][j+1] == 'Q' ||
            board[i+1][j+1] == 'Q' || board[i+1][j-1] == 'Q' )
           return false; 
    } 

    return true;
}

/*
    printOut( int boardsize ) 
    
    Prints the current board layout.
    
    PRECONDITIONS:
    
    Global multidimensional array named board allocated.    
    @param boardsize  Size of the current board (length and width).
                      Must be smaller than array dimensions and larger
                      than 0.
                      
    POSTCONDITIONS
    
    Prints the board layout to stdout
    @returns nothing
*/
void printOut( int boardsize )
{
    for ( int i = 0; i < boardsize; i++ )
    {
        for ( int j = 0; j < boardsize; j++ )
        {
            cout << board[i][j];
            cout << ' ';  // improve formatting
        }
        
        cout << endl;
    }
    
    return;
}
