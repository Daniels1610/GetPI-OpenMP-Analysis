#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 259999999
#define NUM_THREADS 6
// #define PAD 64
// #define ARR_SIZE NUM_STEPS + (NUM_THREADS * PAD)

// getPI-PAD
int threads[] = {1,2,3,4,5,6,7,8,9,10,15,20};
double step; 
double arr[ARR_SIZE];
int numThreads = 0;
int inputThreads = 0;

struct getPIValues {
    double pi;
    double runTime;
};

typedef struct getPIValues Struct;

Struct getPI(){
    omp_set_num_threads(NUM_THREADS);
    double sum = 0.0;
    Struct getPI_ReturnValues;
    step = 1.0/(double) NUM_STEPS;
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        if (id == 0) {numThreads = omp_get_num_threads();}
        for (int i = id; i < NUM_STEPS; i += numThreads)
        {
            double x = (i-0.5) * step;
            arr[i+PAD] = 4.0 / (1.0 + x * x);
        }
    }
    
    for (int i = 0; i < NUM_STEPS; i++)
    {
        sum += arr[i+PAD];
    } 
    
    getPI_ReturnValues.pi = step * sum; 
    getPI_ReturnValues.runTime = omp_get_wtime() - start_time;
    return getPI_ReturnValues;
}

int main () {
    for (int j = 0; j < 12; j++){
        numThreads = threads[j];
        printf("THREAD NUM: %d", numThreads);
        for (int i = 0; i < 5; i++){
            Struct result = getPI();
            printf("\n pi with %d steps is %lf in %lf seconds\n ", NUM_STEPS, result.pi, result.runTime);
        }
    }
}