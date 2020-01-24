#pragma once
#include <stdlib.h>

/*
 * Object - Base class for all other classes
*/
class Object {
    public:
        size_t hash; // stores hashCode from last call to hashCode()
    
    virtual Object() {}

    virtual ~Object() {}

    /*
     * Is this object equal to the other object?
     * True if other points to this object
     * @param other Object to compare against
    */
    virtual bool equals(Object* other) {}

    /*
     * Returns a hashcode for this object
     * hashCode will be this Object's address
    */
    virtual size_t hashCode() {}
}