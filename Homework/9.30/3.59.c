#include <stdio.h>

typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y) {
    *dest = x * (int128_t) y;
}

/* store_prod:            # *dest->rdi, x->rsi, y->rdx
 *   movq   %rdx, %rax    # 把y的值移到%rax，同时也在防止扩展后128位把y覆盖掉
 *   cqto                 # 把rdx按照rax的高位进行填充，rdx:rax分别作为高64和低64位来决定最终的输出
 *   movq   %rsi, %rcx    # 把x的值放到%rcx里面
 *   sarq   $63, %rcx     # rcx = x>>63
 *   imulq  %rax, %rcx    # rcx = y * sx
 *   imulq  %rsi, %rdx    # rdx = sy * x
 *   addq   %rdx, %rcx    # rcx = x*sy+y*sx
 *   mulq   %rsi          # rdx:rax = y * x
 *   addq   %rcx, %rdx    # rdx += rcx
 *   movq   %rax, (%rdi)  # 把result的值交给dest对应的地址
 *   movq   %rdx, 8(%rdi) # 把
 *   ret
 * */

/* 汇编看晕了，书上提示看懂了，x = 2^64*sx + x, y = 2^64*sy + y
 * p = x * y = 2^128*sx*sy + 2^64*(sx*y+sy*x) + (x*y)
 * 这个2^128的系数似乎没什么所谓，只有sx和sy都是负数的时候算出来才会有值，是2^128，但刚好了，按照int相似的环的性质，
 * 虽然这时候算出来的值是负数，但是对2^128取模结果是对的，所以，在这个里面，我们完全可以认为p = 2^64*(sx*y + sy*x) + (x*y)。
 * 因此，计算的时候只需要算出来sx*y+sy*x向左移位64位，然后+x*y就ok了
 * 
 * 另：因为结果是128位，所以rax存不下，高64位会由rdx存储
 */
