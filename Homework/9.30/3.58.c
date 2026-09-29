#include <stdio.h>

/* decode2:             # x -> %rdi, y -> %rsi, z -> %rdx
 *   subq   %rdx, %rsi  # y -= z
 *   imulq  %rsi, %rdi  # x *= y
 *   movq   %rsi, %rax  # result = y
 *   salq   $63, %rax   # 将 y 的最低位移到符号位
 *   sarq   $63, %rax   # 将符号位扩展为全 0 或全 1
 *   xorq   %rdi, %rax  # result ^= x
 *   ret
 */

long decode2(long x, long y, long z) {
    long t = y - z;
    long mask = -(t & 1L);
    return (x * t) ^ mask;
}

int main(void) {
    long x, y, z;
    scanf("%ld %ld %ld", &x, &y, &z);
    printf("%ld\n", decode2(x, y, z));

    return 0;
}
