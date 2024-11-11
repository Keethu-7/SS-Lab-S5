#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void convert(char h[12]);   //function to convert bitmask into relocation bits
char bitmask[12];       //max bit mask length is 12
char bit[12] = {0};
void main() {
    char input[10], binary[12], relocbit, ch, pn[5];
    int add[6], length[10];
    int start, inp, len, i, address, opcode, addr, actualadd, tlen;
    FILE *fp1, *fp2;
    printf("\n\n Enter the actual starting address : ");    //getting starting address from user
    scanf("%x", &start);
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");
    fscanf(fp1, "%s", input);       //read input type from input file
    fprintf(fp2, " ----------------------------\n");
    fprintf(fp2, " ADDRESS\tCONTENT\n");
    fprintf(fp2, " ----------------------------\n");
    while (strcmp(input, "E") != 0) {       //until input record type is not E
        if (strcmp(input, "H") == 0) {      //until input  type is H
            fscanf(fp1, "%s", pn);        //read program name
            fscanf(fp1, "%x", add);     //read starting address from file
            fscanf(fp1, "%x", length);  //read object program length
            fscanf(fp1, "%s", input);   //read input record type
        }
        if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x", &address);    //read starting address of object code in this record
            fscanf(fp1, "%x", &tlen);       //read length of obj code in this record
            fscanf(fp1, "%s", bitmask);     //read relocation bitmask of this record
            address += start;       //adding text address to start address
            convert(bitmask);
            len = strlen(bit);  //length of bit mask
            if (len >= 11)
                len = 10;       //adjust len to 10 since maximum object code in a text record is 10
            for (i = 0; i < len; i++) {
                fscanf(fp1, "%x", &opcode);     //read opcode
                fscanf(fp1, "%x", &addr);       //read operand address
                relocbit = bit[i];      //each relocation bit extracted to relocbit
                if (relocbit == '0')    //if relocbit is 0
                    actualadd = addr;   //relocated address is addr
                else
                    actualadd = addr + start;   //relocated address is sum of start addr given and addr
                fprintf(fp2, "\n  %x\t\t%x%x\n", address, opcode, actualadd);
                address += 3;
            }
            fscanf(fp1, "%s", input);
        }
    }
    fprintf(fp2, " ----------------------------\n");
    fclose(fp1);
    fclose(fp2);
    printf("\n\n The contents of output file(output.txt) \n\n");
    fp2 = fopen("output.txt", "r");
    ch = fgetc(fp2);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp2);
    }
    fclose(fp2);
}

void convert(char h[12]) {
    int i, l;
    strcpy(bit, "");
    l = strlen(h);
    for (i = 0; i < l; i++) {
        switch (h[i]) {
        case '0':
            strcat(bit, "0");
            break;
        case '1':
            strcat(bit, "1");
            break;
        case '2':
            strcat(bit, "10");
            break;
        case '3':
            strcat(bit, "11");
            break;
        case '4':
            strcat(bit, "100");
            break;
        case '5':
            strcat(bit, "101");
            break;
        case '6':
            strcat(bit, "110");
            break;
        case '7':
            strcat(bit, "111");
            break;
        case '8':
            strcat(bit, "1000");
            break;
        case '9':
            strcat(bit, "1001");
            break;
        case 'A':
            strcat(bit, "1010");
            break;
        case 'B':
            strcat(bit, "1011");
            break;
        case 'C':
            strcat(bit, "1100");
            break;
        case 'D':
            strcat(bit, "1101");
            break;
        case 'E':
            strcat(bit, "1110");
            break;
        case 'F':
            strcat(bit, "1111");
            break;
        }
    }
}
