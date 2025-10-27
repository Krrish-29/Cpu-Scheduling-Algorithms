#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int ganttChartProcessLen=0,ganttChartProcessCapacity=1;
void addProcess(int **dynamicarray,int element){
    if(ganttChartProcessLen>=ganttChartProcessCapacity){
        ganttChartProcessCapacity++;
        *dynamicarray=realloc(*dynamicarray,ganttChartProcessCapacity*sizeof(int));
    }
    (*dynamicarray)[ganttChartProcessLen]=element;
    ganttChartProcessLen++;
}
int ganttChartProcessTimeLen=0,ganttChartProcessTimeCapacity=1;
void addTime(int **dynamicarray,int element){
    if(ganttChartProcessTimeLen>=ganttChartProcessTimeCapacity){
        ganttChartProcessTimeCapacity++;
        *dynamicarray=realloc(*dynamicarray,ganttChartProcessTimeCapacity*sizeof(int));
    }
    (*dynamicarray)[ganttChartProcessTimeLen]=element;
    ganttChartProcessTimeLen++;
}
typedef struct queue{
    int front;
    int rear;
    int *arr;
    int capacity;
}Queue;
Queue* initialize_queue(){
    Queue*queue=(Queue*)calloc(1,sizeof(Queue));
    queue->front=-1;
    queue->rear=-1;
    queue->arr=(int*)calloc(1,sizeof(int));
    queue->capacity=1;
    return queue;
}
bool isEmpty(Queue*queue){
    return queue->rear==-1;  
}
bool isFull(Queue*queue){
    return (queue->rear+1)%queue->capacity==queue->front;
}
int getSize(Queue*queue){
    if(isEmpty(queue)){
        return 0;
    }
    else if(queue->rear>=queue->front){
        return queue->rear-queue->front+1;
    }
    else{
        return queue->capacity-(queue->front-queue->rear)-1;
    }
}
void enqueue(Queue*queue,int data){
    if(isFull(queue)){
        queue->capacity*=2;
        int * new_array=(int*)calloc(queue->capacity,sizeof(int));
        int size=getSize(queue);
        for(int i=0;i<size;i++){
            new_array[i]=queue->arr[(queue->front+i)%queue->capacity];
        }
        free(queue->arr);
        queue->arr=new_array;
        queue->front=0;
        queue->rear=size-1;
    }
    if(isEmpty(queue)){
        queue->front=queue->rear=0;
    }
    else{
        queue->rear=(queue->rear+1)%queue->capacity;
    }
    queue->arr[queue->rear]=data;
}
int dequeue(Queue*queue){
    if(isEmpty(queue)){
        return -1;
    }
    int return_value=queue->arr[queue->front];
    if(queue->front==queue->rear){
        queue->front=queue->rear=-1;
    }
    else{
        queue->front=(queue->front+1)%queue->capacity;
    }
    return return_value;
}
int main(){
    printf("\nRound Robin process scheduling\n\n");
    printf("How many processes you want to schedule: ");
    int totalProcesses;
    scanf("%d",&totalProcesses);
    printf("\nQuantum value for Round Robin: ");
    int quantum;
    scanf("%d",&quantum);
    Queue*queue=initialize_queue();
    int *ganttChartTime=(int*)calloc(1,sizeof (int));  
    int *ganttChartProcess=(int*)calloc(1,sizeof (int));  
    int *pid=(int*)calloc(totalProcesses,sizeof(int));
    int *arrivalTime=(int*)calloc(totalProcesses,sizeof(int));
    int *arrivalTimeCopy=(int*)calloc(totalProcesses,sizeof(int));
    int *burstTime=(int*)calloc(totalProcesses,sizeof(int));
    int *burstTimeCopy=(int*)calloc(totalProcesses,sizeof(int));
    int *completionTime=(int*)calloc(totalProcesses,sizeof(int));
    int *turnAroundTime=(int*)calloc(totalProcesses,sizeof(int));
    int *waitingTime=(int*)calloc(totalProcesses,sizeof(int));
    for(int i=0;i<totalProcesses;i++){
        pid[i]=i;
        printf("\nArrival time of process P%d : ",i);
        scanf("%d",&arrivalTime[i]);
        arrivalTimeCopy[i]=arrivalTime[i];
        printf("Burst time of process P%d : ",i);
        scanf("%d",&burstTime[i]);
        burstTimeCopy[i]=burstTime[i];
    }
    int time=0,completedProcesses=0;
    float avgTAT=0,avgWT=0;
    while(completedProcesses<totalProcesses){
        for(int i=0;i<totalProcesses;i++){
            if(arrivalTimeCopy[i]<=time){
                enqueue(queue,i);
                arrivalTimeCopy[i]=1e7;
            }
        }
        if(isEmpty(queue)){
            time++;
            addTime(&ganttChartTime,time-1);
            addTime(&ganttChartTime,time);  
            addProcess(&ganttChartProcess,-1);
            continue;
        }
        while(!isEmpty(queue)){
            int idx=dequeue(queue);
            addTime(&ganttChartTime,time);
            for(int j=1;j<=quantum;j++){
                for(int i=0;i<totalProcesses;i++){
                    if(arrivalTimeCopy[i]<=time){
                        enqueue(queue,i);
                        arrivalTimeCopy[i]=1e7;
                    }
                }
                time++;
                burstTimeCopy[idx]--;
                if(burstTimeCopy[idx]==0){
                    addTime(&ganttChartTime,time);  
                    addProcess(&ganttChartProcess,pid[idx]);
                    completionTime[idx]=time;
                    turnAroundTime[idx]=completionTime[idx]-arrivalTime[idx];
                    waitingTime[idx]=turnAroundTime[idx]-burstTime[idx];
                    avgTAT+=turnAroundTime[idx];
                    avgWT+=waitingTime[idx];
                    completedProcesses++;
                    break;
                }
                if(j==quantum){
                    enqueue(queue,idx);
                    addTime(&ganttChartTime,time);  
                    addProcess(&ganttChartProcess,pid[idx]);
                }
            }
        }
    }



    printf("\n");
    printf("Gantt Chart:\n");
    for(int i=0;i<ganttChartProcessCapacity;i++){
        printf("------");
    }
    printf("-\n");
    for(int i=0;i<ganttChartProcessLen;i++){
        if(ganttChartProcess[i]==-1) printf("|     ");
        else printf("| P%2d ",ganttChartProcess[i]);
    }
    printf("|\n");
    for(int i=0;i<ganttChartProcessLen;i++){
        printf("------");
    }
    printf("-\n");
    printf("%2d    ",ganttChartTime[0]);
    for(int i=1;i<ganttChartProcessTimeCapacity;i++){
        printf("%2d    ",ganttChartTime[i]);
        i++;
    }

    printf("\n\nThe scheduling for Round Robin :\n");
    printf("\nProcess Id | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
    for(int i=0;i<totalProcesses;i++) printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pid[i],arrivalTime[i],burstTime[i],completionTime[i],turnAroundTime[i],waitingTime[i]);
    printf("\nAverage TurnAround Time: %.2f \nAverage Waiting Time: %.2f",avgTAT/totalProcesses,avgWT/totalProcesses);
    return 0;
}