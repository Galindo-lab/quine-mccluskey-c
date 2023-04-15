
#include <stdlib.h>
#include <stdio.h>

char getBitState(int value, char position) {
    return value & (1<<position);
}

void printBinary(int value)
{
    unsigned char lenght = sizeof(int) * 8 - 1;

    for (char i = lenght; i >= 0; i--)
        printf(getBitState(value, i) ? "1" : "-");
}

int main()
{
    int a = 0b00000010000101;
    printBinary(a);

    return EXIT_SUCCESS;
}
