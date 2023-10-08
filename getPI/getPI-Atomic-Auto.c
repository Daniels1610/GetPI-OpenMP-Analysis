#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 259999999

// getPI-Atomic-Auto
int threads[] = {1,2,3,4,5,6,7,8,9,10,15,20};
double step;
int numThreads = 0;

struct getPIValues {
    double pi;
    double runTime;
};

typedef struct getPIValues Struct;

Struct getPI(){
    omp_set_num_threads(numThreads);
    double sum = 0.0;
    Struct getPI_ReturnValues;

    step = 1.0/(double) NUM_STEPS;
    double start_time = omp_get_wtime();

    #pragma omp parallel
    { 
        double localSum = 0.0;
        int id = omp_get_thread_num();


        if (id == 0) {numThreads = omp_get_num_threads();}
        for (int offset = id; offset < NUM_STEPS; offset += numThreads)
        {
            double x = (offset-0.5) * step;
            localSum += 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        sum += localSum;
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