/*
* ********** Please read the instructions below carefully **********
* Your name and student ID must be printed when this project is executed
* Do not print anything other than your name and student ID (Delete printf functions used for debugging when submitting this homework)
* - If not, there will be 20% penalty
* Run make clean command before submitting your homework
* Change this project folder name to studentID_yourname (EX: 1234567_myungkukyoon)
* You must compress this project folder (not the files in this folder)
* - If not, there will be 20% penalty
* - Use ZIP compression utility (DO NOT USE TAR COMMAND)
* The name of ZIP file must be studentID_yourname.zip (EX: 1234567_myungkukyoon.zip)
* All the tests must be done in 5 seconds
* - If not, you will get 0%
*/

/*
* Input instructions
* add, sub, addi, sw, lw
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

//CA: DO NOT CHANGE
const char* inputInstFile = "input_inst.txt";
const char* inputRegFile = "input_reg.txt";
const char* inputMemFile = "input_mem.txt";
const char* outputFileName = "hw03_output.txt";

const unsigned MAX_REG_SIZE = 32;
const unsigned MAX_MEM_SIZE = 1024;

unsigned Register[MAX_REG_SIZE] = { 0 };
unsigned Memory[MAX_MEM_SIZE] = { 0 };

void print_output_to_file(FILE* fp) {
	for (unsigned i = 0; i < MAX_REG_SIZE; i++) {
		fprintf(fp, "%08x\n", Register[i]);
	}
	for (unsigned i = 0; i < MAX_MEM_SIZE; i++) {
		fprintf(fp, "%08x\n", Memory[i]);
	}
}

//CA: Please write your code

typedef struct Instruction {
	char c[10];
	int rd = 9999;
	int rs1 = 9999;
	int rs2 = 9999;
	int imm = 9999;
} instr;

int convert(int* arr, int start, int end, int n) {
	int arr_size = end - start + 1;
	int* slice_arr = (int*)malloc(sizeof(int) * arr_size);
	for (int i = 0; i < arr_size; i++) {
		slice_arr[i] = arr[end - i];
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (slice_arr[i] == 1) {
			int p = 1;
			for (int j = 0; j < n - i - 1; j++) {
				p *= 2;
			}
			sum += p;
		}
	}
	return sum;
}

instr assembly(long long n) {
	instr ins;
	int binary[100], p, i = 0;

	while (n > 0) {
		p = n % 2;
		binary[i] = p;
		n = n / 2;
		i += 1;
	}
	if (i < 32) for (int j = i; j < 32; j++) binary[j] = 0;
	if (binary[5] == 0) {
		ins.rd = convert(binary, 7, 11, 5);
		ins.rs1 = convert(binary, 15, 19, 5);
		int sign = 1;
		if (binary[31] == 1) {
			sign = -1;
			for (int i = 20; i <= 31; i++) {
				if (binary[i] == 1) {
					binary[i] = 0;
					for (int j = 20; j < i; j++) binary[j] = 1;
					break;
				}
			}
			for (int i = 31; i > 19; i--) binary[i] = binary[i] ^ 1;
		}
		ins.imm = (sign)*convert(binary, 20, 31, 12);
		if (binary[4] == 1) strcpy_s(ins.c, "addi");
		else strcpy(ins.c, "lw");
	}
	else if (binary[4] == 0) {
		ins.rs2 = convert(binary, 20, 24, 5);
		ins.rs1 = convert(binary, 15, 19, 5);
		int imm1, imm2;
		int sign = 1;
		if (binary[31] == 1) {
			int l = 0;
			sign = -1;
			for (int i = 7; i < 12; i++) {
				if (binary[i] == 1) {
					binary[i] = 0;
					l = 1;
					for (int j = 7; j < i; j++) binary[j] = 1;
					break;
				}
			}
			if (l == 0) {
				for (int i = 25; i <= 31; i++) {
					if (binary[i] == 1) {
						binary[i] = 0;
						l = 1;
						for (int j = 25; j < i; j++) binary[j] = 1;
						for (int j = 7; j < 12; j++) binary[j] = 1;
						break;
					}
				}
			}
			for (int i = 31; i > 6; i--) binary[i] = binary[i] ^ 1;
		}
		imm1 = convert(binary, 25, 31, 7) << 5;
		imm2 = convert(binary, 7, 11, 5);
		ins.imm = (sign) * (imm1 + imm2);
		strcpy(ins.c, "sw");
	}
	else {
		ins.rs2 = convert(binary, 20, 24, 5);
		ins.rs1 = convert(binary, 15, 19, 5);
		ins.rd = convert(binary, 7, 11, 5);
		if (binary[30] == 1) strcpy(ins.c, "sub");
		else strcpy(ins.c, "add");
	}
	return ins;
	
}

int main() {
	//CA: YOUR NAME with Student ID
	printf("Wonjeong Kim (2176083)\n");

	FILE* fp = fopen(outputFileName, "w");
	FILE* inst = fopen(inputInstFile, "r");
	FILE* reg = fopen(inputRegFile, "r+");
	FILE* mem = fopen(inputMemFile, "r+");
	instr line;
	

	int total;
	fscanf(inst, "%d", &total);
	printf("total: %d\n", total);
	
	for (int t = 0; t < total; t++) {

		for (int i = 0; i < MAX_REG_SIZE; i++) {
			fscanf(reg, "%x", &Register[i]);
		}
		for (int i = 0; i < MAX_MEM_SIZE; i++) {
			fscanf(mem, "%x", &Memory[i]);
		}

		long long hex;
		fscanf(inst, "%llx", &hex);
		line = assembly(hex);

		printf("%s ", line.c);
		printf("rd: %d / rs1: %d / rs2: %d/ imm: %d\n", line.rd, line.rs1, line.rs2, line.imm);
		
		if (strcmp(line.c, "lw") == 0) {
			printf("rs1: 0x%x ( %d )\n", Register[line.rs1], Register[line.rs1]);
			int dest = line.rs1 + line.imm / 4;
			if (dest < 0) {
				dest = 1024 - dest;
			}
			printf("읽은 메모리: %x ( %d )\n", Memory[dest], Memory[dest]);
			Register[line.rd] = Memory[dest];
			printf("레지스터 %d에 작성: 0x%x\n", line.rd, Register[line.rd]);
		}
		else if (strcmp(line.c, "addi") == 0) {
			printf("rs1: 0x%x ( %d )\n", Register[line.rs1], Register[line.rs1]);
			int value = Register[line.rs1] + line.imm;
			printf("rs1 %d + imm %d\n", Register[line.rs1], line.imm);
			Register[line.rd] = value;
			printf("레지스터 %d에 작성: 0x%x\n", line.rd, Register[line.rd]);
		}
		else if (strcmp(line.c, "sw") == 0) {

			printf("rs1: 0x%x ( %d )\n", Register[line.rs1], Register[line.rs1]);
			printf("rs2: 0x%x ( %d )\n", Register[line.rs2], Register[line.rs2]);
			int dest = line.rs1 + line.imm / 4;
			if (dest < 0) {
				dest = 1024 - dest;
			}
			printf("읽은 레지스터: %x ( %d )\n", Register[line.rs1], Register[line.rs1]);
			Memory[dest] = Register[line.rs2];
			printf("메모리 %d에 작성: 0x%x\n", dest, Memory[dest]);
		}
		else if (strcmp(line.c, "add") == 0) {
			printf("rs1: 0x%x ( %d )\n", Register[line.rs1], Register[line.rs1]);
			printf("rs2: 0x%x ( %d )\n", Register[line.rs2], Register[line.rs2]);
			int value = Register[line.rs1] + Register[line.rs2];
			Register[line.rd] = value;
			printf("레지스터 %d에 작성 : 0x%x\n", line.rd, Register[line.rd]);
		}
		else {
			printf("rs1: 0x%x ( %d )\n", Register[line.rs1], Register[line.rs1]);
			printf("rs2: 0x%x ( %d )\n", Register[line.rs2], Register[line.rs2]);
			int value = Register[line.rs1] - Register[line.rs2];
			Register[line.rd] = value;
			printf("레지스터 %d에 작성 : 0x%x\n", line.rd, Register[line.rd]);
		}
		
	}

	printf("-----DONE------");

	print_output_to_file(fp);



	fclose(fp);
	fclose(reg);
	fclose(inst);
	fclose(mem);
	return true;
}