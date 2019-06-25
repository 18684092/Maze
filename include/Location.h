/*

Author: Andy Perrett June 2019
Course: BSc Computer Science Level 1

*/

#ifndef LOCATION_H
#define LOCATION_H

// standard objects
#include <cstdint> // uint8_t

class Location
{
    public:
        // Holds details of whether the location has been visited
        // Required for Recursive Backtracker
        bool Visited;

        // Each bit is assigned as follows
        // N NE E SE S SW W NW
        uint8_t Doors;

        // Constructors
        Location();
        Location(bool, uint8_t);

        virtual ~Location();

    protected:

    private:
};

#endif // LOCATION_H
