#include <stdint.h>

typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y) {
    *dest = x * (int128_t) y;
}

/* store_prod:             # dest -> %rdi, x -> %rsi, y -> %rdx
 *   movq   %rdx, %rax     # %rax = uy
 *   cqto                  # %rdx = sy（0 或 -1）
 *   movq   %rsi, %rcx
 *   sarq   $63, %rcx      # %rcx = sx（0 或 -1）
 *   imulq  %rax, %rcx     # %rcx = sx * uy 的低 64 位
 *   imulq  %rsi, %rdx     # %rdx = sy * ux 的低 64 位
 *   addq   %rdx, %rcx     # %rcx = sx*uy + sy*ux
 *   mulq   %rsi           # %rdx:%rax = ux * uy
 *   addq   %rcx, %rdx     # 修正乘积的高 64 位
 *   movq   %rax, (%rdi)   # 保存低 64 位
 *   movq   %rdx, 8(%rdi)  # 保存高 64 位
 *   ret
 */

/* 令 M = 2^64，ux、uy 是 x、y 的位模式按无符号数解释后的值，
 * sx、sy 是相应的符号扩展值（0 或 -1），则
 *
 * x = ux + M*sx, y = uy + M*sy
 * x*y = ux*uy + M*(sx*uy + sy*ux) + M^2*sx*sy
 *
 * 结果只保留 128 位，所以 M^2*sx*sy 在模 2^128 下消失。
 * mulq 先计算 ux*uy，再把另外两项作为高 64 位修正量加到 %rdx。
 */
