#pragma once
#include <stdlib.h>
#include "object.h"
#include <stddef.h>

// Node for a Deque
class Node : public Object {
    public:
        Node* prev;
        Object* data;
        Node* next;
        bool is_sentinel;

        Node() {
            this->prev = nullptr;
            this->data = nullptr;
            this->next = nullptr;
            this->is_sentinel = false;
        }

        Node(Object* data) {
            this->prev = nullptr;
            this->data = data;
            this->next = nullptr;
            this->is_sentinel = false;
        }

        bool equals(Object* other) {
            Node* other_node = dynamic_cast<Node*>(other);
            if (other_node == nullptr) {
                return false;
            } else {
                return (this->data == other_node->data) 
                || (this->data != nullptr && (this->data->equals(other_node->data)));
            }
        }

        size_t hashCode() {
            size_t x = 0;
            if (this->is_sentinel) {
                x++;
            }
            if (this->data != nullptr) {
                x += this->data->hash();
            }
            return x;
        }
};