#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main() {
    FILE *f1, *f2,*f3,*f4,*f5;
    int i,len,pos;
    char arg[20],mne[20],opnd[20],la[20],name[20],
    mne1[20],opnd1[20],pos1[10],pos2[10];
    f1=fopen("input.txt","r");
    f2=fopen("namtab.txt","w+");
    f3=fopen("deftab.txt","w+");
    f4=fopen("argtab.txt","w+");
    f5=fopen("op.txt","w");
    fscanf(f1,"%s%s%s",la,mne,opnd);
    while(strcmp(mne,"END")!=0) {
        pos=1;
        if(strcmp(mne,"MACRO")==0) {
            fprintf(f2,"%s\n",la);
            fseek(f2,SEEK_SET,0);
            fprintf(f3,"%s\t%s\n",la,opnd);
            fscanf(f1,"%s%s%s",la,mne,opnd);
            while(strcmp(mne,"MEND")!=0) {
                if(opnd[0]=='&') {
                    sprintf(pos1,"%d",pos);
                    strcpy(pos2,"?");
                    strcpy(opnd,strcat(pos2,pos1));
                    pos=pos+1;
                }
                fprintf(f3,"%s\t%s\n",mne,opnd);
                fscanf(f1,"%s%s%s",la,mne,opnd);
            }
            fprintf(f3,"%s\n",mne);
        }
        else {
            fseek(f2,SEEK_SET,0);
            fscanf(f2,"%s",name);
            if(strcmp(mne,name)==0) {
                fseek(f4,SEEK_SET,0);
                len=strlen(opnd);
                for(i=0;i<len;i++) {
                    if(opnd[i]!=',')
                        fprintf(f4,"%c",opnd[i]);
                    else
                        fprintf(f4,"\n");
                }
                fseek(f3,SEEK_SET,0);
                fseek(f4,SEEK_SET,0);
                fscanf(f3,"%s%s",mne1,opnd1);
                fprintf(f5,".\t%s\t%s\n",mne1,opnd);
                fscanf(f3,"%s%s",mne1,opnd1);
                while(strcmp(mne1,"MEND")!=0) {
                    if((opnd1[0]=='?')) {    
                        fscanf(f4,"%s",arg);
                        fprintf(f5,"-\t%s\t%s\n",mne1,arg);
                    }
                    else
                        fprintf(f5,"-\t%s\t%s\n",mne1,opnd1);
                    fscanf(f3,"%s%s",mne1,opnd1);
                }
            }
            else
                fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
        }
        fscanf(f1,"%s\t%s\t%s",la,mne,opnd);
        
    }
        fprintf(f5,"%s\t%s\t%s",la,mne,opnd);
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        fclose(f5);
    printf("Successfull \n");
}
