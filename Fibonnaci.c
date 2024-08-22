#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    int x, y;
    if (n < 2) {
        return n;
    } else {
        #pragma omp task shared(x)
        {
            x = fibonacci(n - 1);
        }

        #pragma omp task shared(y)
        {
            y = fibonacci(n - 2);
        }

        #pragma omp taskwait
        return x + y;
    }
}
int main() {
    int n = 10; 
    int result;
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }
    double end_time = omp_get_wtime();
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
