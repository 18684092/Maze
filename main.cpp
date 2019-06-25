/*

Author: Andy Perrett June 2019
Course: BSc Computer Science Level 1

*/

// My classes
#include "Place.h"
#include "Stack.h"
#include "RecursiveBackTracker.h"


using namespace std;

int main()
{
    // Set up size of maze y, x - needs to fit into screen 13 x 17 good for 640 by 480
    RecursiveBackTracker BT(13,17);

    // Display it using SDL2 library
    BT.DisplayMaze();

    return 0;
}
