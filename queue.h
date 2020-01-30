//lang::CwC

#pragma once
#include <stdlib.h>
#include "node.h"
#include <stddef.h>

/*
 * Queue - Stores objects and returns them in FIFO order
*/
class Queue : public Object {
    public:
        Node* sentinel;
        size_t length;

        Queue() : Object() {
            this->sentinel = new Node();
            this->sentinel->is_sentinel = true;
            this->length = 0;
        }

        virtual ~Queue() {}

        /*
         * Adds object to end of queue
         * Exit if o is null
         * @param o Object to be added to queue
        */
        virtual void add(Object* o) {
            Node* new_tail = new Node(o);
            if (this->sentinel->prev == nullptr) {
                this->sentinel->prev = new_tail;
                new_tail->next = this->sentinel;
                this->sentinel->next = new_tail;
                new_tail->prev = this->sentinel;

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
            if (this->length > 0) {
                return this->sentinel->next->data;
            }
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
        bool equals(Object *otherQ) {
            Queue* other_queue = dynamic_cast<Queue*>(otherQ);
            if (other_queue == nullptr) {
                return false;
            } else {
                if (this->length != other_queue->length) {
                    return false;
                } else {
                    Node* this_node = this->sentinel->next;
                    Node* other_node = other_queue->sentinel->next;

                    while (this_node != nullptr 
                        && other_node != nullptr
                        && !(this_node->is_sentinel && other_node->is_sentinel)) {
                        if (!this_node->equals(other_node)
                            || (this_node->is_sentinel && !other_node->is_sentinel)
                            || (!this_node->is_sentinel && other_node->is_sentinel)) {
                            return false;
                        }
                        this_node = this_node->next;
                        other_node = other_node->next;
                    }
                    return true;
                }
            }
        }

        /**
		 * Returns the hash code for this Queue
         * Overrides hashCode() from Object 
        */
        size_t hashCode() {}
};
