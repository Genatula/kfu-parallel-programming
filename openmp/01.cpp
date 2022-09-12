/*
 * Write a program where each thread prints its id, a total amount of threads and a "Hello World" string
 * Total number of threads : 8
 * */
#include <iostream>
#include <omp.h>

using namespace std;

int main() {
#pragma omp parallel num_threads(8)
    {
        int amount = omp_get_num_threads();
        int id = omp_get_thread_num();
        printf("Thread id = %d \n", id);
        printf("Hello world from thread %d \n", id);
        printf("Total amount of threads = %d \n", amount);
    }
    return 0;
}
