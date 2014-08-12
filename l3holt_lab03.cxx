//  name: Lucas Holt
//  asg#: Lab03
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM Oct 9, 2003
 
/*
    Program Prints out the logarithm table
    for numbers from 1.0-1.9.
*/
 
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void printHeader();
void printTable();
 
int main()
{
    printTable();
    return 0;
}

/*
    Generates the log table while printing
    to stdout

    returns nothing
*/
void printTable()
{
    printHeader(); // print out the header

    // Sets fixed percision on floating point
    // to 4 after decimal pt.
    cout.setf( ios::fixed );
    cout.setf( ios::showpoint );

    for ( double i = 1.0; i < 9.9; i += .1 )
    {
        // begin the row
        cout.precision( 1 );
        cout << ' ' << i << '|';
        
        cout.setf( ios::fixed );
        cout.setf( ios::showpoint );
        cout.precision( 4 );  
      
        for ( double j = 0; j < .099; j += .01 )
        {
            cout << setw( 7 ) << log10( i + j );

        }
        cout << endl;
        
        // place a blank line after every 5th row
        if ( static_cast<int>( (i+.1) * 10) % 5 == 0 && i > 1.0 )
	    cout << endl;    
    }

    return;
}

/*
    Prints out the header to stdout
    including the column numbers
    
    returns nothing
*/
void printHeader()
{
    for ( int i = 0; i < 10; i++ )
    {
        cout << setw(7) << i;
    }
    
    cout << endl;    
    cout << "---------------------------------------------------------------------------" << endl;

    return;
}
