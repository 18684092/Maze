#include "Place.h"

Place::Place()
{
    // Constructor
    this->x = -1;
    this->y = -1;
}

Place::Place(int row, int col)
{
    // Constructor
    this->x = col;
    this->y = row;
}

Place::~Place()
{
    // Destructor
}
