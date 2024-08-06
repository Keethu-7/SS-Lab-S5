#include<stdio.h>

void main() {
    int i,j,k,min,flag[25],count[10],rs[25],m[10],n,f,pf=0,next;
    printf("Enter the length of reference string: ");
    scanf("%d",&n);
    printf("Enter the reference string: ");
    for(i=0;i<n;i++) {
        scanf("%d",&rs[i]);
        flag[i]=0;
    }
    printf("Enter no of frames: ");
    scanf("%d",&f);
    for(i=0;i<f;i++) {
        count[i]=0;
        m[i]=-1;
    }
    
    
    for(i=0;i<n;i++) {
        for(j=0;j<f;j++) {
            if(m[j]==rs[i]) {
                flag[i]=1;
                count[j]=next;
                next++;
            }
        }
        if(flag[i]==0) {
            if(i<f) {
                m[i]=rs[i];
                count[i]=next;
                next++;
            }
            else {
                min=0;
                for(j=1;j<f;j++) {
                    if(count[min]>count[j]) {
                        min=j;
                    }
                }
                m[min]=rs[i];
                count[min]=next;
                next++;
            }
            pf++;
        }
        
        for(j=0;j<f;j++) {
            printf("%d\t",m[j]);
        }
        if(flag[i]==0) {
            printf("PF No. %d",pf);
        }
        printf("\n");
    }
    printf("\nThe number of page faults using LRU are %d",pf);
}
