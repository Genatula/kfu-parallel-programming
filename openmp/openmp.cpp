#include "openmp.h"

#include <iostream>
#include <omp.h>

using namespace std;

/*
 * Write a program where each thread prints its id, a total amount of threads and a "Hello World" string
 * Total number of threads : 8
 * */

void executeFirstOpenMpTask()
{
#pragma omp parallel num_threads(8)
    {
        int amount = omp_get_num_threads();
        int id = omp_get_thread_num();
        printf("Thread id = %d \n", id);
        printf("Hello world from thread %d \n", id);
        printf("Total amount of threads = %d \n", amount);
    }
}

/*
 * Write a program with 2 parallel regions which execution depends on `#pragma omp parallel if(...)`
 * The condition is as follows : if the set number of threads is greater than 1, than the area is executed
 * Set the number of threads before the 1st area to 3, before the 2nd one - to 1
 * Inside the regions find out and print the number of threads and their identifiers
 */

void executeSecondOpenMpTask()
{
    omp_set_num_threads(3);
    printf("Executing the task with 3 threads: \n");
    if (omp_get_max_threads() == 1) {
        return;
    }
#pragma omp parallel if(omp_get_max_threads() > 1)
    {
        printf("Total amount of threads = %d \n", omp_get_max_threads());
        printf("Thread id = %d \n", omp_get_thread_num());
    }
    omp_set_num_threads(1);
    printf("Executing the task with 1 thread: \n");
    if (omp_get_max_threads() == 1) {
        return;
    }
#pragma omp parallel if(omp_get_max_threads() > 1)
    {
        printf("Total amount of threads = %d \n", omp_get_max_threads());
        printf("Thread id = %d", omp_get_thread_num());
    }
}

void executeThirdOpenMpTask() {
    int a = 1, b = 1;
    printf("a = %d, b = %d \n", a, b);
#pragma omp parallel private(a) firstprivate(b) num_threads(2)
    {
        a += omp_get_thread_num();
        b += omp_get_thread_num();
        printf("a = %d, b = %d from thread %d \n", a, b, omp_get_thread_num());
    }
    printf("a = %d, b = %d \n\n", a, b);
#pragma omp parallel shared(a) private(b) num_threads(4)
    {
        a -= omp_get_thread_num();
        b -= omp_get_thread_num();
        printf("a = %d, b = %d from thread %d \n", a, b, omp_get_thread_num());
    }
    printf("a = %d, b = %d", a, b);
}
