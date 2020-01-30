#pragma once
#include <stdlib.h>
#include "object.h"

// Node for a Deque
class Node : public Object {
    public:
        Node* prev;
        Object* data;
        Node* next;

        Node() {
            this->prev = nullptr;
            this->data = nullptr;
            this->next = nullptr;
        }

        Node(Object* data) {
            this->prev = nullptr;
            this->data = data;
            this->next = nullptr;
        }
};