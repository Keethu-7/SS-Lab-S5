#include <stdio.h>
#include <string.h>

void main() {
    FILE *fp_ou, *fp_op, *fp_len, *fp_sy, *fp_opc, *fp_obj;
    int i, j, len, reclen = 0, loc;
    char symnam[5], code[5], start[10], label[20], opcode[20], operand[20], symloc[10];
    char mnemonic[10], a[20], b[20], count[20];

    fp_ou = fopen("output.txt", "r");
    fp_len = fopen("length.txt", "r");
    fp_op = fopen("optab.txt", "r");
    fp_sy = fopen("symtab.txt", "r");
    fp_opc = fopen("optab.txt", "r");
    fp_obj = fopen("object_program.txt", "w");  // File to store object program

    if (!fp_ou || !fp_len || !fp_op || !fp_sy || !fp_opc || !fp_obj) {
        printf("Error opening files.\n");
        return;
    }

    printf("\nPass 2 of a two-pass assembler:\n\n");
    printf("Header rec:\n");

    // Read the first line from the source file
    fscanf(fp_ou, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        strcpy(start, operand);
        fscanf(fp_len, "%d", &len);  // Get program length
    }

    // Write the header record to both console and object file
    printf("H^%s^00%s^0000%X\n", label, start, len);
    fprintf(fp_obj, "H^%s^00%s^0000%X\n", label, start, len);

    printf("Text rec:\n");
    printf("T^00%s^", start);
    fprintf(fp_obj, "T^00%s^", start);  // Write start of text record to object file
    reclen += 6;

    // Process each line of the source file
    fscanf(fp_ou, "%d %s %s %s", &loc, label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        fscanf(fp_op, "%s %s", mnemonic, code);
        while (!feof(fp_op)) {
            if (strcmp(opcode, mnemonic) == 0) {
                fscanf(fp_sy, "%s %s", symnam, symloc);
                while (!feof(fp_sy)) {
                    if (strcmp(operand, symnam) == 0) {
                        reclen += 6;
                        printf("%s%s^", code, symloc);
                        fprintf(fp_obj, "%s%s^", code, symloc);  // Write opcode and address directly to object file
                        break;
                    } else {
                        fscanf(fp_sy, "%s %s", symnam, symloc);
                    }
                }
                break;
            } else {
                fscanf(fp_op, "%s %s", mnemonic, code);
            }
        }

        // Process WORD and BYTE directives
        if (strcmp(opcode, "WORD") == 0 || strcmp(opcode, "BYTE") == 0) {
            if (strcmp(opcode, "WORD") == 0) {
                printf("00000%s^", operand);
                fprintf(fp_obj, "00000%s^", operand);  // Write WORD directly to object file
                reclen += 6;
            } else {
                for (i = 0, j = 2; j < (strlen(operand) - 1); i++, j++) {
                    count[i] = operand[j];
                }
                count[i] = '\0';
                while (!feof(fp_opc)) {
                    fscanf(fp_opc, "%s %s", a, b);
                    if (strcmp(count, a) == 0) {
                        printf("0000%s", b);
                        fprintf(fp_obj, "0000%s", b);  // Write BYTE directly to object file
                        reclen += 6;
                        break;
                    }
                }
            }
        }

        fscanf(fp_ou, "%d %s %s %s", &loc, label, opcode, operand);
        fseek(fp_op, 0, SEEK_SET);  // Reset optab pointer
        fseek(fp_sy, 0, SEEK_SET);  // Reset symtab pointer
    }

    // Complete the text record by adding the record length
    printf("%X^", reclen / 2);
    fprintf(fp_obj, "%X^", reclen / 2);  // Write record length to object file

    // Write the end record to both console and object file
    printf("\nEnd rec:\n");
    printf("E^00%s\n", start);
    fprintf(fp_obj, "\nE^00%s\n", start);

    // Close all open files
    fclose(fp_ou);
    fclose(fp_op);
    fclose(fp_sy);
    fclose(fp_len);
    fclose(fp_obj);

    printf("Object program written to object_program.txt successfully.\n");
}
