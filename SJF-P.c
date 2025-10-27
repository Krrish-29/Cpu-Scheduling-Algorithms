#include <stdio.h>
#include<stdlib.h>
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
int main(){
    printf("\nShortest Job First process scheduling (Preemptive)\n\n");
    printf("How many processes you want to schedule: ");
    int totalProcesses;
    scanf("%d",&totalProcesses);
    int *ganttChartTime=(int*)calloc(1,sizeof (int));  
    int *ganttChartProcess=(int*)calloc(1,sizeof (int));  
    int *pid=(int*)calloc(totalProcesses,sizeof(int));
    int *arrivalTime=(int*)calloc(totalProcesses,sizeof(int));
    int *burstTime=(int*)calloc(totalProcesses,sizeof(int));
    int *burstTimeCopy=(int*)calloc(totalProcesses,sizeof(int));
    int *completionTime=(int*)calloc(totalProcesses,sizeof(int));
    int *turnAroundTime=(int*)calloc(totalProcesses,sizeof(int));
    int *waitingTime=(int*)calloc(totalProcesses,sizeof(int));
    for(int i=0;i<totalProcesses;i++){
        pid[i]=i;
        printf("\nArrival time of process P%d : ",i);
        scanf("%d",&arrivalTime[i]);
        printf("Burst time of process P%d : ",i);
        scanf("%d",&burstTime[i]);
        burstTimeCopy[i]=burstTime[i];
    }
    int time=0,completedProcesses=0;
    float avgTAT=0,avgWT=0;
    while(completedProcesses<totalProcesses){
        int minBT=1e9,idx=-1;
        for(int i=0;i<totalProcesses;i++){
            if(burstTimeCopy[i]<minBT&&arrivalTime[i]<=time) {
                minBT=burstTimeCopy[i];
                idx=i;
            }
        }
        if(idx==-1) {
            time++;
            addTime(&ganttChartTime,time-1);  
            addTime(&ganttChartTime,time);  
            addProcess(&ganttChartProcess,-1);
            continue;
        }
        time++;
        burstTimeCopy[idx]--;
        addTime(&ganttChartTime,time-1);  
        addTime(&ganttChartTime,time);  
        addProcess(&ganttChartProcess,pid[idx]);
        if(burstTimeCopy[idx]==0){
            burstTimeCopy[idx]=1e9;
            completionTime[idx]=time;
            turnAroundTime[idx]=completionTime[idx]-arrivalTime[idx];
            waitingTime[idx]=turnAroundTime[idx]-burstTime[idx];
            avgTAT+=turnAroundTime[idx];
            avgWT+=waitingTime[idx];
            completedProcesses++;
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

    printf("\n\nThe scheduling for Shortest Job First Preemptive:\n");
    printf("\nProcess Id | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
    for(int i=0;i<totalProcesses;i++) printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pid[i],arrivalTime[i],burstTime[i],completionTime[i],turnAroundTime[i],waitingTime[i]);
    printf("\nAverage TurnAround Time: %.2f \nAverage Waiting Time: %.2f",avgTAT/totalProcesses,avgWT/totalProcesses);
    return 0;
}