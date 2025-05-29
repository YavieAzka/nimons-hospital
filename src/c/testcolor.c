#include <stdio.h>

int main() {
    printf("\033[31mMerah\033[0m\n");
    printf("\033[32mHijau\033[0m\n");
    printf("\033[33mKuning\033[0m\n");
    printf("\033[34mBiru\033[0m\n");
    printf("\033[1;35mTebal Magenta\033[0m\n");
    printf("\033[1;33;44mKuning di atas biru\033[0m\n");
    return 0;
}