/*
    cs111 MW 4:00 PM
    author: Lucas Holt
    group: 8
*/

/* 
    Substring
    
    takes a character array and looks for
    the substring presented in a second array
    
    This code works by iterating through the first string and comparing the value
    to the first character of the second string.  If there is a match,
    a variable called index is incremented so the second character of the
    second string is checked on the next run through.  If the second character
    is a match its incremented again, otherwise the index variable is 
    reset to zero so we can compare from the beginning of the string again.
    
    The incrementing of index depending on the state in the loop is the
    reason i don't need a second for loop.  (index is for list2 only)
    
    I used this approach because i was thinking with two for loops
    i would be comparing charaters twice.  If i understood the
    two loop approach, i'd be reading ahead on the first string
    in the inner loop and then escaping back out each time.
*/

#include <iostream>
using namespace std;

int main()
{
    const int L1 = 5;
    const int L2 = 2;
    
    // I didn't use the null character on these because we hadn't covered it
    // at the time it was written.  The problem's example didn't use them
    // either.  The code would still work with an adjustment for the length
    // in two places if a null was used.
    char list1[L1] = { 'l', 'u', 'c', 'a', 's' };
    char list2[L2] = { 'c', 'a' };
    int i;  // position in list1 during loop
    int index = 0;  // position in list2 during the for loop
    int firstOccur = 0; // position in list1 where the substring starts (list2)
    bool exists = false;  // the substring exists in list1 if this is true
    bool process = false;  // flag to determine if we are comparing list2's first character to list1's
                           // at list1[i]
    
    for ( i = 0; i < L1; i++ )
    {
        // compare characters in both lists.. the first time through
        // both i and index are zero
        if ( list1[i] == list2[index] )
        {
            if ( process == false )  // we need to compare the first character of list2 to whatever in list1
            {
                firstOccur = i;  // if there is a match, this needs to be set to the beginning of substring in list2
                index++;  // so we can check the second character in list2 with list1's next character
                process = true;
            } else {
                // last time through we had a match so we are comparing the second or later charaters
                // index > 0
                if ( index < L2 -1 )
                {
                    index++;
                } else {
                    // index's length is equal to L2 so we are at the end of the string
                    // set our flag and exit the loop because we are done.
                    exists = true;
                    break;
                }
            }
        } else {
            // we hit this code when the character in list1 and list2 don't equal
            firstOccur = 0;
            index = 0;  // we need to compare the first character of list2 again
            process = false;
        }
    }
    
    // print out a status message telling us if we found the substring or not.
    if ( exists == true )
        cout << "It is a substring and the first occurance begins at " << firstOccur  << endl;
    else
        cout << "Substring does not exist" << endl;
    
    return 0;
}