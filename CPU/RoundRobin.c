#include <stdio.h>

int main() {
    int i,j, n, time=0, remain, flag = 0, ts;
    int at[10], bt[10], ct[10], wt[10], tat[10], rt[10];
    float totaltat = 0, totalwt = 0;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    remain = n;
    
    printf("\nEnter The Process Arrival Time and Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("Enter Arrival time of process[%d]: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst time of process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
    
    printf("\nEnter time slice: ");
    scanf("%d", &ts);
    
    int queue[50],rear=0,front=0;
    
    for(i=0;i<n;i++) {
        if(at[i]==0) {
            queue[rear++]=i;
        }
    }
    
    while (remain != 0) {
        
        i=queue[front++];
        
        if (rt[i] <= ts && rt[i] > 0) {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        } else if (rt[i] > 0) {
            rt[i] -= ts;
            time += ts;
        }
        
        if (rt[i] == 0 && flag == 1) {
            remain--;
            ct[i] = time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            totaltat += tat[i];
            totalwt += wt[i];
            flag = 0;
        }
        
        //processes that arrived during time slice
        for(j=0;j<n;j++) {
            if(at[j]>time-ts && at[j]<=time && rt[j]>0) {
                queue[rear++] = j;
            }
        }
        
        //if current process has not finished executing
        if(rt[i]>0) {
            queue[rear++] = i;
        }
        
    }
    
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t %d\t %d\t %d\t %d\t %d", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\n\nAverage Turnaround Time: %f", totaltat / n);
    printf("\nAverage Waiting Time: %f\n", totalwt / n);
    return 0;
}
