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

#define min(a,b) (((a) < (b)) ? (a) : (b))

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_32_32(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]);
void transpose_61_67(int M, int N, int A[N][M], int B[M][N]);
/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
// char transpose_submit_desc[] = "Transpose submission";
// void transpose_submit(int M, int N, int A[N][M], int B[M][N])
// {

// }

/*
    • 32 × 32: 8 points if m < 300, 0 points if m > 600
    • 64 × 64: 8 points if m < 1, 300, 0 points if m > 2, 000
    • 61 × 67: 10 points if m < 2, 000, 0 points if m > 3, 000
*/

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    // int a0,a1,a2,a3,a4,a5,a6,a7;
    // int i,j;
    // int offset = 8;
    // for(i=0;i<N;i=min(i+offset,N)){
    //     for(j=0;j<M;j=min(j+offset,M)){
    //         for(int k=i;k<min(i+offset,N);k++){
    //             a0 = A[k][j];
    //             a1 = A[k][j+1];
    //             a2 = A[k][j+2];
    //             a3 = A[k][j+3];
    //             a4 = A[k][j+4];
    //             a5 = A[k][j+5];
    //             a6 = A[k][j+6];
    //             a7 = A[k][j+7];
    //             B[j][k] = a0;
    //             B[j+1][k] = a1;
    //             B[j+2][k] = a2;
    //             B[j+3][k] = a3;
    //             B[j+4][k] = a4;
    //             B[j+5][k] = a5;
    //             B[j+6][k] = a6;
    //             B[j+7][k] = a7;
    //         }
    //     }
    // }
    if(M == 32 && N == 32)
        transpose_32_32(M, N, A, B);    
    else if(M == 64 && N == 64)
        transpose_64_64(M, N, A, B);
	else if(M == 61 && N == 67)
		transpose_61_67(M, N, A, B);
}


// char transpose_32_32_desc[] = "Transpose submission";
void transpose_32_32(int M, int N, int A[N][M], int B[M][N])
{
    int a0,a1,a2,a3,a4,a5,a6,a7;
    int i,j;
    int offset = 8;
    for(i=0;i<N;i=min(i+offset,N)){
        for(j=0;j<M;j=min(j+offset,M)){
            for(int k=i;k<min(i+offset,N);k++){
                // helped by registers
                a0 = A[k][j];
                a1 = A[k][j+1];
                a2 = A[k][j+2];
                a3 = A[k][j+3];
                a4 = A[k][j+4];
                a5 = A[k][j+5];
                a6 = A[k][j+6];
                a7 = A[k][j+7];
                B[j][k] = a0;
                B[j+1][k] = a1;
                B[j+2][k] = a2;
                B[j+3][k] = a3;
                B[j+4][k] = a4;
                B[j+5][k] = a5;
                B[j+6][k] = a6;
                B[j+7][k] = a7;
            }
        }
    }
}

// char transpose_61_67_desc[] = "Transpose submission";
void transpose_61_67(int M, int N, int A[N][M], int B[M][N])
{
    int i,j,m,n;
    int offset = 16;
    for(i=0;i<N;i=min(i+offset,N)){
        for(j=0;j<M;j=min(j+offset,M)){                  
            for(m = i;m<min(i+offset,N);++m){
                for(n = j;n<min(j+offset,M);++n){
                    B[n][m] = A[m][n];
                }
            }
        }
    }
}



// char transpose_64_64_desc[] = "Transpose submission";
void transpose_64_64(int M, int N, int A[N][M], int B[M][N])
{
    int i,j,m,k;
    int a0,a1,a2,a3,a4,a5,a6,a7,tmp;
    int offset = 8;
    for(i=0;i<N;i=min(i+offset,N)){
        for(j=0;j<M;j=min(j+offset,M)){                  
            for(m=0;m<offset/2;m++){
                a0 = A[i+m][j];
                a1 = A[i+m][j+1];
                a2 = A[i+m][j+2];
                a3 = A[i+m][j+3];
                a4 = A[i+m][j+4];
                a5 = A[i+m][j+5];
                a6 = A[i+m][j+6];
                a7 = A[i+m][j+7];

                B[j+0][i+m] = a0;
                B[j+1][i+m] = a1;
                B[j+2][i+m] = a2;
                B[j+3][i+m] = a3;

                B[j+0][i+m+offset/2] = a4;
                B[j+1][i+m+offset/2] = a5;
                B[j+2][i+m+offset/2] = a6;
                B[j+3][i+m+offset/2] = a7;
            }
            for(k=0;k<offset/2;k++){
                // step 1 2
                a0 = A[i + 4][j + k], a4 = A[i + 4][j + k + 4];
                a1 = A[i + 5][j + k], a5 = A[i + 5][j + k + 4];
                a2 = A[i + 6][j + k], a6 = A[i + 6][j + k + 4];
                a3 = A[i + 7][j + k], a7 = A[i + 7][j + k + 4];
                // step 3
                tmp = B[j + k][i + 4], B[j + k][i + 4] = a0, a0 = tmp;
                tmp = B[j + k][i + 5], B[j + k][i + 5] = a1, a1 = tmp;
                tmp = B[j + k][i + 6], B[j + k][i + 6] = a2, a2 = tmp;
                tmp = B[j + k][i + 7], B[j + k][i + 7] = a3, a3 = tmp;
                // step 4
                B[j + k + 4][i + 0] = a0, B[j + k + 4][i + 4 + 0] = a4;
                B[j + k + 4][i + 1] = a1, B[j + k + 4][i + 4 + 1] = a5;
                B[j + k + 4][i + 2] = a2, B[j + k + 4][i + 4 + 2] = a6;
                B[j + k + 4][i + 3] = a3, B[j + k + 4][i + 4 + 3] = a7;
            }
        }
    }
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

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

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
    // registerTransFunction(transpose_61_67, transpose_61_67_desc); 
    // registerTransFunction(transpose_32_32, transpose_32_32_desc); 
    // /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc); 
    // // registerTransFunction(transpose_32, transpose_32_desc); 
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

