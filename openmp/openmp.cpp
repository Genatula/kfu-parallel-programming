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
 * Write a program with 2 parallel areas which execution depends on `#pragma omp parallel if(...)`
 * The condition is as follows : if the set number of threads is greater than 1, than the area is executed
 * Set the number of threads before the 1st area to 3, before the 2nd one - to 1
 * Inside the areas find out and print the number of threads and their identifiers
 */

void executeSecondOpenMpTask() {

}
