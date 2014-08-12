//  name: Lucas Holt
//  asg#: Lab02
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM Oct 2, 2003
 
/*
    the program takes an amount invested, a percentage rate, and 
    the number of years to invest. It will output the total 
    amount invested after N years and the minimum number
    of years to double the original investment.
*/
 
#include <iostream>
using namespace std;
 
int main()
{
    int n = 0; // number of years
    double p = 0; // amount invested
    double r = 0; // annual percentage rate.
    double totalInvested = 0; // used to calculate the exact amount
    double investment = 0; // used to calculate the minimum number of years...
    double a = 1.0; 

    cout << "Investment Calculation Program" << endl;

    /* Get user input */
    
    while ( p < 1000 || p > 10000 )
    {
        cout << "Please input the amount to invest: ";
        cin >> p;

        if ( p < 1000 || p > 10000)
            cout << "Error: The amount should be between $1000 and $10000\n";
    } 

    while ( r < 3.0 || r > 10.0 )
    {
        cout << "Please input the annual percentage rate: ";
        cin >> r;
                                                                                
        if ( r < 3.0 || r > 10.0 )
            cout << "Error: The APR should be between 3.0 and 10.0\n";
    }

    while ( n < 2 || n > 13 )
    {
        cout << "Please input the number of years the investment will build: ";
        cin >> n;
                                                                                                                                                             
        if ( n < 2 || n > 13 )
            cout << "Error: The APR should be between 2 and 13 years inclusive\n";
    }

    /* calculate the total invested over n years */
    for ( int i = 0; i < n; i++ )
    {
        a = a * ( 1.0 + (r/100) );
    } 

    totalInvested = p * a;

    cout << endl;  // for clarity in output
    cout << "Given $" << p << " over " << n << " years at " << r << "%, the total invested is $" << totalInvested << endl << endl; 

    /*
       Second Calculation.. get fresh input from user!
       We will need to reset several variables to ensure accurate
       calculations.
    */
    p = 0;
    r = 0;
    n = 0;

    while ( p < 1000 || p > 10000 )
    {
        cout << "Please input the amount to invest: ";
        cin >> p;

        if ( p < 1000 || p > 10000)
            cout << "Error: The amount should be between $1000 and $10000\n";
    }

    while ( r < 3.0 || r > 10.0 )
    {
        cout << "Please input the annual percentage rate: ";
        cin >> r;

        if ( r < 3.0 || r > 10.0 )
            cout << "Error: The APR should be between 3.0 and 10.0\n";
    }    
    
    /* Calculate the minimum number of years to double the initial investment P */   
    while ( investment < (p * 2) )
    {
        n++; // increment the number of years by 1
        
        a = 1.0;  // reset for fresh calculation
        for ( int z = 0; z < n; z++ )
        {
            a = a * ( 1.0 + (r/100) );
        }
        
        investment = p * a;
        // cout << "debug Investment:" << investment << endl;
    } 

    cout << "The minimum number of years for the investment to double is " << n  << " yrs at " << r 
        << "% with an initial investment of $" << p << endl;
    cout << "The actual amount after this time would be $" << investment << endl;
                                                                                
    return 0;
}
