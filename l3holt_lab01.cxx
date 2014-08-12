//  name: Lucas Holt
//  asg#: Lab01
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM Sept 25, 2003

/*
    Program takes 3 integer inputs and sorts them in
    ascending order.  The ints are then printed
    to standard output.
*/

#include <iostream>
using namespace std;

int main()
{

    int x;  // first input variable
    int y;  // second input variable
    int z;  // third input variable

    // Get user input
    cout << "Please input 3 integers seperated by a space: ";
    cin >> x >> y >> z;

    // common to all the lines below
    cout << "In ascending order, they are: ";

    if ( y < z )
    {
        // y is smaller than z
        
        if ( x <= y )
        {  
            // we determined that x is the smallest, then y, and finally z
            cout << x << ' ';
            cout << y << ' ';
            cout << z << endl;
        } 
	else 
        {

            if ( x < z )
            { 
            	// y is smaller than x, and x is smaller than z
            	cout << y << ' ';
            	cout << x << ' ';
            	cout << z << endl;
            } 
            else 
            {
                cout << y << ' ';
                cout << z << ' ';
                cout << x << endl;
            }
        }
    } 
    else         // y >= z
    {

        if ( x <= z )
        {
            // x is smaller than z and y
            cout << x << ' ';
            cout << z << ' ';
            cout << y << endl;
        } 
        else 
        {
            
            if ( x < y )
            {
                // z is the smallest, followed by x and y
                cout << z << ' ';
                cout << x << ' ';
                cout << y << endl;
            } 
            else 
            {
                cout << z << ' ';
                cout << y << ' ';
                cout << x << endl;
            }  
        }
    }

    return 0;   
}
