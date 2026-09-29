#include <stdio.h>

long decode2(long x, long y, long z);

/* decode2:            # x->rdi, y->rsi, z->rdx
 *   subq   %rdx, %rsi # y += z
 *   imulq  %rsi, %rdi # x *= y
 *   movq   %rsi, %rax # y放到rax
 *   salq   $63, %rax  # rax算数左移63
 *   sarq   $63, %rax  # rax算数右移63
 *   xorq   %rdi, %rax # rax和x做异或运算
 *   ret
 */

long decode2(long x, long y, long z) {
    y -= z;
    x *= y;
    long result = ((y << 63) >> 63) ^ x;
    return result;
}   

int main(void) {
    long x, y, z;
    scanf("%ld %ld %ld", &x, &y, &z);
    printf("%ld", decode2(x, y, z));
}


