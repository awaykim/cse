/*
* Cse-sophomore 2nd Computer Archietecture (major)
* This code changes given 32-bit sequences into assembly codes
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

 //CA: DO NOT CHANGE
const char* outputFileName = "hw02_output.txt";

//CA: Please write your code
int convert(int* arr, int start, int end) {
	int arr_size = end - start + 1;
	int* slice_arr = (int*)malloc(sizeof(int*) * arr_size);
	slice_arr = 0;
	for (int i = 0; i < arr_size; i++) {
		slice_arr[i] = arr[end - i];
	}
	int sum = 0;
	for (int i = 0; i < arr_size; i++) {
		if (slice_arr[i] == 1) {
			int p = 1;
			for (int j = 0; j < arr_size - i - 1; j++) {
				p *= 2;
			}
			sum += p;
		}
	}
	return sum;
}
int main() {
	//CA: YOUR NAME with Student ID
	printf("Wonjeong Kim (2176083)\n");
	int totalcase;
	FILE* in_fp = fopen("input.txt", "r");
	FILE* fp = fopen(outputFileName, "w");
	fscanf(in_fp, "%d", &totalcase);
	for (int t = 0; t < totalcase; t++) {
		long long hex;
		int binary[100], p, i = 0;
		fscanf(in_fp, "%llx", &hex);
		while (hex > 0) {
			p = hex % 2;
			binary[i] = p;
			hex = hex / 2;
			i += 1;
		}
		if (i < 32) for (int j = i; j < 32; j++) binary[j] = 0;
		if (binary[6] == 1) {
			int rs1 = convert(binary, 15, 19, 5);
			int rs2 = convert(binary, 20, 24, 5);
			int imm1, imm2, imm3 = 0;
			int imm4 = 0;
			int sign = 1;
			if (binary[31] == 1) {
				int l = 0;
				sign = -1;
				for (int i = 8; i < 12; i++) {
					if (binary[i] == 1) {
						binary[i] = 0;
						l = 1;
						for (int j = 8; j < i; j++) binary[j] = 1;
						break;
					}
				}
				if (l == 0) {
					for (int i = 25; i < 31; i++) {
						if (binary[i] == 1) {
							binary[i] = 0;
							l = 1;
							for (int j = 25; j < i; j++) binary[j] = 1;
							for (int j = 8; j < 12; j++) binary[j] = 1;
							break;
						}
					}
					if (l == 0) {
						for (int j = 25; j < 31; j++) binary[j] = 1;
						for (int j = 8; j < 12; j++) binary[j] = 1;
						if (binary[7] == 0) {
							binary[7] = 1;
							sign = 0;
							imm4 = -4096;
						}
						else binary[7] = 0;
					}
				}
				for (int i = 31; i > 6; i--) binary[i] = binary[i] ^ 1;
			}
			imm1 = convert(binary, 25, 30, 6) << 5;
			imm2 = convert(binary, 8, 11, 4) << 1;
			if (binary[7] == 1) imm3 = 2048;
			int imm = (sign) * (imm1 + imm2 + imm3) + imm4;
			fprintf(fp, "beq x%d,x%d,%d\n", rs1, rs2, imm);
		}
		else if (binary[5] == 0) {
			int rd = convert(binary, 7, 11, 5);
			int rs1 = convert(binary, 15, 19, 5);
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
			int imm = (sign)*convert(binary, 20, 31, 12);
			if (binary[4] == 1) fprintf(fp, "addi x%d,x%d,%d\n", rd, rs1, imm);
			else fprintf(fp, "lw x%d,%d(x%d)\n", rd, imm, rs1);
		}
		else if (binary[4] == 0) {
			int rs2 = convert(binary, 20, 24, 5);
			int rs1 = convert(binary, 15, 19, 5);
			int imm1, imm2, imm;
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
			imm = (sign) * (imm1 + imm2);
			fprintf(fp, "sw x%d,%d(x%d)\n", rs2, imm, rs1);
		}
		else {
			int rs2 = convert(binary, 20, 24, 5);
			int rs1 = convert(binary, 15, 19, 5);
			int rd = convert(binary, 7, 11, 5);
			if (binary[30] == 1) fprintf(fp, "sub ");
			else fprintf(fp, "add ");
			fprintf(fp, "x%d,x%d,x%d\n", rd, rs1, rs2);
		}
	}
	fclose(in_fp);
	fclose(fp);
	return true;
}