#include <stdio.h> 
#include <stdbool.h>
#define MAX_P 10
#define MAX_R 10
int Available[MAX_R];
int Max[MAX_P][MAX_R];
int Allocation[MAX_P][MAX_R];
int Need[MAX_P][MAX_R];
int safeSequence[MAX_P];
int P, R;
void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}
bool isSafe() {
    int Work[MAX_R];
    bool Finish[MAX_P] = {false};
    int count = 0;
    for (int i = 0; i < R; i++)
        Work[i] = Available[i];
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!Finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (Need[i][j] > Work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        Work[j] += Allocation[i][j];
                    safeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);
    printf("Enter Available resources:\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &Available[i]);
    printf("Enter Max matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &Max[i][j]);
    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &Allocation[i][j]);
    calculateNeed();
    if (isSafe()) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < P; i++)
            printf("P%d ", safeSequence[i]);
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }
    return 0;
}