#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
    int start, locctr, length, locdisp = 8192;
    printf("\n Pass 1 of a two pass assembler : ");
    printf("\n Loc\tLabel\tOpcode\tOperand\n");
    char opcode[20], operand[20], label[20], code[20], mnemonic[20];
    FILE *fp_in, *fp_op, *fp_sy, *fp_ou, *fp_len;
    fp_in = fopen("input.txt", "r"); // open input.txt in read mode
    fp_op = fopen("optab.txt", "r"); // open optab.txt in read mode
    fp_sy = fopen("symtab.txt", "w"); // open symtab.txt in write mode
    fp_ou = fopen("output.txt", "w"); // open output.txt in write mode
    fp_len = fopen("length.txt", "w"); // open length.txt in write mode
    fscanf(fp_in, "%s\t%s\t%s", label, opcode, operand); // read label, opcode, and operand from input.txt
    if (strcmp(opcode, "START") == 0){ // check if opcode == START
        start = atoi(operand); // save integer equivalent of operand as starting address
        locctr = start; // initialize locctr to starting address
        fprintf(fp_ou, "\t\t%s\t%s\t%s\n", label, opcode, operand); // write line to intermediate file
        printf("%d\t%s\t%s\t%s\n", locctr, label, opcode, operand); // print to terminal
        fscanf(fp_in, "%s\t%s\t%s", label, opcode, operand);
    }   
    else
        locctr = 0; // initialize locctr as 0
    while (strcmp(opcode, "END") != 0) {
        fprintf(fp_ou, "%d\t", locctr);
        printf("%X\t", locdisp);
        if (strcmp(label, "**") != 0){ // check for symbol in label field            
            fprintf(fp_sy, "%s\t%d\n", label, locctr);
        } // insert (label, locctr) into symtab
        fscanf(fp_op, "%s\t%s\n", mnemonic, code); // read (mnemonic, code) from optab
        while (strcmp(mnemonic, "END") != 0) {
            if (strcmp(opcode, mnemonic) == 0){ // checking if the read opcode is present in OPTAB.txt
                // additional code here
                locctr += 3; // add instruction length to locctr
                locdisp += 3; 
                break;
            }
            fscanf(fp_op, "%s\t%s\n", mnemonic, code); // read next mnemonic and code
        }
        if (strcmp(opcode, "WORD") == 0){ // if opcode is a word, add 3 to locctr
            locctr += 3;
            locdisp += 3;}
        else if (strcmp(opcode, "RESW") == 0) {// if opcode is RESW, add 3 * [operand] to locctr
            locctr += 3 * (atoi(operand));
            locdisp += 3 * (atoi(operand));
        }
        else if (strcmp(opcode, "RESB") == 0){ // if opcode is RESB, add [operand] to locctr
            locctr += atoi(operand);
            locdisp += atoi(operand);
        }
        else if (strcmp(opcode, "BYTE") == 0){ // if opcode is BYTE, find length of constant in bytes and add it to locctr
            locctr++;
            locdisp++;
        }

        /*
        else if (strcmp(opcode, "BYTE") == 0) { 
            int byteLength = 0;
            if (operand[0] == 'C') {
                // For character constants like C'HELLO'
                byteLength = strlen(operand) - 3;  // Subtract 3 for C' and '
            } 
            else if (operand[0] == 'X') {
                // For hexadecimal constants like X'F1A3'
                byteLength = (strlen(operand) - 3) / 2;  // Subtract 3 for X' and ', divide by 2 for hex pairs
            }
            locctr += byteLength; 
            locdisp += byteLength;
        }

*/
        fprintf(fp_ou, "%s\t%s\t%s\t\n", label, opcode, operand);
        printf("%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(fp_in, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(fp_ou, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand); // write locctr, label, opcode, and operand for END to output.txt
    printf("\t%s\t%s\t%s\n", label, opcode, operand); // to standard output
    length = locctr - start;
    printf("\nStarting address: %d\n", start);
    fprintf(fp_len, "%d", length); // program length
    printf("\nProgram length: %X\n\n", length); // print program length
    fclose(fp_len); // close file pointer to length.txt
    fclose(fp_in); // close file pointer to input.txt
    fclose(fp_op); // close file pointer to optab.txt
    fclose(fp_sy); // close file pointer to symtab.txt
    fclose(fp_ou); // close file pointer to output.txt
}
