//  name: Lucas Holt
//  asg#: Lab05
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM Oct 30, 2003

/*
    Poker hand tester
    
    Tests a hand of five cards to see if it is a full house.  
    Prints out the result of these tests over 100,000 hands.
    
    The directions on implementation were contradictory.  I 
    tried to implement the required functionality using
    the "tasks" section.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>  // rand() on some platforms
#include <ctime>  // c time() function
#include <iomanip>

using namespace std;

void initDeck( int[], int );
void printDeck( int[], int );
void printCard( int );
void printFaceValue( int );
void printSuit( int );
void shuffle( int[], int );
bool isFullHouse( int[], int );
void printFullHouse( int[], int );
void printStraight( int[], int );
int getRand( int );
int faceValueMatch( int[], int, int );

const int DECKSIZE = 52;
const int CLUBS = 0;
const int SPADES = 1;
const int DIAMONDS = 2;
const int HEARTS = 3;

int main()
{
    int A[DECKSIZE];
    
    srand( time(0) );  // initialize the random seed
    
    initDeck( A, DECKSIZE );  
    printDeck( A, DECKSIZE );
    
    // show that deck shuffling works.
    shuffle( A, DECKSIZE );
    printDeck( A, DECKSIZE );
    
    printFullHouse( A, DECKSIZE );

    return 0;
}

/*
    initDeck( int A[], int size )
    
    Initializes a deck of cards in a specific order.  Since
    the cards are stored as integers, the pattern
    counts from 2 to A four times (52 cards in a deck)
    
    PRE CONDITIONS: 
    @param A[]   Array of playing cards as integers
    @param size  number of playing cards in the array
    
    POST CONDITIONS: 
    Array of playing cards is altered with unique cards
    in each array element.
    @returns nothing
*/
void initDeck( int A[], int size )
{
    for ( int i = 0; i < size; i++ )
        A[i] = i;
        
    return;
}

/*
    printDeck( int A[], int size )
    
    Prints all the cards in the current deck
    in the order they appear. (52 cards in a deck)
    
    PRE CONDITIONS: 
    @param A[]   Array of playing cards as integers
    @param size  number of playing cards in the array
    
    POST CONDITIONS: 
    Cards are printed four per line to stdout.
    @returns nothing
*/
void printDeck( int A[], int size )
{
    cout << "current deck: \n\n";
    
    for ( int i = 0; i < size; i++ )
    {
        printCard( A[i] );
            
        // four cards per line with commas in between them
        if ( i % 4 == 3 )
            cout << endl;
        else
            cout << ", ";
    }
    
    cout << endl;
    
    return;
}

/*
    printCard( int card )
    
    Prints one playing card in the following format:
    3 of spades
    No newlines are used so this function is more
    reusable.
    
    PRE CONDITIONS: 
    @param card  Playing card's internal integer representation.
    
    POST CONDITIONS: 
    Card printed to stdout in specified format.
    @returns nothing
*/
void printCard( int card )
{
    printFaceValue( card );    
    cout << " of ";
    printSuit( card );
    
    return;
}

/*
    printFaceValue( int card )
    
    Prints the face value of the playing card.
    
    PRE CONDITIONS: 
    @param card  Playing card's internal integer representation.
    
    POST CONDITIONS: 
    Playing card's face value printed to stdout with
    a space before single character values to
    improve appearance.
    @returns nothing
*/
void printFaceValue( int card )
{

    int face = card % 13;  // get the face card value
    
    switch ( face )
    {
        case 0:
            cout << " 2";
            break;
        case 1:
            cout << " 3";
            break;
        case 2:
            cout << " 4";
            break;
        case 3:
            cout << " 5";
            break;
        case 4:
            cout << " 6";
            break;
        case 5:
            cout << " 7";
            break;
        case 6:
            cout << " 8";
            break;
        case 7:
            cout << " 9";
            break;
        case 8: 
            cout << "10";
            break;
        case 9: 
            cout << " J";
            break;
        case 10: 
            cout << " Q";
            break;
        case 11:
            cout << " K";
            break;
        case 12:
            cout << " A";
            break;
    }
    
    return;
}

/*
    printSuit( int card )
    
    Prints out the suit of a specific playing card.
    
    PRE CONDITIONS: 
    @param card  Playing card's internal integer representation.
    
    POST CONDITIONS: 
    Prints playing card suit to stdout
    @returns nothing
*/
void printSuit( int card )
{
    
    switch ( card % 4 )
    {
        case CLUBS:
            cout << "clubs";
            break;
        case SPADES:
            cout << "spades";
            break;
        case DIAMONDS:
            cout << "diamonds";
            break;
        case HEARTS:
            cout << "hearts";
            break;
    }
    
    return;
}

/*
    shuffle( int A[], int size )
    
    Shuffles playing cards into a "random" order
    stored as integers.
    
    PRE CONDITIONS: 
    @param A[]   Array of playing cards as integers
    @param size  number of playing cards in the array
    
    POST CONDITIONS: 
    Array of playing cards is altered.  Contents are 
    stored in a "random" order.
    @returns nothing
*/
void shuffle( int A[], int size )
{
    int card;
    int randIndex;

    for ( int i = 0; i < size; i++ )
    {
        // randomly select an index
        randIndex = getRand( size );
        card = A[randIndex];
        
        // perform the swap
        A[randIndex] = A[i]; 
        A[i] = card;
    }
    
    return;
}

/*
    getRand( int scale )
    
    Generates a random integer scaled with
    the specified value. 0 to scale -1
    
    PRE CONDITIONS: 
    @param scale  Value to scale the random number to.  Should be less
                  than RAND_MAX to be useful.
    
    POST CONDITIONS: 
    @returns random number scaled as an integer
*/
int getRand( int scale )
{
  return rand() % scale;
}

/*
    isFullHouse( int A[], int size )
    
    Determines if the first five cards
    in the array form a full house.  This
    was designed for the full deck to be
    passed, but a hand of five cards
    should work also.
    
    PRE CONDITIONS: 
    @param A[]   Array of playing cards as integers
    @param size  number of playing cards in the array
    
    POST CONDITIONS: 
    @returns true if the hand is a full house, false if its not.

    What is a full house?
    any five card hand such that two of the cards have the same face 
    value and the other three cards have the same face value.Ê 
    (Example:Ê 3 of spades, 3 of clubs, K of diamonds, K of spades, K of hearts).
*/
bool isFullHouse( int A[], int size )
{
    int i = 0;
    int numcard;
    bool fullhouse = false;  // takes a two card and three card to be true
    bool twocard = false;
    bool threecard = false;
    
    while ( i < 4 )  // 4 because we don't want to waste cpu time checking 1 card
    {
        numcard = faceValueMatch( A, size, i );
        
        if ( numcard == 2 )
            twocard = true;
        else if ( numcard == 3 )
            threecard = true;   
        
        i++;
        
        if ( twocard == true && threecard == true )
            break;
    }
    
    if ( twocard == true && threecard == true )
        fullhouse = true;
    
    return fullhouse;
}


/*
    faceValueMatch( int A[], int size, int start )
    
    Determines the number of matching cards in
    the first five cards of a deck or hand of five
    cards.  For example, there are two cards with
    the value 4 in a hand.  
    
    PRE CONDITIONS: 
    @param A[]   Array of playing cards as integers
    @param size  number of playing cards in the array
    @param start the card to start at in the array
    
    POST CONDITIONS: 
    @returns number of cards with a matching value starting at start.
*/
int faceValueMatch( int A[], int size, int start )
{
    int i;
    int numcard = 1; // we must have one to do the comarisons.. oops
    int cardvalue;
    
    // read in the first card and perform work
    // starting at the card proceeding it.
    i = 0;  
    cardvalue = A[start] % 13; // bug was here

    while ( size > i && i < 5 )
    {
        if ( i != start )
        {
            if ( cardvalue == A[i] % 13 )
            {
                numcard++;
                //cout << "card value: " << cardvalue << endl;
                //cout << "numcard: " << numcard << endl;
            }
        }
        i++;
    }

    return numcard;
}


/*
    printFullHouse( int A[], int size )

    Runs through hands looking for full houses
    and prints out those hands. 
    
    PRE CONDITIONS: 
    @param A[]   Array of playing cards as integers
    @param size  number of playing cards in the array
    
    POST CONDITIONS:
    Prints full house hands to stdout in addition
    to statistics.
    @returns nothing
*/
void printFullHouse( int A[], int size )
{
    int num_full_house = 0;
    
    for ( int i = 0; i < 100000; i++ )
    {
        shuffle( A, size );
    
        if ( isFullHouse( A, size ) == true )
        {
            num_full_house++;
            
            for ( int x = 0; x < 5; x++ )
            {
                 printCard( A[x] );
                 cout << ' ';
            }
                 
            cout << endl << endl;
        }

    }
   
    // print statistics
    cout << "Total number of full house hands: " << num_full_house << endl;
    
    cout.setf( ios::fixed );
    cout.setf( ios::showpoint );
    cout.precision( 2 );
    cout << "Probability of getting a full house: " << ( (static_cast<double>(num_full_house) / 100000) * 100 ) << '%' << endl;
    
    return;
}
