#include "openmp.h"

#include <iostream>
#include <omp.h>
#include <iterator>
#include <limits>
#include <random>

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

/*
 * Initialize two integers a and b. Define two parallel regions with 2 and 4 threads respectively.
 * For the first region declare a and b protected as private and firstprivate respectively. In the region
 * find out the thread number and add it to a and b. Print values of a and b before the region, in the region
 * and after the region. For the second region declare a shared and b protected as private. Find out
 * the thread number and subtract it from a and b. Print the same information.
 * */

void executeThirdOpenMpTask()
{
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

/*
 * Initialize two integer arrays a[10] and b[10]. Define a parallel region with 2 threads.
 * Make master thread compute min(a), thread with id = 1 - max(b).
 * Print the results.
 * */

void executeFourthOpenMpTask()
{
    int a[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[]{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
#pragma omp parallel shared(a, b) num_threads(2)
    {
#pragma omp master
        {
            int min = numeric_limits<int>::max();
            for (int i : a) {
                if (i < min) {
                    min = i;
                }
            }
            printf("The minimum value of the array a is %d \n", min);
            printf("This section has been executed by thread %d \n\n", omp_get_thread_num());
        }
#pragma omp single nowait
        {
            int max = numeric_limits<int>::min();
            for (int i : b) {
                if (i > max) {
                    max = i;
                }
            }
            printf("The maximum value of the array b is %d \n", max);
            printf("This section has been executed by thread %d \n\n", omp_get_thread_num());
        }
    }
}

/*
 * Initialize two-dimensional integer array d[6][8] with random values.
 * Using sections construct, define 3 sections: the first to compute the mean, the second to compute
 * the min and max values, the third to find out how many numbers give remainder = 0 when divided by 3.
 * In each section print the executing thread's id and the result.
 * */

void executeFifthOpenMpTask()
{
    int d[6][8]{};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = rand();
        }
    }
#pragma omp parallel shared(d)
    {
#pragma omp sections
        {
#pragma omp section
            {
                double mean = 0;
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 8; j++) {
                        mean += d[i][j];
                    }
                }
                mean = mean / 48;
                printf("The mean equals to %f \n", mean);
                printf("This section has been executed by thread %d \n\n", omp_get_thread_num());
            }
#pragma omp section
            {
                int min = numeric_limits<int>::max();
                int max = numeric_limits<int>::min();
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 8; j++) {
                        if (d[i][j] > max) {
                            max = d[i][j];
                        }
                        if (d[i][j] < min) {
                            min = d[i][j];
                        }
                    }
                }
                printf("The min = %d, the max = %d \n", min, max);
                printf("This section has been executed by thread %d \n\n", omp_get_thread_num());
            }
#pragma omp section
            {
                int num = 0;
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 8; j++) {
                        if (d[i][j] % 3 == 0) {
                            num += 1;
                        }
                    }
                }
                printf("There are %d numbers which give remainder of 0 when divided by 3 \n", num);
                printf("This section has been executed by thread %d \n\n", omp_get_thread_num());
            }
        }
    }
}

void executeSixthOpenMpTask()
{
    int a[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[]{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int i, sum_a = 0, sum_b = 0;
#pragma omp parallel for private(i) reduction(+:sum_a, sum_b)
        for (i = 0; i < 10; i++)
        {
            sum_a += a[i];
            sum_b += b[i];
        }
    printf("The means are as follows: \n Mean of a = %f, mean of b = %f",
           static_cast<float>(sum_a / 10),
           static_cast<float>(sum_b / 10));
}

void executeSeventhOpenMpTask()
{
    int a[12], b[12], c[12], i;
    omp_set_num_threads(3);
    int chunk = 4;
#pragma omp parallel for private(i) schedule(static, chunk)
    for (i = 0; i < 12; i++)
    {
        a[i] = i * 2;
        b[i] = i * 3;
        printf("Total amount of threads = %d, current thread id = %d \n", omp_get_num_threads(), omp_get_thread_num());
    }
    for (i = 0; i < 12; i++)
    {
        printf("a[%d] = %d, b[%d] = %d \n", i, a[i], i, b[i]);
    }

    omp_set_num_threads(4);
    chunk = 3;
#pragma omp parallel for private(i) schedule(dynamic, chunk)
    for (i = 0; i < 12; i++)
    {
        c[i] = a[i] + b[i];
        printf("Total amount of threads = %d, current thread id = %d \n", omp_get_num_threads(), omp_get_thread_num());
    }
    for (i = 0; i < 12; i++)
    {
        printf("c[%d] = %d \n", i, c[i]);
    }
}

void executeNinthOpenMpTask() {
    int d[6][8];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = rand();
        }
    }
    int min = numeric_limits<int>::max(), max = numeric_limits<int>::min();
#pragma omp parallel num_threads(8)
    {
#pragma omp parallel for
        for (int i = 0; i < 6; i++) {
#pragma omp parallel for
            for (int j = 0; j < 8; j++) {
#pragma omp critical
                {
                    if (d[i][j] < min) {
                        min = d[i][j];
                    }
                    if (d[i][j] > max) {
                        max = d[i][j];
                    }
                }
            }
        }
    }
    printf("The minimum of the array = %d, the maximum of the array = %d \n", min, max);
}

void executeTenthOpenMpTask() {
    int a[30];
    for (int i = 0; i < 30; i++) {
        a[i] = rand();
    }
    int num = 0;
#pragma omp parallel num_threads(8)
    {
#pragma omp for
        for (int i = 0; i < 30; i++) {
            if (a[i] % 9 == 0) {
#pragma omp atomic
                num += 1;
            }
        }
    }
    printf("Amount of multiples of 9 = %d", num);
}

void executeEleventhOpenMpTask() {
    int array_size = rand() % 100000;
    int a[array_size];
    for (int i = 0; i < array_size; i++) {
        a[i] = rand();
    }
    int max = numeric_limits<int>::min();
#pragma omp parallel num_threads(8)
    {
#pragma omp for
        for (int i = 0; i < array_size; i++) {
#pragma omp critical
            {
                if (a[i] % 7 == 0 && a[i] > max) {
                    max = a[i];
                }
            }
        }
    }
    if (max == numeric_limits<int>::min()) {
        printf("There is no multiplies of 7 in the array \n");
    }
    else {
        printf("The maximum multiply of 7 in the array is  %d", max);
    }
}
