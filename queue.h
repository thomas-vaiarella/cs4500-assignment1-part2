//lang::CwC

#pragma once
#include <stdlib.h>

/*
 * Queue - Stores objects and returns them in FIFO order
*/
class Queue : public Object {
    public:

        Queue() : Object() {}

        virtual ~Queue() {}

        /*
         * Adds object to end of queue
         * Exit if o is null
         * @param o Object to be added to queue
        */
        virtual void add(Object* o) {}

        /*
         * Removes the object at the head of the queue
        */
        virtual void remove() {}

        /*
         * Returns pointer to object at the head of the queue
         * Exits if queue is empty
        */
        virtual Object* head() {}

        /*
         * Returns size of queue
        */
        virtual size_t size() {}

        /**
		 * Is this Queue equal to the given Object?
         * Equality based on calling equals() on each queue element
         * Overrides equals() from Object
		 * @param otherQ Object pointer
		*/
        bool equals(Object *otherQ) {}

        /**
		 * Returns the hash code for this Queue
         * Overrides hashCode() from Object 
        */
        size_t hashCode() {}
};
