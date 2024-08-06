#include<stdio.h>
#include<stdlib.h>

void main() {
    int RQ[100],i,j,n,TotalHeadMoment=0,initial,size,move,temp,index;
    printf("Enter the no of requests: ");
    scanf("%d",&n);
    printf("Enter the requests sequence: ");
    for(i=0;i<n;i++) {
        scanf("%d",&RQ[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter total disk size: ");
    scanf("%d",&size);
    printf("Enter the head movement direction for high 1 and low 0: ");
    scanf("%d",&move);
    
    //Sort the request array
    for(i=0;i<n;i++) {
        for(j=0;j<n-i-1;j++) {
            if(RQ[j]>RQ[j+1]) {
                temp=RQ[j];
                RQ[j]=RQ[j+1];
                RQ[j+1]=temp;
            }
        }
    }
    
    for(i=0;i<n;i++) {
        if(initial<RQ[i]) {
            index=i;
            break;
        }
    }
    
    //if movement is towards high value
    if(move==1) {
        for(i=index;i<n;i++) {
            TotalHeadMoment=TotalHeadMoment+abs(RQ[i]-initial);
            initial=RQ[i];
        }
        //last movement for max size
        TotalHeadMoment=TotalHeadMoment+abs(size-RQ[i-1]-1);
        initial=size-1;
        for(i=index-1;i>=0;i--) {
            TotalHeadMoment=TotalHeadMoment+abs(RQ[i]-initial);
            initial=RQ[i];
        }
    }
    
    //if movement is towards low value
    else{
        for(i=index-1;i>=0;i--) {
            TotalHeadMoment=TotalHeadMoment+abs(RQ[i]-initial);
            initial=RQ[i];
        }
        //last movement for min size
        TotalHeadMoment=TotalHeadMoment+abs(RQ[i+1]-0);
        initial=0;
        for(i=index;i<n;i++) {
            TotalHeadMoment=TotalHeadMoment+abs(RQ[i]-initial);
            initial=RQ[i];
        }
    }
    
    printf("Total head movement is %d",TotalHeadMoment);
}
