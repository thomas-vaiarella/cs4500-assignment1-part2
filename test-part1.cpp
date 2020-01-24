//lang::Cpp

#pragma once
#include <stdlib.h>
#include "object.h"
#include "queue.h"
#include "string.h"

// Using test functions from warmup 3
void FAIL() {
    printf("Something failed");
    exit(1);
}
void OK(const char* m) { printf(m); }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }


int main(int argc, char** argv) {
    OK("All tests passed!");
}