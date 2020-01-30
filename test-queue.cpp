//lang::Cpp

#include <stdlib.h>
#include "object.h"
#include "queue.h"
#include "string.h"
#include <stdio.h>

// Using test functions from warmup 3
void FAIL() {
    printf("tests failed (expected since nothing is implemented)");
    exit(1);
}
void OK(const char* m) { printf(m); }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }


int main(int argc, char** argv) {
    Object* a = new Object();
    String* str1 = new String("a");
    String* str2 = new String("b");
    String* str3 = new String("a");
    String* str4 = new String("ab");
    
    
    // t_true(str1->equals(str3)); //str1 and str3 are equal
    // t_false(str1->equals(a)); //str1 and a are not equal
    // t_false(str1->equals(str2)); //str1 and str2 are not equal
    
    // t_true(str1->hashCode() == str3->hashCode()); //str1 & str3 hashes equal
    // t_false(str2->hashCode() == str3->hashCode()); //str2 & str3 hashes not equal
    
    // t_true(str1->compare(str2) < 0); //str1 has a lower first diff char than str2
    // t_true(str2->compare(str1) > 0); //str2 has a higher first diff char than str1
    // t_true(str1->compare(str3) == 0); //str1 and str3 are equal
    
    // t_true(str1->size() == 1); //str1 is size 1, not counting null terminator
    
    // t_true(str1->concat(str2)->equals(str4)); //str2 added to str1 equals str4
    
    // t_true(strcmp(str4->strCopy(),str4->str));
    
    Queue* queue1 = new Queue();
    t_true(queue1->size() == 0); //nothing in queue1

    queue1->add(a); //add a to queue1
    t_true(queue1->size() == 1); //1 item (a)

    queue1->add(str1); //add str1 to queue1
    t_true(queue1->size() == 2); //2 items (a, str1)
    t_true(queue1->head()->equals(a)); //a is head of queue1
    queue1->remove(); //removes the head from queue1 (a)
    t_true(queue1->size() == 1); //1 item (str1)
    t_false(queue1->head()->equals(a)); //a is no longer the head
    t_true(queue1->head()->equals(str1)); //str1 is head of queue1

    Queue* queue2 = new Queue(); 
    queue2->add(str2); //add str2 to queue2
    
    t_true(queue2->size() == 1); //1 item (str2)
    t_true(queue1->size() == queue2->size()); //sizes of both queues are equal
    
    t_false(queue1->equals(queue2)); //queues are not equal despite equal size
    //t_false(queue1->hashCode() == queue2->hashCode()); //no equal hash codes

    queue2->remove(); //removes the head from queue2 (str2)
    queue2->add(str1); //adds str1 to queue2
    t_true(queue1->equals(queue2)); //queues are now equal
    //t_true(queue1->hashCode() == queue2->hashCode()); //equal hash codes
    
    delete a;
    delete str1;
    delete str2;
    delete str3;
    delete str4;
    delete queue1;
    delete queue2;
    
    OK("All tests passed!");
}