#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
    FILE *f1,*f2,*f3,*f4,*f5;   //file pointers
    int len,i,pos=1;
    char
    arg[20],mne[20],opnd[20],la[20],name[20],
    mne1[20],opnd1[20],pos1[10],pos2[10];
    f1=fopen("input.txt","r");
    f2=fopen("namtab.txt","w+");
    f3=fopen("deftab.txt","w+");
    f4=fopen("argtab.txt","w+");
    f5=fopen("op.txt","w");   //expanded code file
    fscanf(f1,"%s%s%s",la,mne,opnd);    //reads first line of input file
    while(strcmp(mne,"END")!=0) {       //checks if mnemonic!=END
        if(strcmp(mne,"MACRO")==0) {    //checking if its a macro
            fprintf(f2,"%s\n",la);      //adding macro name to namtab
            fseek(f2,SEEK_SET,0);       //reset pointer to namtab to beginning
            fprintf(f3,"%s\t%s\n",la,opnd);     // enter macro prototype in to deftab
            fscanf(f1,"%s%s%s",la,mne,opnd);    //read next line of input
            while(strcmp(mne,"MEND")!=0) {      //checks if mnemonic!=MEND
                if(opnd[0]=='&') {      //checks if operand begins with &
                    sprintf(pos1,"%d",pos); //replace parameters with positional notation
                    strcpy(pos2,"?");
                    strcpy(opnd,strcat(pos2,pos1));
                    pos=pos+1;
                }
                fprintf(f3,"%s\t%s\n",mne,opnd);    //write macro definition to deftab
                fscanf(f1,"%s%s%s",la,mne,opnd);    //read next line of input
            }
            fprintf(f3,"%s",mne);       //writes MEND to deftab
        }
        else {
            fscanf(f2,"%s",name);       //read macro name from namtab
            if(strcmp(mne,name)==0) {   //checks if mnemonic from deftab,namtab match
                len=strlen(opnd);       //if match found,find length of operand
                for(i=0;i<len;i++) {
                    if(opnd[i]!=',')
                        fprintf(f4,"%c",opnd[i]);   //add operands to argtab
                    else
                        fprintf(f4,"\n");
                }
                fseek(f3,SEEK_SET,0);   //reset deftab pointer to its beginning
                fseek(f4,SEEK_SET,0);   //reset argtab pointer to its beginning
                fscanf(f3,"%s%s",mne1,opnd1);
                fprintf(f5,".\t%s\t%s\n",mne1,opnd);    //commented macro invocation statement
                fscanf(f3,"%s%s",mne1,opnd1);       //reading a line of macro definition
                while(strcmp(mne1,"MEND")!=0) {     //repeat until the mnemonic is not MEND
                    if((opnd[0]=='?')) { 
                        fscanf(f4,"%s",arg);        //read argument from argtab
                        fprintf(f5,"-\t%s\t%s\n",mne1,arg); //print mne1 from deftab,arg from argtab
                    }
                    else
                        fprintf(f5,"-\t%s\t%s\n",mne1,opnd1);
                    fscanf(f3,"%s%s",mne1,opnd1);
                }
            }
            else
                fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
        }
        fscanf(f1,"%s%s%s",la,mne,opnd);    //read next line from input table
    }
    fprintf(f5,"%s\t%s\t%s",la,mne,opnd);   //writes END to output file
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    printf("Successfull !!! \n");
}
