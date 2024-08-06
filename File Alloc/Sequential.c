#include<stdio.h>
#include<string.h>
struct file {
    int name;
    int sb,length;
}
f[30];

int main() {
    int i,j,n;
    char s[20];
    printf("Enter no of files :");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("\nEnter file name : ");
        scanf("%d",&f[i].name);
        printf("Enter starting block of file %d :",f[i].name);
        scanf("%d",&f[i].sb);
        printf("Enter the length of the file %d :",f[i].name);
        scanf("%d",&f[i].length);
        printf("\n");
    }
    
    for(i=0;i<n;i++) {
        printf("\nFile Name: %d",f[i].name);
        printf("\nStart Block: %d",f[i].sb);
        printf("\nLength: %d",f[i].length);
        printf("\nFile is allocated from block %d to block %d",f[i].sb,f[i].sb+f[i].length-1);
        printf("\n");
        
        /*for(j=0;j<f[i].length;j++)
            printf("%d, ",f[i].sb+j);
        */
    }
    
    return 0;
}
