/*

Author: Andy Perrett June 2019
Course: BSc Computer Science Level 1

*/

#ifndef STACK_H
#define STACK_H

// my classes
#include "Place.h"

class Stack
{
    public:
        Stack();
        void Push(Place);
        Place Pop();
        Place Top();
        bool IsEmpty();

        virtual ~Stack();

    protected:

    private:
        int _top;
        Place stack[1000];
};

#endif // STACK_H
