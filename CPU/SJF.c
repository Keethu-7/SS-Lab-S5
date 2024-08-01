#include<stdio.h>
int main() {
    int n,at[10],bt[10],wt[10],tat[10],ct[10],p[10],sum,i,j,k,temp;
    float totaltat=0,totalwt=0;
    printf("Enter the total number of processes:");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("Enter process id: P");
        scanf("%d",&p[i]);
        printf("Enter Arrival time of P[%d]: ",p[i]);
        scanf("%d",&at[i]);
        printf("Enter Burst time of P[%d]: ",p[i]);
        scanf("%d",&bt[i]);
        printf("\n");
    }
    /* Apply Bubble sort to sort according to arrival time */
    for(i=0;i<n;i++) {
        for(j=0;j<n-i-1;j++) {
            if(at[j]>at[j+1]) {
                temp=at[j];
                at[j]=at[j+1];
                at[j+1]=temp;
                
                temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    
    
    // Calculate completion time, turnaround time and waiting time
    sum = at[0];
    for(i = 0; i < n; i++) {
        // Find the process with the minimum burst time among the processes that have arrived
        int min = i;
        for(j = i + 1; j < n; j++) {
            if(at[j] <= sum && bt[j] < bt[min]) {
                min = j;
            }
        }
        
        // Swap to bring the selected process to the current position
        if(min != i) {
            temp = at[i];
            at[i] = at[min];
            at[min] = temp;

            temp = bt[i];
            bt[i] = bt[min];
            bt[min] = temp;

            temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }

        sum += bt[i];
        ct[i] = sum;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totaltat += tat[i];
        totalwt += wt[i];
    }
    
    
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n\n\n");
    for(i=0;i<n;i++) {
        printf("\nP%d\t %d\t %d\t %d\t %d\t %d\n",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
   
    printf("\nAverage TurnaroundTime:%f\n",totaltat/n);
    printf("\nAverage Waiting Time:%f",totalwt/n);
 
    return 0;
}
