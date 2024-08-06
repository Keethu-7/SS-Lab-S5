#include<stdio.h>
#include<stdlib.h>

struct file
{
    int nob, blocks[30], start, length;
}
f[30];

int main() {
    int i, j, n, s, ch;
    printf("Enter no of files : ");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("Enter the start address of file %d: ",i+1);
        scanf("%d",&f[i].start);
        printf("Enter the length of file %d: ",i+1);
        scanf("%d",&f[i].length);
        printf("Enter no of blocks in file %d: ",i+1);
        scanf("%d",&f[i].nob);
        printf("Enter the blocks of the file: ");
        for(j=0;j<f[i].nob;j++)
            scanf("%d",&f[i].blocks[j]);
        printf("\n");
    }
    
    for(i=0;i<n;i++) {
        printf("File no: %d",i+1);
        printf("\tNo of blocks: %d",f[i].nob);
        printf("\t\tLength: %d",f[i].length);
        printf("\tStart address: %d",f[i].start);
        printf("\n");
        
    }
    
    
    printf("1. Get the blocks\t2. Exit\n");
    scanf("%d",&ch);
    while(ch!=2) {
        if(ch==1) {
            printf("\nEnter the file number: ");
            scanf("%d",&s);
            printf("Blocks allocated : \n");
            for(j=0;j<f[s-1].nob;j++)
                printf("%d\t",f[s-1].blocks[j]);
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
