/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #01
 *
 *        Version:  1.0
 *        Created:  2022-07-23
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: Wonjeong Kim
 * 	 Student ID: 2176083
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

 //CA: DO NOT CHANGE
const int MAX = 100;
const char* outputFileName = "hw01_output.txt";

//CA: DO NOT CHANGE
int matrixOutput[MAX][MAX] = { 0 };

//CA: DO NOT CHANGE
void print_output_to_file(FILE* fp, int ROW, int COL) {
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			fprintf(fp, "%d ", matrixOutput[y][x]);
		}
		fprintf(fp, "\n");
	}
}

//CA: Please write your code
int main() {
	//CA: YOUR NAME with Student ID
	printf("Wonjeong Kim (2176083)\n");

	int matrixInputA[MAX][MAX], matrixInputB[MAX][MAX];
	int totalcase, n, k, m;

	FILE* in_fp = fopen("input.txt", "r");
	FILE* fp = fopen(outputFileName, "w");
	

	fscanf(in_fp, "%d", &totalcase);
	printf("total case: %d\n\n", totalcase);

	
	for (int t = 0; t < totalcase; t++) {

		fscanf(in_fp, "%d %d %d", &n, &k, &m);
		printf("\n%d번째 행렬, n: %d k: %d m: %d\n\n", (t + 1), n, k, m);

		printf("matrix A%d\n", t + 1);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				fscanf(in_fp, "%d", &matrixInputA[i][j]);
				printf("%d ", matrixInputA[i][j]);
			}
			printf("\n");
		}

		printf("matrix B%d\n", t + 1);
	
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < m; j++) {
				fscanf(in_fp, "%d", &matrixInputB[i][j]);
				printf("%d ", matrixInputB[i][j]);
			}
			printf("\n");
		}

		printf("Outputmatrix%d\n", t + 1);
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				matrixOutput[i][j] = 0;
				for (int l = 0; l < k; l++) {
					matrixOutput[i][j] += matrixInputA[i][l] * matrixInputB[l][j];
					
				}
				printf("%d ", matrixOutput[i][j]);
			}
			printf("\n");
		}
		print_output_to_file(fp, n, m);

	}

	fclose(in_fp);
	fclose(fp);

	return true;

}




