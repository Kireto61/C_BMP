//
// Created by kikig on 27.4.2023 г..
//
//
// Created by Kiril Valkov on 26.04.23.
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned char c = 203;
//    for (int i = 7; i > 0; i--) {
//        printf("%d ", c >> (i * 2) & 1);
//    }

    for (int k = 7; k >= 0; k -= 2) {
        unsigned char d=0;
        d+=(c >> k) & 1;
        d=d<<1;
        d+=(c >> (k - 1)) & 1;
        printf("%d ", d);
    }

    return 0;
}
