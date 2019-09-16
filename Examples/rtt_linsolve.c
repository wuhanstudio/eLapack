#include <rtthread.h>
#include <stdio.h>
#include <time.h>
#include <LinearAlgebra/declareFunctions.h>

/* Matlab Code */
// A = [3,  4, 1; 
//      6, 10, 2; 
//      5,  3, 2]

// B = [4, 3, 22, 5; 
//      5, 3,  2, 5; 
//      3, 4,  5, 3]

// X = linsolve(A, B)

static void elapack_linsolve_thread_entry(void *parameter)
{
    // Start
    clock_t start, end;
    float cpu_time_used;
    start = clock();

     // Math
    double A[3*3] = {3,  4, 1,
                     6, 10, 2,
                     5,  3, 2};

    double X[3*4];

    double B[3*4] = {4, 3, 22, 5,
                     5, 3,  2, 5,
                     3, 4,  5, 3};

    linsolve(A, X, B, 3, 4); // 3 = A row, 4 = B column
    printf("\n\nA = \n\n");
    print(A, 3, 3);
    printf("B = \n\n");
    print(B, 3, 4);
    printf("X = \n\n");
    print(X, 3, 4);

    // End
    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("[elapack] Total speed was %f ms\n", cpu_time_used * 1000);

    // Uncomment this if you'd like to check memory usage with list_thread
    while(1)
    {
        rt_thread_mdelay(500);
    }
}

static void elapack_linsolve(int argc,char *argv[])
{
    rt_thread_t thread = rt_thread_create("e_lin", elapack_linsolve_thread_entry, RT_NULL, 2048, 25, 10);
    if(thread != RT_NULL)
    {
        rt_thread_startup(thread);
        rt_kprintf("[elapack] New thread linsolve\n");
    }
    else
    {
        rt_kprintf("[elapack] Failed to create thread linsolve\n");
    }
}
MSH_CMD_EXPORT(elapack_linsolve, elapack linsolve example);
