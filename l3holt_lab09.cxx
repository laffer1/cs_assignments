//  name: Lucas Holt
//  asg#: Lab09
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM  Dec 4, 2003

/*
    Payroll (XYZ Corporation)
 
    Given an input file, the program calculates payroll
    for all the employees.  The output consists of a 
    flat file sorted with each employee's name, address,
    and pay stub information.
 
    Program tested under Mac OS 10.3.1 with gcc 3.3.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>  // strcmp, exit, etc.
#include <iomanip>  // for setw

using namespace std;

/*
    employee class represents one employee's
    information.  Name, address, dependants
    hours worked, and other information needed
    to calculate payroll are encapsolated in this
    class.  
 
    The original data file example used
    full state names, but the current data
    file does not.  This class will keep
    a longer buffer for compatibility 
    reasons.
*/
class employee
{
private:
    char lname[25];    // last name
    char fname[25];    // first name
    char address[25];  // address field
    char city[25];     // city
    char state[25];    // full state name or abbrev.. e.g. Michigan or MI
    char zip[6];       // five digit zip code
    char type;         // hourly or salary
    int payrate;       // per hour or yearly depending on type filed.
    int hours;         // hours worked.. e.g. 80
    int dependents;    // number of dependants.. could be several if children, etc.
    int grosspay;      // what did we make.
    int fedwith;       // federal withheld
    int statewith;     // state 
    int socsec;        // social security
    int netpay;        // net pay ( gross - taxes )
    
    // private member functions for calculation
    void calcGrossPay();
    void calcFedWithhold();
    void calcStWithhold();
    void calcSocialSec();
    void calcNetPay();
    
    // overloaded operators
    friend istream & operator>>( istream &, employee & );
    friend ostream & operator<<( ostream &, employee & );
    friend bool operator>( employee &, employee & );
    friend bool operator<( employee &, employee & );
    
    
public:
    employee();
    employee( char *, char *, char *, char *, char *, char *, char, int, int, int );
    void set( char *, char *, char *, char *, char *, char *, char, int, int, int );
    void computePay();
};


int main ( void )
{
    char infilename[25];
    char outfilename[25];
    ifstream infile;   // our file input stream
    ofstream outfile;  // file output stream
    employee x[100];   // increase if we have more than 100 employees.
    int i = 0;         // number of employees starting at zero
    
    cout << "XYZ Corp Payroll Calculator" << endl << endl;
    
    cout << "File to read: (file name up to 24 characters) :";
    cin >> infilename;
    cout << endl;
    
    cout << "File to write: (file name up to 24 characters) :";
    cin >> outfilename;
    
    infile.open( infilename, ios::in );
    
    // verify the file loaded ok (permissions, not found)
    if ( !infile )
    {
        cerr << "Error opening file " << infilename << endl;
        exit(1);
    }
    
    outfile.open( outfilename, ios::out );
    
    // verify the file loaded ok (permissions)
    if ( !outfile )
    {
        cerr << "Error opening file" << outfilename << endl;
        exit(1);
    }
    
    while ( !infile.eof() && i < 100)
    {
        // initialize
        infile >> x[i];
        
        // finish setting up our objects
        x[i].computePay();
        
        i++;
    }
    
    // Insertion sort algorithm.  Sort the employees in ascending
    // order by their last, first name.
    /*
    FOR I <-- 1 TO N-1
        
        KEY <--  X[I]
        J <-- I - 1
     
         WHILE (J >=0  AND X[J] > KEY)
             X[J+1] <-- X[J]   {Move X[J] one place to the right}
             J <-- J-1
        END OF WHILE
        
        X[J+1] <-- KEY   {Insert KEY into its proper location}
    END OF FOR
     */
    
    employee key;
    int z;
    
    for ( int k = 1; k < i; k++ )
    {
        key = x[k];
        z = k - 1;
        
        while ( z >= 0 && x[z] > key )
        {
            cout << "z:" << z << endl;
            x[z+1] = x[z];  // move it one place to the right.
            z--;
        }
        
        x[z+1] = key;
    }
        
    // output
    for ( int n = 0; n < i; n++ )
        outfile << x[n];
    
    // we are done with the file.
    outfile.close();
    
    // we are done with the file, remove the file descriptor.
    infile.close();

    return 0;
}


/*
 employee:employee()
 
 Default constructor, calls the other constructor.
 
 PRECONDITIONS:
 none.
 
 POSTCONDITIONS:
 object created with default values.
*/
employee::employee()
{
    // default: All values zero and hourly employee type
    employee( "", "", "", "", "", "", 'H', 0, 0, 0 );
}


/*
 employee:employee( char * ln, char * fn, char * addr, char * mycity, 
                   char * mystate, char * myzip, char mytype, int pay, int hour, int dep )
 
 Creates an employee object with the specified parameters.
 
 PRECONDITIONS:
 @param ln      last name
 @param fn      first name
 @param addr    address
 @param mycity  city
 @param mystate state
 @param myzip   zip code (5 digit)
 @param mytype  salary or hourly
 @param pay     salary per year or hourly wage
 @param hour    hours worked
 @param dep     number of dependants
 
 POSTCONDITIONS:
 object created with specified values.
*/
employee::employee( char * ln, char * fn, char * addr, char * mycity, 
                    char * mystate, char * myzip, char mytype, int pay, int hour, int dep )
{
    strcpy( lname, ln );
    strcpy( fname, fn );
    strcpy( address, addr );
    strcpy( city, mycity );
    strcpy( state, mystate );
    strcpy( zip, myzip );
    type = mytype;
    payrate = pay;
    hours = hour;
    dependents = dep;    
}


/*
 employee:set( char * ln, char * fn, char * addr, char * mycity, 
                    char * mystate, char * myzip, char mytype, int pay, int hour, int dep )
 
 Creates an employee object with the specified parameters.
 
 PRECONDITIONS:
 @param ln      last name
 @param fn      first name
 @param addr    address
 @param mycity  city
 @param mystate state
 @param myzip   zip code (5 digit)
 @param mytype  salary or hourly
 @param pay     salary per year or hourly wage
 @param hour    hours worked
 @param dep     number of dependants
 
 POSTCONDITIONS:
 Object state is altered.
 @returns nothing.
 */
void employee::set( char * ln, char * fn, char * addr, char * mycity, 
               char * mystate, char * myzip, char mytype, int pay, int hour, int dep )
{
    strcpy( lname, ln );
    strcpy( fname, fn );
    strcpy( address, addr );
    strcpy( city, mycity );
    strcpy( state, mystate );
    strcpy( zip, myzip );
    type = mytype;
    payrate = pay;
    hours = hour;
    dependents = dep;    
}


/*
 employee::computePay( void )
 
 Computes a paycheck on the given object instance.
 
 PRECONDITIONS:
 The 10 base fields are set including
 address, hours worked, employee type, etc.
 
 POSTCONDITIONS:
 @returns nothing.
 */
void employee::computePay( void )
{
    calcGrossPay();
    calcFedWithhold();
    calcStWithhold();
    calcSocialSec();
    calcNetPay();
}


/*
 employee::calcGrossPay( void )
 
 Calculates the gross pay and stores it
 in the current object instance.
 
 PRECONDITIONS:
 hours and payrate are set.
 employee type is set (hourly or salary)
 
 POSTCONDITIONS:
 gross pay is altered.
 @returns nothing.
 */
void employee::calcGrossPay( void )
{
    // either hours times rate or salary / 26
    
    if ( type == 'H' )
        grosspay = hours * payrate;
    else if ( type == 'S' )
        grosspay = payrate / 26;
    else
        // error condition
        cerr << "Invalid employee type.  Must be H or S.";
    
    return;
}


/*
 employee::calcFedWithhold( void )
 
 Calculates the federal withholding and stores it
 in the current object instance.
 
 PRECONDITIONS:
 grosspay and dependants are set.
 
 POSTCONDITIONS:
 fedwith is altered.
 @returns nothing.
 */
void employee::calcFedWithhold( void )
{
    // formula (GrossPay*26 - $2,500*NumberofDependents)*.28/26
    fedwith = static_cast<int>( ((grosspay * 26) - (2500 * dependents)) *.28/26 );
 
    return;
}


/*
 employee::calcStWithhold( void )
 
 Calculates the state withholding and stores it
 in the current object instance.
 
 PRECONDITIONS:
 grosspay is set.
 
 POSTCONDITIONS:
 statewith is altered.
 @returns nothing.
 */
void employee::calcStWithhold( void )
{
    // gross pay times 4.8 percent
    statewith = static_cast<int>( grosspay * .048 );
    
    return;
}


/*
 employee::calcSocialSec( void )
 
 Calculates the social security and stores it
 in the current object instance.
 
 7.5 percent of the gross.
 
 PRECONDITIONS:
 grosspay is set.
 
 POSTCONDITIONS:
 socsec is altered.
 @returns nothing.
 */
void employee::calcSocialSec( void )
{
    socsec = static_cast<int>( grosspay * .075 );
    
    return;
}


/*
 employee::calcNetPay( void )
 
 Calculates the net pay and stores it
 in the current object instance.
 
 The net pay is the gross minus taxes.
 
 PRECONDITIONS:
 grosspay, socsec, fedwith, and statewith are set.
 
 POSTCONDITIONS:
 netpay is altered.
 @returns nothing.
 */
void employee::calcNetPay( void )
{
    netpay = grosspay - socsec - fedwith - statewith;
    
    return;
}


/*
 istream & operator>>( istream & in, employee & em )
 
 Overloads the >> operator to setup a employee class
 instance.  Must pass it an istream object like
 an ifstream or similar.
 
 PRECONDITIONS:
 file is open containing employees in the correct format.
 @param in   input file stream
 @param em   employee instance.
 
 POSTCONDITIONS:
 employee class em is setup correctly.
 @returns istream  (original file stream object or similar)
 */
istream & operator>>( istream & in, employee & em )
{
    char temp[2] = { 'H', '\0' };
    char temp2[25];
    
    in.getline( em.lname, sizeof(em.lname), '|' );
    in.getline( em.fname, sizeof(em.fname), '|' );
    in.getline( em.address, sizeof(em.address), '|' );
    in.getline( em.city, sizeof(em.city), '|' );
    in.getline( em.state, sizeof(em.state),'|' );
    in.getline( em.zip, sizeof(em.zip), '|' );
    
    in.getline( temp , sizeof(temp), '|' );
    em.type = temp[0];
    
    in.getline( temp2, sizeof(temp2), '|' );
    em.payrate = atoi( temp2 );
    
    in.getline( temp2, sizeof(temp2), '|' );
    em.hours = atoi( temp2 );
    
    in.getline( temp2, sizeof(temp2), '\n' );
    em.dependents = atoi( temp2 );
 
    return in; 
}


/*
 ostream & operator<<( ostream & out, employee & em )
 
 Overloads the << operator to output the employee class
 instance to a file or similar.
 
 PRECONDITIONS:
 file is open for writing.
 @param out  output file stream
 @param em   employee instance.
 
 POSTCONDITIONS:
 employee class em is setup correctly.
 @returns ostream passed in ( probably a ofstream )
 */
ostream & operator<<( ostream & out, employee & em )
{
    out << em.fname << ' ' << em.lname << endl;
    out << em.address << endl;
    out << em.city << ", " << em.state << ' ' << em.zip << endl;
    
    // fix the formatting of the numbers to look more "curency like"
    out.setf( ios::fixed );
    out.setf( ios::showpoint );
    out.precision( 2 );
    
    out << "Gross Pay:          " << setw( 10 ) << "$ " << em.grosspay / 100.0 << endl;
    out << "Federal Withholding:" << setw( 10 ) << "$ " << em.fedwith / 100.0  << endl;
    out << "State Withholding:  " << setw( 10 ) << "$ " << em.statewith / 100.0 << endl;
    out << "FICA:               " << setw( 10 ) << "$ " << em.socsec / 100.0 << endl;
    out << "Net Pay:            " << setw( 10 ) << "$ " << em.netpay / 100.0 << endl;
    
    // double space between sets
    out << endl << endl;
    
    return out;
}


/*
 operator>( employee & a, employee & b )
 
 Overloads the > operator for comparisons of
 two employee objects on lname and fname.
 
 PRECONDITIONS:
 two employee objects are initilized
 @param a  employee instance.
 @param b  employee instance.
 
 POSTCONDITIONS:
 @returns a boolean that is true if the first 
          employee (a) is greater than the second.
          Otherwise false is returned.
 */
bool operator>( employee & a, employee & b )
{
    int cmp;
    
    cmp = strcmp( a.lname, b.lname );
    cout << cmp << endl;
    
    if ( cmp > 0 )
    {
        return true;
    }
    else if ( cmp == 0 )
    {
        if ( strcmp( a.fname, b.fname ) > 0 )
            return true;
    }
    
    return false;
}


/*
 operator<( employee & a, employee & b )
 
 Overloads the < operator for comparisons of
 two employee objects on lname and fname.
 
 PRECONDITIONS:
 two employee objects are initilized
 @param a  employee instance.
 @param b  employee instance.
 
 POSTCONDITIONS:
 @returns a boolean that is true if the first 
 employee (a) is less than the second.
 Otherwise false is returned.
 */
bool operator<( employee & a, employee & b )
{
    int cmp;
    
    cmp = strcmp( a.lname, b.lname );
    
    if ( cmp < 0 )
    {
        return true;
    }
    else if ( cmp == 0 )
    {
        if ( strcmp( a.fname, b.fname ) < 0 )
            return true;
    }
    
    return false;
}