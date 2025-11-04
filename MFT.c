#include <stdio.h> 
#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10
int main() {
    int totalMemory, partitionSize, numPartitions;
    int numProcesses, processSize[MAX_PROCESSES];
    int partitionAllocated[MAX_PARTITIONS] = {0};
    int internalFragmentation[MAX_PARTITIONS] = {0};
    printf("Enter total memory size: ");
    scanf("%d", &totalMemory);
    printf("Enter fixed partition size: ");
    scanf("%d", &partitionSize);
    numPartitions = totalMemory / partitionSize;
    printf("Total partitions available: %d\n", numPartitions);
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    int processIndex = 0;
    for (int i = 0; i < numPartitions && processIndex < numProcesses; i++) {
        if (processSize[processIndex] <= partitionSize) {
            partitionAllocated[i] = processIndex + 1;
            internalFragmentation[i] = partitionSize - processSize[processIndex];
            processIndex++;
        }
    }
    printf("\nPartition Allocation:\n");
    for (int i = 0; i < numPartitions; i++) {
        if (partitionAllocated[i] != 0) {
            printf("Partition %d: Process %d (Internal Fragmentation: %d KB)\n",
                   i + 1, partitionAllocated[i], internalFragmentation[i]);
        } else {
            printf("Partition %d: Empty\n", i + 1);
        }
    }
    if (processIndex < numProcesses) {
        printf("\nProcesses not allocated due to insufficient partition size or memory:\n");
        for (int i = processIndex; i < numProcesses; i++) {
            printf("Process %d (Size: %d KB)\n", i + 1, processSize[i]);
        }
    }
    return 0;
}