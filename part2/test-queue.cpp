#pragma once
#include <stdlib.h>
#include "object.h"
#include "queue.h"
#include "string.h"

// Using test functions from warmup 3
void FAIL() {   exit(1);    }
void OK(const char* m) { /** print m */ }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }


int main(int argc, char** argv) {
    Object* a = new Object();
    String* str1 = new String("a");
    String* str2 = new String("b");
    
    Queue* queue1 = new Queue();
    t_true(queue1->size() == 0);

    queue1.add(a);
    t_true(queue1->size() == 1);

    queue1.add(str1);
    t_true(queue1->remove()->equals(a))
    t_true(queue1->head()->equals(str1));

    Queue* queue2 = new Queue();
    queue2.add(str2);
    t_false(queue1->equals(queue2));

    queue2.remove();
    queue2.add(str1);
    t_true(queue1->equals(queue2));
    // t_true(queue1->hash(queue2));
}