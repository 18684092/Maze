/*

Author: Andy Perrett June 2019
Course: BSc Computer Science Level 1

*/


#include "Stack.h"


Stack::Stack()
{
    // Constructor
    _top = -1;
}

void Stack::Push(Place place)
{
    stack[++_top] = place;
}

Place Stack::Pop()
{
    if (IsEmpty())
    {
        return Place(-1, -1);
    }
    return stack[_top--];
}

Place Stack::Top()
{
    if (IsEmpty())
    {
        return Place(-1, -1);
    }
    return stack[_top];
}

bool Stack::IsEmpty()
{
    if (_top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Stack::~Stack()
{
    //dtor
}
