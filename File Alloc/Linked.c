#include<stdio.h>
#include<stdlib.h>
int main() { 
    int f[50],p,a,st,len,n,c,ch;
    for(int i=0;i<50;i++)
        f[i]=0;     //unallocated
    printf("Enter the number of blocks which are already allocated: ");
    scanf("%d",&p);
    if(p!=0) {
        printf("\nEnter the blocks which are already allocated: ");
        for(int i=0;i<p;i++) {
            scanf("%d",&a);
            f[a]=1; //allocate the blocks
        }
    }
    
    printf("\n1. Add file \t2. Exit\n");
    scanf("%d",&ch);
    while(ch!=2) {
        if(ch==1) {
            printf("Enter the starting index block & length: ");
            scanf("%d%d",&st,&len);
            int k=len;
            for(int j=st;j<(k+st);j++) {
                if(f[j]==0) {
                    f[j]=1;
                    printf("\n%d->%d",j,f[j]);
                }
                else { 
                    printf("\n%d->file is already allocated",j);
                    k++;
                }
            }
            printf("\n");
        }
        else if(ch==2) {
            exit(0);
        }
        else {
            printf("Invalid choice");
        }
        printf("\n1. Get the blocks\t2. Exit\n");
        scanf("%d",&ch);
    }
    return 0;
}
