#include <stdio.h>
#include <stdbool.h>
#define MAX 50
void fifo(int pages[], int n, int frames) {
    int queue[MAX], front = 0, rear = 0, faults = 0;
    bool inFrame[MAX] = {false};
    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (!inFrame[pages[i]]) {
            faults++;
            if (rear - front == frames) {
                inFrame[queue[front]] = false;
                front++;
            }
            queue[rear++] = pages[i];
            inFrame[pages[i]] = true;
        }
        printf("Page %d -> ", pages[i]);
        for (int j = front; j < rear; j++)
            printf("%d ", queue[j]);
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}
void lru(int pages[], int n, int frames) {
    int memory[MAX], time[MAX], faults = 0;
    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < frames; i++)
        memory[i] = -1;
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = true;
                time[j] = i;
                break;
            }
        }
        if (!found) {
            faults++;
            int lruIndex = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[lruIndex])
                    lruIndex = j;
            }
            memory[lruIndex] = pages[i];
            time[lruIndex] = i;
        }
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < frames; j++)
            if (memory[j] != -1)
                printf("%d ", memory[j]);
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}
int predict(int pages[], int memory[], int n, int index, int frames) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (memory[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}
void optimal(int pages[], int n, int frames) {
    int memory[MAX], faults = 0;
    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < frames; i++)
        memory[i] = -1;
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            faults++;
            int replaceIndex = -1;
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }
            if (replaceIndex == -1)
                replaceIndex = predict(pages, memory, n, i + 1, frames);
            memory[replaceIndex] = pages[i];
        }
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < frames; j++)
            if (memory[j] != -1)
                printf("%d ", memory[j]);
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}
int main() {
    int pages[MAX], n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);
    return 0;
}