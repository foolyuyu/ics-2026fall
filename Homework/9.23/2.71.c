#include <stdio.h>

typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum);

/* 错误的代码
 * int xbyte(packed_t)
 * {
 *    return (word >> (bytenum << 3)) & 0xFF;
 * }
 * 
 * 错误在：每一个字节都是有符号字节，如果取到的字节最高位为1，是负数，但是这种扩展方式只能扩出来正数
 */
int xbyte(packed_t word, int bytenum) {
    unsigned shift = (unsigned)bytenum << 3;
    int result = (int)((word >> shift) << 24) >> 24; //int类型左移把符号消掉是未定义行为，最好先用unsigned左移然后再转int赋予符号含义
    return result;
}

int main() {
    packed_t word;
    int bytenum;
    scanf("%x %d", &word, &bytenum);
    printf("%d\n", xbyte(word, bytenum));

    return 0;
}