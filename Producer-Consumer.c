#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int mutex = 1;  // Mutex for critical section
int full = 0;   // Number of full slots
int empty = 10; // Number of empty slots in the buffer
int x = 0;      // Shared variable for item count

void producer() {
    --mutex;    // Enter critical section
    ++full;     // Increase full slot count
    --empty;    // Decrease empty slot count
    x++;        // Produce an item
    printf("\nProducer produces item %d", x);
    ++mutex;    // Exit critical section
}

void consumer() {
    --mutex;    // Enter critical section
    --full;     // Decrease full slot count
    ++empty;    // Increase empty slot count
    printf("\nConsumer consumes item %d", x);
    x--;        // Consume an item
    ++mutex;    // Exit critical section
}

int main() {
    int n;

    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        #pragma omp critical
        {
            switch (n) {
                case 1:
                    if (mutex == 1 && empty != 0) {
                        producer();
                    } else {
                        printf("Buffer is full!");
                    }
                    break;
                case 2:
                    if (mutex == 1 && full != 0) {
                        consumer();
                    } else {
                        printf("Buffer is empty!");
                    }
                    break;
                case 3:
                    exit(0);
                default:
                    printf("Invalid choice!");
            }
        }
    }

    return 0;
}
