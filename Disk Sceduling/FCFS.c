#include<stdio.h>
#include<stdlib.h>

void main() {
    int RQ[100],i,n,TotalHeadMoment=0,initial;
    printf("Enter the no of requests: ");
    scanf("%d",&n);
    printf("Enter the requests sequence: ");
    for(i=0;i<n;i++) {
        scanf("%d",&RQ[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    
    for(i=0;i<n;i++) {
        TotalHeadMoment=TotalHeadMoment+abs(RQ[i]-initial);
        initial=RQ[i];
    }
    
    printf("Total head moment is %d",TotalHeadMoment);
}
