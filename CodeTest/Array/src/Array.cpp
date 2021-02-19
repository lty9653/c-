#include "Array.h"

Array::Array()
{
    //ctor
}

Array::~Array()
{
    //dtor
}

Array::Array(const Array& other)
{
    //copy ctor
}

Array& Array::operator=(const Array& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
