//  name: Lucas Holt
//  asg#: Lab04
//  lab section: 10:00 AM, Thursday
//  lab instructor: Yan Lu
//  due date: 10:00 AM Oct 23, 2003
 
/*
    Fishing Trip Simulation

    Simluates a fishing trip where a person makes serveral choices and
    must catch dinner for his family and friends. 

    Choices include the number of lures to bring with you, the number
    of families you have invited, location to fish in, reel speed,
    and when to give up.
*/
 
#include <iostream>
#include <cstdlib>   // for exit()
#include <cmath>     // for rand?
#include <ctime>     // for c time() function
using namespace std;

double getRand();
void getBaseInput( int& nfamilies, int& nlures );
void getLocation( char& location );
void doCast( int& lures, int& fish, int& gfish, int& minutes );
void castInDeep( int& lures, int& fish, int& gfish, int& minutes );
void castInShallow( int& lures, int& fish, int& gfish, int& minutes );
void castInLogs( int& lures, int& fish, int& gfish, int& minutes );
void castInWeeds( int& lures, int& fish, int& gfish, int& minutes );
void reelIn( bool isGigantic, char location, int& fish, int& gfish, int& minutes );
void loseLure( char location, int& lures );
void report( int& lures, int& fish, int& gfish, int& minutes );
void gameOver();
int calcServings( int fish, int gfish );
bool isTimeUp( int minutes );
void addTime( int& minutes, int addmin );

int main()
{
    int families = 0;
    int lures = 0;
    int fish = 0;
    int gfish = 0;
    int minutes = 0;
    
    srand( time(0) );  // initialize random functions.

    getBaseInput( families, lures );

    /* start fishing */
    do
    {

        doCast( lures, fish, gfish, minutes );
        report( lures, fish, gfish, minutes );

    } while ( !isTimeUp( minutes ) || lures == 0 || ( calcServings( fish, gfish ) < families ) );
    
    gameOver();
    
    return 0;
}

/* 
    getRand(); 
    Generates a random number between 0 and 1 as a double.

    PRE CONDITIONS: 
    srand was called once in the program.
    
    POST CONDITIONS: 
    @returns random # as double
*/
double getRand()
{
    return ( static_cast<double> (rand() / RAND_MAX) );
}

/*
    getBaseInput( int& nfamilies, int& nlures )
    
    Asks the user for the number of guest families and lures.
    This function assumes your family will need to eat.
    
    PRE CONDITIONS: 
    @param nfamilies  number of guest families you must feed [1,5]  (byref)
    @param nlures     number of lures to take with you [1,5] (byref)
    
    POST CONDITIONS: 
    nfamilies and nlures receive new values.
    @returns nothing
*/
void getBaseInput( int& nfamilies, int& nlures )
{

    while ( nfamilies < 1 || nfamilies > 5 )
    {
        cout << "Input the number of guest familes between 1 and 5: ";
        cin >> nfamilies;
        
        if ( nfamilies < 1 || nfamilies > 5 )
            cout << "Error: The number of families must be between 1 and 5" << endl;
    }
    
    while ( nlures < 1 || nlures > 5 )
    {
        cout << "Input the number of lures to take with you (Max 5): ";
        cin >> nlures;
        
        if ( nlures < 1 || nlures > 5 )
            cout << "Error: The number of lures must be between 1 and 5" << endl;
    }

}

/*
    getLocation( char& location )
    
    Displays a menu on the console asking for the location
    to fish.
    
    PRE CONDITIONS:
    @param location  location such as swap, logs, etc. categorized as a single character (byref)
    
    POST CONDITIONS:
    location variable is altered in caller.
    @returns nothing
*/
void getLocation( char& location )
{
    do 
    {
        cout << endl << "Select where you want to cast:" << endl;
        cout << "  (d)\t Deep" << endl;
        cout << "  (l)\t Logs" << endl;
        cout << "  (s)\t Shallow" << endl;
        cout << "  (w)\t Weeds" << endl;
        cout << endl;
        cout << "  (q)\t Quit" << endl;
        
        cout << "choice: ";
        cin >> location;
        // debug cout << location << endl;
        
        /* 
            Initially i could test for not equal in the 
            while loop but for some reason it broke.
            this solved the problem on mac os x and freebsd.
        */
        if ( location == 's' )
            break;
        else if ( location == 'd' )
            break;
        else if ( location == 'l' )
            break;
        else if ( location == 'w' )
            break;
        else if ( location == 'q' )
            break;
        
    } while ( true );
}

/*
    doCast( int& lures, int& fish, int& gfish, int& minutes )
    
    A basic controller fucntion.  makes the appropriate calls
    to get the location in the lake to fish, and directs
    the program flow to the correct cast function
    
    PRE CONDITIONS:
    @param lures number of lures remaining (byref)
    @param fish  number of fish caught (byref)
    @param gfish number of gigantic fish caught (byref)
    @param gfish number of minutes elapsed. (byref)
    
    POST CONDITIONS:
    Several variables could be altered depending on 
    control flow.  minutes is guaranteed to be altered.
    @returns nothing
*/
void doCast( int& lures, int& fish, int& gfish, int& minutes )
{
    char location;
    getLocation( location );
    
    switch ( location )
    {
        case 'd': 
            castInDeep( lures, fish, gfish, minutes );
            break;
        case 's': 
            castInShallow( lures, fish, gfish, minutes );
            break;
        case 'l': 
            castInLogs( lures, fish, gfish, minutes );
            break;
        case 'w': 
             castInWeeds( lures, fish, gfish, minutes );
             break;
        case 'q':
            // we want to quit.  TODO: find cleaner way
            report( lures, fish, gfish, minutes );
            gameOver();
            exit(0);
            // don't need to break we called exit.
        default:
             cout << "Error Casting" << endl;
    }
    
    addTime( minutes, 30 );
}

/*
    castInDeep( int& lures, int& fish, int& gfish, int& minutes )
    
    Calculates the chances of catching a fish, losing a lure
    or catching a gigantic fish in deep water.
    
    PRE CONDITIONS:
    @param lures number of lures remaining (byref)
    @param fish number of fish caught
    @param gfish number of gigantic fish caught
    @param minutes elapsed number of minutes
    
    POST CONDITIONS:
    Depending on control flow, the fish or gfish params could 
    be incremented.  lure could be decremented.
    @returns nothing
*/    
void castInDeep( int& lures, int& fish, int& gfish, int& minutes )
{
    double myrand;

    myrand = getRand();

    if ( myrand <= .2 )
        reelIn( false, 'd', fish, gfish, minutes );  // standard fish
    else if ( myrand <= .3 )
        loseLure( 'd', lures );
    else if ( myrand <= .4 )
        reelIn( true, 'd', fish, gfish, minutes );  // gigantic fish
    
}

/*
    castInShallow( int& lures, int& fish, int& gfish, int& minutes )
    
    Calculates the chances of catching a fish, losing a lure
    or catching a gigantic fish in shallow water.
    
    PRE CONDITIONS:
    @param lures number of lures remaining (byref)
    @param fish number of fish caught
    @param gfish number of gigantic fish caught
    @param minutes elapsed number of minutes
    
    POST CONDITIONS:
    Depending on control flow, the fish param could 
    be incremented.
    @returns nothing
*/    
void castInShallow( int& lures, int& fish, int& gfish, int& minutes )
{
    double myrand;

    myrand = getRand();

    if ( myrand <= .15 )
        reelIn( false, 's', fish, gfish, minutes );  // standard fish
}

/*
    castInLogs( int& lures, int& fish, int& gfish, int& minutes )
    
    Calculates the chances of catching a fish, losing a lure
    or catching a gigantic fish in loggy water.
    
    PRE CONDITIONS:
    @param lures number of lures remaining (byref)
    @param fish number of fish caught
    @param gfish number of gigantic fish caught
    @param minutes elapsed number of minutes
    
    POST CONDITIONS:
    Depending on control flow, the fish param could 
    be incremented.  lure could be decremented.
    @returns nothing
*/  
void castInLogs( int& lures, int& fish, int& gfish, int& minutes )
{
    double myrand;

    myrand = getRand();

    if ( myrand <= .55 )
        reelIn( false, 'l', fish, gfish, minutes );  // standard fish
    else if ( myrand <= .95 )
        loseLure( 'l', lures );
}

/*
    castInWeeds( int& lures, int& fish, int& gfish, int& minutes )
    
    Calculates the chances of catching a fish, losing a lure
    or catching a gigantic fish in water with weeds.
    
    PRE CONDITIONS:
    @param lures number of lures remaining (byref)
    @param fish number of fish caught
    @param gfish number of gigantic fish caught
    @param minutes elapsed number of minutes
    
    POST CONDITIONS:
    Depending on control flow, the fish param could 
    be incremented.  lure could be decremented.
    @returns nothing
*/  
void castInWeeds( int& lures, int& fish, int& gfish, int& minutes )
{
    double myrand;

    myrand = getRand();

    if ( myrand <= .25 )
        reelIn( false, 'w', fish, gfish, minutes );  // standard fish
    else if ( myrand <= .4 )
        loseLure( 'w', lures );
}

/*
    reelIn( bool isGigantic, char location, int& fish, int& gfish, int& minutes )
    
    Asks the user if they want to reel in fast or slow with a console menu.
    Then using a random number, determines if the user caught a fish or
    struck out.  It takes longer to slow lure so minutes can be changed.
    
    PRE CONDITIONS:
    @param isGigantic  is this fish gigantic? (deep water only)
    @param location    Deep, shallow, etc.
    @param fish        number of fish caught (byref)
    @param gfish       number of gigantic fish caught (byref)
    @param minutes     elapsed number of minutes (byref)
    
    POST CONDITIONS:
    If the reel is slow, minutes is increased.  fish and gfish can also
    be incremented.
    @returns nothing
*/  
void reelIn( bool isGigantic, char location, int& fish, int& gfish, int& minutes ) 
{
    double myrand;
    char reelspeed;
    
    do
    {
        /* get reel speed from user */
        cout << endl << "Do you want to reel the fish in fast or slow?" << endl;
        cout << "  (f)\t Fast" << endl;
        cout << "  (s)\t Slow" << endl;
        cout << "choice: ";
        cin >> reelspeed;
        
        /* same as before
           while ( reelspeed != 'f' || reelspeed != 's' )
           worked for some time and then stopped.
        */
        
        if ( reelspeed == 'f' )
            break;
        else if ( reelspeed == 's' )
            break;
        
    } while ( true );
    
    myrand = getRand();
    
     switch ( location )
    {
        case 'd': 
            if ( reelspeed == 'f' && myrand > .3 ) 
            {
                if ( isGigantic == true )
                    gfish++;
                else
                    fish++;
            }
            else if ( reelspeed == 's' )
            {
                if ( myrand > .15 )
                    if ( isGigantic == true )
                        gfish++;
                    else
                        fish++;
                
                 addTime( minutes, 30 );
            }
                    
            break;
        
        case 's': 
             if ( reelspeed == 'f' )
             {
                 // this must be a seperate if
                 // so the else only occurs when 
                 // reelspeed = 's'
                 if ( myrand > .05 )
                     fish++;
             }    
             else
             {
                 fish++; // reel speed is slow so we are guaranteed the fish
                 addTime( minutes, 30 );
             }
                 
             break;
        
        case 'l': 
            if ( reelspeed == 'f' && myrand > .35 )
            {
                fish++;
            }
            else if ( reelspeed == 's' )
            {
                if ( myrand > .10 )
                    fish++;
                    
                addTime( minutes, 30 );
            }
            break;    
        
        case 'w':
            if ( reelspeed == 'f' && myrand > .1 )
            {
                fish++;
            }
            else if ( reelspeed == 's' )
            {
                if ( myrand > .05 )
                    fish++;
                    
                addTime( minutes, 30 );
            }
 
            break; 
        
        default:
             cout << "Error Reeling" << endl;
    }

}

/*
    loseLure( char location, int& lures )
    
    Uses a random number to determine the
    chance of losing a lure.  If you lose this 
    bet, lures is decremented.
    
    PRE CONDITIONS:
    @param location  current location such as deep, shallow, etc.
    @param lures     number of lures remaining.  should be > 0 (byref)
    
    POST CONDITIONS:
    lures might be altered with a smaller value.
    @returns nothing
    
*/
void loseLure( char location, int& lures )
{
    double myrand;
    myrand = getRand();
    
    switch ( location )
    {
        case 'd':
            if ( myrand <= .1 )
                lures--;
            break;
        case 'l':
            if ( myrand <= .4 )
                lures--;
            break;
        case 'w':
            if ( myrand <= .15 )
                lures--;
            break;
    }
}

/*
    report( int& lures, int& fish, int& gfish, int& minutes )
    
    Prints out the status of the fishing trip including
    the current time, number of lures, and number/type of
    fish caught.  
    
    PRE CONDITIONS:
    @param lures  number of lures remaining (byref)
    @param fish   number of fish caught (byref)
    @param gfish  number of gigantic fish caught (byref)
    @param minutes time elapsed. (byref)
    
    POST CONDITIONS:
    Console is updated with current values of these fields.
    Time is converted into H:MM AM/PM format.
    @returns nothing
*/
void report( int& lures, int& fish, int& gfish, int& minutes )
{
    int servings = 0;
    int hours;
    int hours_12;
    
    hours = ( (minutes + 390) / 60 );
    hours_12 = hours % 12;
    
    if ( hours_12 == 0 )
        hours_12 = 12;  // so 12:00 works right
        
    cout << endl << "Fishing Trip Status" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "fish: " << fish << endl;
    cout << "gigantic fish: " << gfish << endl;
    
    // minutes plus 390 == 6:30 AM
    cout << "time: " << hours_12 << ":" << (minutes + 390) % 60;
    
    // this works in the constraints of the program requirements
    if ( hours >= 12 )
        cout << " PM";
    else
        cout << " AM";
    
    cout << endl; 
    // cout << "debug time: " << minutes << endl;
    cout << "lures remaining: " << lures << endl << endl;
    
    servings = calcServings( fish, gfish );
    
    switch ( servings )
    {
        case 0:
            cout << "I can not feed anyone." << endl;
            break;
        case 1:
            cout << "I can feed my own family." << endl;
            break;
        default:
            cout << "I can feed my own family and " << servings - 1 << " guest families." << endl; 
    }
    
    cout <<  endl;
}

/*
    gameOver()
    
    Displays game over message
    
    PRE CONDITIONS:
    none.
    
    POST CONDITIONS:
    console updated with message
    @returns nothing
*/
void gameOver()
{
    cout << "Game Over." << endl;
}

/*
    calcServings( int fish, int gfish )
    
    Calculates the serving size for fish and
    gigantic fish as one value.
    
    PRE CONDITIONS:
    @param fish  number of fish caught
    @param gfish number of gigantic fish caught
    
    POST CONDITIONS:
    @returns the number of servings as an integer
*/
int calcServings( int fish, int gfish )
{
    // gigantic fish are worth 3 normal fish currently
    return ( fish + gfish * 3 );
}

/*
    isTimeUp( int minutes )
    
    Determines if time has elapsed for the fishing trip.
    
    PRE CONDITIONS:
    @param minutes time elapsed
    
    POST CONDITIONS:
    @returns a bool where true means its time to go home, false means keep fishing.
*/
bool isTimeUp( int minutes )
{
    // 600 == 4:30
    if ( minutes >= 600 )
        return true;
    else
        return false;
}

/*
    addTime( int& minutes, int addmin )
    
    Add more minutes to the storage for
    minutes since the trip started.
    
    PRE CONDITIONS:
    @param minutes  time elapsed (byref)
    @param addmin   number of minutes to add to time  (addmin > 0)
    
    POST CONDITIONS:
    minutes is altered
    @returns nothing
*/
void addTime( int& minutes, int addmin )
{
    minutes += addmin;    
}
