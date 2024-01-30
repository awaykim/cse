/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #04
 *
 *        Version:  1.0
 *        Created:  2022-09-17
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: Wonjeong Kim
 * 	   Student ID: 2176083
 *   Organization:  Ewha Womans University
 *
 * =====================================================================================
 */

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

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

 //CA: DO NOT CHANGE
const char* outputFileName = "4_99txt";

unsigned long long cacheHit;
unsigned long long cacheMiss;

void init() {
	cacheHit = 0;
	cacheMiss = 0;
}

void ratio(FILE* fp) {
	unsigned long long total = cacheHit + cacheMiss;
	fprintf(fp, "Hit: %3.2f\n", (float)cacheHit / total * 100);
	fprintf(fp, "Miss: %3.2f\n", (float)cacheMiss / total * 100);
}

//CA: Please write your code

int convert(int* arr, int start, int end) {
	int arr_size = end - start + 1;
	int* slice_arr = (int*)malloc(sizeof(int) * arr_size);
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
	//CA: YOUR NAME with Student 	
	printf("\n");

	FILE* fp = fopen(outputFileName, "w");
	FILE* in_fp = fopen("4.txt", "r");
	
	int testcase = 0;
	fscanf(in_fp, "%d", &testcase);
	printf("testcase: %d\n", testcase);

	for (int t = 0; t < testcase; t++) {
		printf("====%d번째 케이스====\n", t + 1);
		init();
		int blocksNum = 0, blockSize = 0, adNum = 0;
		int store[1000]{};
		int valid[1000]{};

		for (int i = 0; i < 1000; i++) valid[i] = 0;
		

		fscanf(in_fp, "%d", &blocksNum);
		fscanf(in_fp, "%d", &blockSize);
		fscanf(in_fp, "%d", &adNum);

		int cacheSize = log2(blocksNum);
		int blockSizeBit = blockSize * 8;

		printf("Blocks: %d (%d bit)\n", blocksNum, cacheSize);
		printf("Block Size: %d Byte (%d bit)\n", blockSize, blockSizeBit);
		printf("Address 개수: %d\n", adNum);

		int offset = log2(blockSize);
		printf("offset: %d bit\n", offset);

		for (int a = 0; a < adNum; a++) {
			int binary[10000]{};
			int p = 0, i = 0;
			long long hex = 0;
			int tag = 0;
		
			fscanf(in_fp, "%llx", &hex);
			//printf("[16진수 %llx 10진수 %d]\n", hex, hex);

			while (hex > 0) {
				p = hex % 2;
				binary[i] = p;
				hex = hex / 2;
				i += 1;
			}

			if (i < blockSizeBit) for (int j = i; j < blockSizeBit; j++) binary[j] = 0;
			

			/*printf("[2진수 ");
			for (int k = blockSizeBit - 1; k >= 0; k--)
				printf("%d", binary[k]);
			printf("]\n");*/
			
			/*int index = convert(binary, offset, cacheSize + offset - 1);
			tag = convert(binary, cacheSize + offset, blockSizeBit - 1);*/

			int base = convert(binary, offset, blockSizeBit - 1);
			int index = base % blocksNum;
			tag = convert(binary, cacheSize + offset, blockSizeBit - 1);

			/*printf("index: ((");
			for (int k = cacheSize + offset - 1; k >= offset; k--)
				printf("%d", binary[k]);
			printf(")) [10진수: %d]\n", index);

			printf("tag: ((");
			for (int k = blockSizeBit - 1; k >= cacheSize + offset; k--)
				printf("%d", binary[k]);
			printf(")) [10진수: %d]\n", tag); */

			if (valid[index] == 0) {
				//printf("<<Miss>> 값 없음\n");
				store[index] = tag;
				cacheMiss += 1;
				valid[index] = 1;
			}
			else {
				//printf("tag: %d  new tag: %d\n", store[index], tag);
				if (store[index] == tag) {
					//printf("!!<<HIT>>!!\n");
					cacheHit += 1;
				}
				else {
					//printf("<<Miss>>값 틀림\n");
					store[index] = tag;
					cacheMiss += 1;
				}

			}

			
			//printf("누적 Hit: %d \n", cacheHit);
			//printf("누적 Miss: %d\n", cacheMiss);



		}
		int total = cacheHit + cacheMiss;
		printf("Hit: %3.2f\n", (float)cacheHit / total * 100);
		printf("Miss: %3.2f\n", (float)cacheMiss / total * 100);
		printf("\n");

		ratio(fp);
	}


	fclose(in_fp);
	fclose(fp);
	return 1;
}
