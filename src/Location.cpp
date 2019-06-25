/*

Author: Andy Perrett June 2019
Course: BSc Computer Science Level 1

*/

#include "Location.h"

Location::Location()
{
    // Constructor
    Visited = false;
    Doors = (uint8_t)0b00000000;
}

Location::Location(bool visited, uint8_t doors)
{
    // Constructor
    Visited = visited;
    Doors = doors;
}

Location::~Location()
{
    // Destructor
}
