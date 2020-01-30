//lang::CwC

#pragma once
#include <stdlib.h>
#include "node.h"

/*
 * Queue - Stores objects and returns them in FIFO order
*/
class Queue : public Object {
    public:
        Node* sentinel;
        size_t length;

        Queue() : Object() {
            this->sentinel = new Node();
            this->length = 0;
        }

        virtual ~Queue() {}

        /*
         * Adds object to end of queue
         * Exit if o is null
         * @param o Object to be added to queue
        */
        virtual void add(Object* o) {
            if (this->sentinel->prev == nullptr) {
                this->sentinel->prev = new Node(o);
            } else {
                Node* old_tail = this->sentinel->prev;
                Node* new_tail = new Node(o);
                this->sentinel->prev = new_tail;
                new_tail->next = this->sentinel;
                new_tail->prev = old_tail;
                old_tail->next = new_tail;
            }
            this->length++;
        }

        /*
         * Removes the object at the head of the queue
        */
        virtual void remove() {
            if (this->sentinel->next != nullptr) {
                Node* old_head = this->sentinel->next;
                Node* new_head = this->sentinel->next->next;
                this->sentinel->next = new_head;
                if (new_head != nullptr) {
                    new_head->prev = this->sentinel;
                }
                this->length--;
            }
        }

        /*
         * Returns pointer to object at the head of the queue
         * Exits if queue is empty
        */
        virtual Object* head() {
            return this->sentinel->next;
        }

        /*
         * Returns size of queue
        */
        virtual size_t size() {
            return this->length;
        }

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
