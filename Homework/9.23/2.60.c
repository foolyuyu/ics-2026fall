#include <stdio.h>
unsigned replace_byte (unsigned x, int i, unsigned char b) {
    unsigned shift = (unsigned)i << 3;
    unsigned mask = ~(0xFFu << shift);
    unsigned result = ((unsigned)b << shift) | (x & mask);
    return result;
}

int main() {
    unsigned x;
    int i;
    unsigned char b;
    scanf("%x %d %hhx", &x, &i, &b);
    unsigned result = replace_byte(x, i, b);
    printf("0x%08X\n", result);

    return 0;
}