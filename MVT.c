#include <stdio.h>
#define MAX_PROCESSES 20
int main() {
    int totalMemory, usedMemory = 0;
    int numProcesses, processSize[MAX_PROCESSES];
    int allocated[MAX_PROCESSES] = {0};
    printf("Enter total memory size (in KB): ");
    scanf("%d", &totalMemory);
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter memory required for Process %d (in KB): ", i + 1);
        scanf("%d", &processSize[i]);
        if (processSize[i] <= (totalMemory - usedMemory)) {
            allocated[i] = 1;
            usedMemory += processSize[i];
            printf("Process %d allocated %d KB\n", i + 1, processSize[i]);
        } else {
            printf("Process %d cannot be allocated due to insufficient memory.\n", i + 1);
        }
    }
    int externalFragmentation = totalMemory - usedMemory;
    printf("\nMemory Allocation Summary:\n");
    for (int i = 0; i < numProcesses; i++) {
        if (allocated[i])
            printf("Process %d: Allocated %d KB\n", i + 1, processSize[i]);
        else
            printf("Process %d: Not Allocated\n", i + 1);
    }
    printf("\nTotal Used Memory: %d KB\n", usedMemory);
    printf("Total Free Memory (External Fragmentation): %d KB\n", externalFragmentation);
    return 0;
}