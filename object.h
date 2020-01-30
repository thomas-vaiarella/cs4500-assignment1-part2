//lang::CwC

#pragma once
#include <stdlib.h>

/*
 * Object - Base class for all other classes
*/
class Object {
    public:
        Object() {}

        virtual ~Object() {}

        /*
         * Is this object equal to the other object?
         * True if other points to this object
         * @param other Object to compare against
        */
        virtual bool equals(Object* other) {
            return reinterpret_cast<int>(this) == reinterpret_cast<int>(other);
        }

        /*
         * Returns a hashcode for this object
         * hashCode will be this Object's address
        */
        virtual size_t hashCode() {}
};
