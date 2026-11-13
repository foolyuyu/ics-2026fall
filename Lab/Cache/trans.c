/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"
#include "contracts.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. The REQUIRES and ENSURES from 15-122 are included
 *     for your convenience. They can be removed if you like.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    REQUIRES(M > 0);
    REQUIRES(N > 0);

    int i, j, p, q;
    int t0, t1, t2, t3, t4, t5, t6, t7;

    if (M == 32 && N == 32) {
        /* Read each row of an 8x8 block before writing it to B. */
        for (p = 0; p < 4; ++p) {
            for (q = 0; q < 4; ++q) {
                for (i = p * 8; i < (p + 1) * 8; ++i) {
                    t0 = A[i][q * 8 + 0];
                    t1 = A[i][q * 8 + 1];
                    t2 = A[i][q * 8 + 2];
                    t3 = A[i][q * 8 + 3];
                    t4 = A[i][q * 8 + 4];
                    t5 = A[i][q * 8 + 5];
                    t6 = A[i][q * 8 + 6];
                    t7 = A[i][q * 8 + 7];
                    B[q * 8 + 0][i] = t0;
                    B[q * 8 + 1][i] = t1;
                    B[q * 8 + 2][i] = t2;
                    B[q * 8 + 3][i] = t3;
                    B[q * 8 + 4][i] = t4;
                    B[q * 8 + 5][i] = t5;
                    B[q * 8 + 6][i] = t6;
                    B[q * 8 + 7][i] = t7;
                }
            }
        }
    } else if (M == 64 && N == 64) {
        for (q = 0; q < 8; ++q) {
            for (p = 0; p < 8; p += 2) {
                /* Stage the two adjacent 8x8 blocks as one 8x16 region. */
                for (i = 0; i < 16; ++i) {
                    t0 = A[p * 8 + i][q * 8 + 0];
                    t1 = A[p * 8 + i][q * 8 + 1];
                    t2 = A[p * 8 + i][q * 8 + 2];
                    t3 = A[p * 8 + i][q * 8 + 3];
                    t4 = A[p * 8 + i][q * 8 + 4];
                    t5 = A[p * 8 + i][q * 8 + 5];
                    t6 = A[p * 8 + i][q * 8 + 6];
                    t7 = A[p * 8 + i][q * 8 + 7];
                    B[q * 8 + 0][p * 8 + i] = t0;
                    B[q * 8 + 4][p * 8 + (i + 8) % 16] = t4;
                    B[q * 8 + 1][p * 8 + i] = t1;
                    B[q * 8 + 5][p * 8 + (i + 8) % 16] = t5;
                    B[q * 8 + 2][p * 8 + i] = t2;
                    B[q * 8 + 6][p * 8 + (i + 8) % 16] = t6;
                    B[q * 8 + 3][p * 8 + i] = t3;
                    B[q * 8 + 7][p * 8 + (i + 8) % 16] = t7;
                }

                /* Restore the lower four rows by swapping the two blocks. */
                for (i = 4; i < 8; ++i) {
                    for (j = 0; j < 8; ++j) {
                        t0 = B[q * 8 + i][p * 8 + j];
                        B[q * 8 + i][p * 8 + j] =
                            B[q * 8 + i][p * 8 + j + 8];
                        B[q * 8 + i][p * 8 + j + 8] = t0;
                    }
                }
            }
        }
    } else if (M == 60 && N == 68) {
        /* Use 16x8 blocks and handle the four remaining columns. */
        for (p = 0; p < N; p += 16) {
            for (q = 0; q < M; q += 8) {
                for (i = p; i < p + 16 && i < N; ++i) {
                    t0 = A[i][q];
                    t1 = A[i][q + 1];
                    t2 = A[i][q + 2];
                    t3 = A[i][q + 3];
                    if (q + 7 < M) {
                        t4 = A[i][q + 4];
                        t5 = A[i][q + 5];
                        t6 = A[i][q + 6];
                        t7 = A[i][q + 7];
                    }
                    B[q][i] = t0;
                    B[q + 1][i] = t1;
                    B[q + 2][i] = t2;
                    B[q + 3][i] = t3;
                    if (q + 7 < M) {
                        B[q + 4][i] = t4;
                        B[q + 5][i] = t5;
                        B[q + 6][i] = t6;
                        B[q + 7][i] = t7;
                    }
                }
            }
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

 /*
  * trans - A simple baseline transpose function, not optimized for the cache.
  */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

