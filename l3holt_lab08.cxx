//  name: Lucas Holt
//  asg#: Lab08
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM  Nov 20, 2003

/*
    Shapes
 
    Loads shape definitions from a file and determines
    if the shapes are "inside" other shapes.  The file should be
    named "lab08.dat" given to the application.  If the file is
    not found, an error is sent to stderr.
 
    The file may contain up to 10 shape definitions, prefixed
    with the number of shapes.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;


/* 
    Shape class definition

    Can represent points, circles, or squares.
 
 
    Implementation details:
 
    For a circle, the (x,y) represents the center point.
 
    For a square, the (x,y) represents the bottom
    left hand corner.
 
     P = point
     C = circle
     S = square
*/
class Shape
{
private:
    int x;      // x-coordinate
    int y;      // y-coordinate
    int r;      // radius or side of shape
    char type;  // type of shape P, S, C

public:
    Shape();
    void print();
    bool isInside( Shape );
    void set( char, int, int, int );
    void set( int, int );
    int getX();
    int getY();
    int getRadius();
    int getSide();
    char getType();
};


int main( void )
{
    Shape shapes[10];  // create 10 shapes
    ifstream infile;   // our file input stream
    int n = 0;         // number of shapes read from file
    int x;             // x-coordinate
    int y;             // y-coordinate
    int r;             // radius or side
    char type;         // P, S, or C
    
    // file format:
    // 8
    // P -1 0
    // S 0 0 5
    // S 1 1 2
    // ...
    infile.open( "lab08.dat", ios::in );
    
    // verify the file loaded ok (permissions, not found)
    if ( !infile )
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    
    infile >> n; // number of records
    
    for ( int k = 0; k < n; k++ )
    {
        // required by all 3 shapes
        infile >> type >> x >> y;
        
        if ( type == 'P' )
        {
            // if its a point, there is no side/radius defined.
            shapes[k].set( x, y );
        }
        else
        {
            // we better get the radius too
            infile >> r;
            shapes[k].set( type, x, y, r );
        }
    }
    
    // we are done with the file, remove the file descriptor.
    infile.close();
    
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            if ( j != i && shapes[j].isInside( shapes[i] ) )
            {
                shapes[j].print();
                cout << " is contained in ";
                shapes[i].print();
                cout << "." << endl; 
            }
        }
    }
    
    return 0;
}


/*
 Shape::Shape()
 
 Initializes a shape.
 
 PRECONDITIONS:
 None.
 
 POSTCONDITIONS:
 shape is initialized with default values
 */
Shape::Shape()
{
    x = 0;
    y = 0;
    r = 0;
    type = 'P';
}


/*
 Shape::print()
 
 Prints the shape defined in the instance
 of the Shape class.
 
 PRECONDITIONS:
 Shape is initialized.
 
 POSTCONDITIONS:
 Shape data is printed to stdout
 @returns nothing
 */
void Shape::print()
{
    switch( type )
    {
        case 'P':
            cout << "Point " << "(" << x << "," << y << ")";
            break;
        case 'S':
            cout << "Square of side " << r << " with lower left corner " << "(" << x << "," << y << ")";
            break;
        case 'C':
            cout << "Circle of radius " << r << " and center " << "(" << x << "," << y << ")";
            break;
        default:
            cout << "Invalid shape";
    }
}


/*
 Shape::isInside()
 
 Determines if the shape defined by the class
 instance is inside another shape.
 
 PRECONDITIONS:
 Both shapes initialized
 @param a  A shape instance to compare
 
 POSTCONDITIONS:
 @returns true  if the shape in this instance is inside
                the shaped passed.  Otherwise, false.
 */
bool Shape::isInside( Shape a )
{
    // these are used for one of the cases to represent points
    // it seemed more efficient than creating 4 Shape objects
    // but we could have...
    int pt1x;
    int pt1y;
    int pt2x;
    int pt2y;
    int pt3x;
    int pt3y;
    int pt4x;
    int pt4y;
    
    // cases   
    // p contains in p
    // p contains in c   | pc | <= r
    // p contains in s
    // c contains in p (false )
    // c contains in c
    // c contains in s
    // s contains in p  (false )
    // s contains in c
    // s contains in s
   
    /* is the shape contained in this object instance a
      point, circle or square = type */ 
    switch ( type )
    {
        case 'P':    // this object is a point
            if ( a.getType() == 'P' )
            {
                if ( x == a.getX() && y == a.getY() )
                    return true;
                else
                    return false;
            } 
            else if ( a.getType() == 'S' )
            {
                if ( x <= a.getX() + a.getSide() && x >= a.getX() 
                    &&  y <= a.getY() + a.getSide() && y >= a.getY() )
                    return true;
                else
                    return false;
            } 
            else if ( a.getType() == 'C' )
            {
                // is the point inside a circle?
                if ( x * x + y * y < a.getRadius() )
                
                    /*
                if ( a.getX() + a.getRadius() >= x && a.getX() - a.getRadius() <= x 
                     && a.getY() + a.getRadius() >= y && a.getY() - a.getRadius() <= y ) */
                    return true;
                else
                    return false; 
            }
        
            break;
        
        case 'S':   // this object is a square
            if ( a.getType() == 'P' )
            {
                return false;
            }
            else if ( a.getType() == 'S' )
            {
                // is our square inside another square?

                if ( getRadius() < a.getRadius() )
                {
                    if ( x >= a.getX() && y >= a.getY()  && x <= a.getX() + a.getRadius() && 
                        y <= a.getY() + a.getRadius() )
                        return true;
                    else
                        return false; 
                } 
                else if ( getRadius() == a.getRadius() )
                {
                    if ( x == a.getX() && y == a.getY() )
                        return true;
                    else
                        return false;
                }
                else
                {
                    return false;
                }
            }
            else if ( a.getType() == 'C' )
            {
                // square inside a circle.
                // the distance formula between the center
                // of the circle and each corner point
                // of the square should work here.
                
                double d1;
                double d2;
                double d3;
                double d4;
                int crad;
                
                crad = a.getRadius();  // just to make the code easier to read below
                
                d1 = sqrt( pow( static_cast<double>(x - (a.getX() - crad)), 2) + 
                           pow(static_cast<double>( y - (a.getY() - crad)), 2 ) );
                
                d2 = sqrt( pow( static_cast<double>(x + r - (a.getX() - crad)), 2) + 
                           pow( static_cast<double>(y - (a.getY() - crad)), 2 ) );
                
                d3 = sqrt( pow( static_cast<double>(x - (a.getX() - crad)), 2) + 
                           pow( static_cast<double>(y + r - (a.getY() - crad)), 2 ) );
                
                d4 = sqrt( pow( static_cast<double>(x + r - (a.getX() - crad)), 2) + 
                           pow( static_cast<double>(y + r - (a.getY() - crad)), 2 ) );
                
               /*  for debugging 
                cout << "d1: " << d1 << endl;
                cout << "d2: " << d2 << endl;
                cout << "d3: " << d3 << endl;
                cout << "d4: " << d4 << endl;
                cout << "circle rad: " << crad * 2 << endl; */
                
                // if the distance is less than the diameter in all four cases,
                // we are inside.
                if (  d1 < crad * 2 && d2 < crad * 2 && d3 < crad * 2 && d4 < crad * 2 )
                    return true;
                else
                    return false;
            }
        
            break;
        
        case 'C':
            if ( a.getType() == 'P' )
            {
                return false;
            }
            else if ( a.getType() == 'S' )
            {
                // is the circle in a square?
           
                // left pt
                pt1y = (a.getY() + a.getRadius()) / 2;
                pt1x = a.getX();

                // top pt
                pt2x = (a.getX() + a.getRadius()) / 2;
                pt2y = (a.getY() + a.getRadius());

                // right pt
                pt3y = (a.getY() + a.getRadius()) / 2;
                pt3x = (a.getX() + a.getRadius());

                // bottom pt
                pt4x = (a.getX() + a.getRadius()) / 2;
                pt4y = a.getY();
                
                /*
                cout << "is the circle in a square?" << endl;
                cout << print << end;
                cout << " is this in " << a.print(); */

                if ( x + r <= pt3x &&  y + r <= pt2y && y - r >= pt4y && x - r >= pt1x )
                    return true;
                else
                    return false; 
            }
            else if ( a.getType() == 'C' )
            {
                // is the circle in another circle
                
                // if the radius is equal, then they must
                // have the same center point to be inside
                // each other.
                if ( r == a.getRadius() )
                    if ( x == a.getX() && y == a.getY() )
                        return true;
                    else
                        return false;

                // The radius must be smaller if we get here to
                // be inside.  Now we must look for overlaping
                // circles.
                if ( (r < a.getRadius()) && (x + r < a.getX() + a.getRadius()) &&
                     (x - r > a.getX() - a.getRadius()) && 
                     (y + r < a.getY() + a.getRadius()) && 
                     (y - r > a.getY() - a.getRadius()) )

                    return true;
                else
                    return false;
                     
            }
        
            break;
    }

    // we should never get here
    // it was useful during debugging so it would compile
    return false;
}


/*
 Shape::set( char mytype, int myx, int myy, int myrad )
 
 Alters the state of the class with new
 coordinates and a new radius.  Can also
 change the type of shape.
 
 PRECONDITIONS:
 @param mytype  A char representing the type (P=point, S=square, C=circle)
 @param myx     X-coordinate as an integer
 @param myy     Y-coordinate as an integer
 @param myrad   Radius/Side as an integer
 
 POSTCONDITIONS:
 object instance altered to new state.
 @returns nothing
 */
void Shape::set( char mytype, int myx, int myy, int myrad )
{
    type = mytype;
    x = myx;
    y = myy;
    r = myrad;
}


/*
 Shape::set( int myx, int myy )
 
 Alters the state of the class with new
 coordinates.  This version assumes
 that we are dealing with a Point.
 
 PRECONDITIONS:
 Assumes this is a point. (no type or radius required)
 @param myx     X-coordinate as an integer
 @param myy     Y-coordinate as an integer

 
 POSTCONDITIONS:
 Object instance setup to be a point (x,y)
 @returns nothing
 */
void Shape::set( int myx, int myy )
{
    type = 'P';  // it must be a point
    x = myx;
    y = myy;
}

/*
 Shape::getX()
 
 Retrieves the x coordinate value
 
 PRECONDITIONS:
 object initialized
 
 POSTCONDITIONS:
 @returns x coordinate as an integer
 */
int Shape::getX()
{
    return x;
}


/*
 Shape::getY()
 
 Retrieves the y coordinate value
 
 PRECONDITIONS:
 object initialized
 
 POSTCONDITIONS:
 @returns y coordinate as an integer
 */
int Shape::getY()
{
    return y;
}


/*
 Shape::getRadius()
 
 Retrieves the radius of the shape.
 
 Note: this is the same as getSide()
       but by making it seperate we could
       change the implementation of a
       circle or square later.
 
 PRECONDITIONS:
 object initialized
 
 POSTCONDITIONS:
 @returns radius as an integer
 */
int Shape::getRadius()
{
    return r;
}


/*
 Shape::getSide()
 
 Retrieves the side length of the shape.
 
 Note: this is the same as getRadius()
 but by making it seperate we could
 change the implementation of a
 circle or square later.
 
 PRECONDITIONS:
 object initialized
 
 POSTCONDITIONS:
 @returns the side length as an integer
 */
int Shape::getSide()
{
    return r;
}


/*
 Shape::getType()
 
 Retrieves the type of shape.
 
 PRECONDITIONS:
 object initialized
 Shape type set.
 
 POSTCONDITIONS:
 @returns type of shape as a character (P, S, or C)
 */
char Shape::getType()
{
    return type;
}
