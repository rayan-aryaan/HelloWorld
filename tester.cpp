#include <stdio.h>

int main() {
    char alphabets [95] = {'\0'};
    for(int i = 0; i < 95; i++){
        alphabets[i] = ' ' + i;
    }
    for(int i = 0; i < 95; i++){
        printf("%c\n", alphabets[i]);
    }
}