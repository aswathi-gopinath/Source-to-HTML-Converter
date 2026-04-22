#include <stdio.h>
#include "myheader.h"

int main() {
    int a = 10;
    float b = 20.5;

    // single line comment

    /*
       multi line
       comment
    */

    char ch = 'A';
    char *str = "Hello World";

    if(a < b) {
        printf("Value: %d\n", a);
    }

    return 0;
}
