#include<stdio.h>

void main() {
    int i,j,k,f,pf=0,count=0,rs[25],m[10],n;
    printf("Enter the length of reference string: ");
    scanf("%d",&n);
    printf("Enter the reference string: ");
    for(i=0;i<n;i++) {
        scanf("%d",&rs[i]);
    }
    printf("Enter no of frames: ");
    scanf("%d",&f);
    for(i=0;i<f;i++) {
        m[i]=-1;
    }
    
    
    for(i=0;i<n;i++) {
        for(k=0;k<f;k++) {
            if(m[k]==rs[i]) {  // page hit
                break;
            }
        }
        if(k==f) {
            m[count++] = rs[i];
            pf++;
        }
        for(j=0;j<f;j++) {
            printf("\t%d",m[j]);
        }
        if(k==f) {
            printf("\tPF No. %d",pf);
        }
        printf("\n");
        if(count==f) {
            count=0;
        }
    }
    printf("\n The number of page faults using FIFO are %d",pf);
}
