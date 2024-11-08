#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main() {
    FILE *fp;
    int i,j,stdaddr1;
    char line[50],name1[50],staddr[200];
    
    fp=fopen("ab.txt","r");
    fscanf(fp,"%s",line);       //read first line - header rec
    for(i=2,j=0;line[i]!='^';i++,j++) {     //i=2 to avoid H^
        name1[j]=line[i];       //store name of prgm from header record
    }
    name1[j]='\0';              //string end
    printf("name from obj.%s\n",name1);
    
    while(!feof(fp)) {  
        fscanf(fp,"%s",line);
        while(line[0]=='T') {
            for(i=2,j=0;line[i]!='^';i++,j++) {
                staddr[j]=line[i];  //starting addr of that text rec-string format
            }
            staddr[j]='\0';
            stdaddr1=atoi(staddr);  //convert addr to int from string
            i=12;           //object code starts from index 12
            
            while(line[i]!='$') {
                if(line[i]!='^') {
                    //two bytes of object code is stored in one addrress
                    printf("00%d\t%c%c\n",stdaddr1,line[i],line[i+1]);
                    stdaddr1++;
                    i=i+2;  //two char in one adrr, so skip two char
                }
                else {  //if line=^ then skip and will reach nect obj code
                    i++;
                }
            }
            fscanf(fp,"%s",line);
        }
        if(line[0]=='E') {
            fclose(fp);
        }
        
    }
}




/*
OUTPUT

name from obj.COPY
001000	00
001001	10
001002	03
001003	00
001004	11
001005	22
002000	01
002001	0B
002002	0A
*/
