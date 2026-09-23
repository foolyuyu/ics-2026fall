#include <stdio.h>

int main(void) {
    unsigned x, y;
    scanf("%x %x", &x, &y);
    unsigned result = (x & 0xFFu) | (y & ~0xFFu); // 这里使用~0xFFu避免只适用于32位
    printf("0x%08X\n", result);

    return 0;
}
