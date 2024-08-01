#include<stdio.h>

int main() {
    int n, at[10], bt[10], wt[10], tat[10], ct[10], pr[10], p[10], sum, i, j, k, pos, temp;
    float totaltat = 0, totalwt = 0;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    
    printf("\nEnter The Process Arrival Time, Burst Time and Priority\n");
    for(i = 0; i < n; i++) {
        printf("Enter Arrival time of process[%d]: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst time of process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter priority of process[%d]: ", i + 1);
        scanf("%d", &pr[i]);
        p[i]=i+1;
        printf("\n");
    }
    
    
    // Sort processes based on arrival time
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(at[j] > at[j + 1]) {
                
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;
                
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    // Calculate completion time, turnaround time, and waiting time
    sum = at[0];
    for(i = 0; i < n; i++) {
        // Find the process with the highest priority (lowest priority number) among the processes that have arrived
        pos = i;
        for(j = i + 1; j < n; j++) {
            if(at[j] <= sum && pr[j] < pr[pos]) {
                pos = j;
            }
        }
        
        // Swap to bring the selected process to the current position
        if(pos != i) {
            temp = at[i];
            at[i] = at[pos];
            at[pos] = temp;

            temp = bt[i];
            bt[i] = bt[pos];
            bt[pos] = temp;

            temp = pr[i];
            pr[i] = pr[pos];
            pr[pos] = temp;
            
            temp = p[j];
            p[j] = p[j + 1];
            p[j + 1] = temp;
        }

        if (sum < at[i]) {
            sum = at[i];
        }
        
        sum += bt[i];
        ct[i] = sum;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totaltat += tat[i];
        totalwt += wt[i];
    }
    
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("\nP%d\t %d\t %d\t %d\t %d\t %d",p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
   
    printf("\n\nAverage Turnaround Time: %.2f", totaltat / n);
    printf("\nAverage Waiting Time: %.2f", totalwt / n);
    
    return 0;
}
