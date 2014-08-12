//  name: Lucas Holt
//  asg#: Lab07
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM  Nov 13, 2003
 
/*
    Creates a deck of playing cards and allows you to manipulate the deck
    by shuffling and sorting the deck.  The deck can be printed to the
    console.
*/

#include <iostream>
#include <cmath>  // rand()
#include <ctime>  // time()
using namespace std;

const int DECK_SIZE = 52;
const int CLUBS = 0;
const int SPADES = 1;
const int DIAMONDS = 2;
const int HEARTS = 3;

/*
    Card Class
    
    Represents a single playing card.
*/
class Card
{
private:
    int faceValue;
    int suit;

public:
    Card( int myFaceValue, int mySuit );
    Card( int cardNumber );
    Card();
    void printCard();
    void printFaceValue();
    void printSuit();
    int compare( Card card2 ); 
    int getFaceValue();
    int getSuit();
};

/*
    Deck Class
    
    Initializes and stores and deck of playing cards.
    The deck can be shuffled and sorted or printed
    to the console.
*/
class Deck
{
private:
    Card deck[DECK_SIZE];
    int getRand( int );

public: 
    Deck(); 
    void shuffle();
    void sort( int nCards );
    void printDeck( int numCards );
    void printDeck();
};

int main()
{
    Deck myDeck;
    int n;  // number of cards to sort and print
    
    srand( time(0) );  // initialize the random seed

    myDeck.printDeck();
    myDeck.shuffle();
    myDeck.printDeck();

    // get user input
    cout << "Please input the number of cards to sort: ";
    cin >> n;
    cout << endl;
    
    // sort and print a subset of the deck.
    myDeck.sort( n );
    myDeck.printDeck( n );

    return 0;
}


/*
    Card::Card()
    
    Initializes a playing card
    
    Preconditions:
    None.
    
    Postconditions:
    card is initialized with default values
*/
Card::Card()
{
    Card( 12, 1 );  // face, suit 
}

/*
    Card::Card()
    
    Initializes a playing card
    
    Preconditions:
    @param cardNumber Card represented as a single integer
    
    Postconditions:
    card is initialized with specified value
*/
Card::Card( int cardNumber )
{
    faceValue = cardNumber % 13;
    suit = cardNumber % 4;
} 

/*
    Card::Card()
    
    Initializes a playing card
    
    Preconditions:
    @param myFaceValue  playing card's face value as int
    @param mySuit  playing card's suit as integer
    
    Postconditions:
    card is initialized with specified values
*/
Card::Card( int myFaceValue, int mySuit )
{
    faceValue = myFaceValue;
    suit = mySuit;
}


/*
    Card::printCard()
    
    Prints the face value and suit of the card
    
    PRE CONDITIONS:
    faceValue and suit are set in the class instance.
    
    POST CONDITIONS:
    Prints face value and suit to stdout.
    @returns nothing
*/
void Card::printCard()
{
    printFaceValue();    
    cout << " of ";
    printSuit();

} 

/*
    Card::printFaceValue()
    
    Prints the face value
    
    PRE CONDITIONS:
    faceValue is set in the class instance
    
    POST CONDITIONS:
    Prints face value to stdout.
    @returns nothing
*/
void Card::printFaceValue()
{
    
    switch ( faceValue )
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
    Card::printFaceSuit()
    
    Prints the suit of the playing card
    
    PRE CONDITIONS:
    suit is set in the class instance
    
    POST CONDITIONS:
    Prints suit to stdout.
    @returns nothing
*/
void Card::printSuit()
{
    
    switch ( suit )
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
    Card::compare( Card card2 )
    
    Compares the two playing cards face value.
    
    PRE CONDITIONS:
    card instance is initialized properly.
    @param card2  a second playing card instance to examine.
    
    POST CONDITIONS:
    If card 1 is greater than card 2, 1 is returned.
    If card 2 is greater than card 1, -1 is returned
    if they are equal, 0 is returned.
    @returns an integer representing card1 >, < or = card 2
*/
int Card::compare( Card card2 )
{
    int c2 = card2.getFaceValue();
    int c1 = getFaceValue();
    
    if ( c1 > c2 )
        return 1;
    else if ( c1 < c2 )
        return -1;
    else
        return 0;
}

/*
    Card::getFaceValue()
    
    Retrieves internal face value
    
    PRE CONDITIONS:
    faceValue is set in the class instance
    
    POST CONDITIONS:
    @returns card's face value as an integer
*/
int Card::getFaceValue()
{
    return faceValue;
}

/*
    Card::getSuit()
    
    Retrieves internal suit value
    
    PRE CONDITIONS:
    suit is set in the class instance
    
    POST CONDITIONS:
    @returns Card's suit value as an integer
*/
int Card::getSuit()
{
    return suit;
}

/*
    Deck::Deck()
    
    Initializes the deck with default card values (unique card)
    
    PRE CONDITIONS:
    none.
    
    POST CONDITIONS:
    deck is initialized and ready to use
*/
Deck::Deck()
{
    // initialize the deck
    for ( int i = 0; i < DECK_SIZE; i++ )
        deck[i] = Card(i);
}

/*
    Deck::shuffle()
    
    Shuffles the deck of playing cards
    
    PRE CONDITIONS:
    deck is initialized.
    
    POST CONDITIONS:
    deck is altered.
    cards in deck are shuffled in "random" order.
    @returns nothing
*/
void Deck::shuffle()
{
    Card myCard;
    int randIndex;

    for ( int i = 0; i < DECK_SIZE; i++ )
    {
        // randomly select an index
        randIndex = getRand( DECK_SIZE );
        myCard = deck[randIndex];
        
        // perform the swap
        deck[randIndex] = deck[i]; 
        deck[i] = myCard;
    }

}

/*
    Deck::sort( int nCards )
    
    Sorts n cards in the deck starting with the first card.
    All cards can be shuffled by specifying the deck size.
    
    PRE CONDITIONS:
    deck is initialized.
    @param nCards An integer representing the n cards to sort
    
    POST CONDITIONS:
    deck is sorted by face value. (altered)
    @returns nothing
*/
void Deck::sort( int nCards )
{
    Card tmpCard;
    
    for ( int i = 0; i < nCards - 1; i++ ) 
    {
        for ( int j = 0; j < nCards - 1 - i; j++ )
            // compare face value of two neighboring cards.
            if ( deck[j+1].getFaceValue() < deck[j].getFaceValue() ) 
            {  
                tmpCard = deck[j];   // swap deck[j] and deck[j+1] 
                deck[j] = deck[j+1];
                deck[j+1] = tmpCard;
            }
    }
}

/*
    Deck::printDeck()
    
    Prints the entire deck of playing cards
    
    PRE CONDITIONS:
    deck is initialized.
    
    POST CONDITIONS:
    deck is printed to stdout.
    @returns nothing
*/
void Deck::printDeck()
{
    printDeck( DECK_SIZE );  // whole deck is printed.
}

/*
    Deck::printDeck( int numCards )
    
    Prints partial deck of playing cards
    
    PRE CONDITIONS:
    deck is initialized.
    @param numCards the number of cards to print
    
    POST CONDITIONS:
    partial deck is printed to stdout.
    @returns nothing
*/
void Deck::printDeck( int numCards )
{
    for ( int i = 0; i < numCards; i++ )
    {
        deck[i].printCard();
            
        // four cards per line with commas in between them
        if ( i % 4 == 3 )
            cout << endl;
        else
            cout << ", ";
    }
    
    cout << endl;
}

/*
    Deck::getRand( int scale )
    
    Generates a random integer scaled with
    the specified value. 0 to scale -1
    
    PRE CONDITIONS: 
    @param scale  Value to scale the random number to.  Should be less
                  than RAND_MAX to be useful.
    
    POST CONDITIONS: 
    @returns random number scaled as an integer
*/
int Deck::getRand( int scale )
{
  return rand() % scale;
}
