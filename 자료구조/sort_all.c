#include <stdio.h>

#define MAX_SIZE 100
int sorted[MAX_SIZE];

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) { //분할한 왼쪽 정렬과 오른쪽 정렬이 쭉쭉 옆으로 가는 화살표들
		if (list[i] <= list[j])
			sorted[k++] = list[i++]; //오른쪽 정렬보다 왼쪽 정렬된 레코드가 작으면 왼쪽것을 sorted에 넣음
		else sorted[k++] = list[j++];
	}
	if (i > mid) for (l = j; l <= right; l++)
		sorted[k++] = list[l];
	else for (l = i; l <= mid; l++)
		sorted[k++] = list[l]; //왼쪽.오른쪽 비교가 불가하면 그대로 sorted에 붙여넣기

	for (l = i; l <= right; l++)
		list[l] = sorted[l]; //sorted 배열을 다시 list에
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2; 
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int partition(int list[], int left, int right) {
	int pivot, tmp, low, high;
	low = left; high = right + 1; pivot = list[left];

	do {
		do low++;
		while (low <= high && list[low] < pivot); //pivot보다 커지면 low 높이기를 멈춤
		do high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], tmp); //pivot보다 큰 low와 작은 high의 값을 SWAP함
	} while (low < high);//low > high가 되면 종료
	SWAP(list[left], list[high], tmp);
	return high;
}

void quick(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick(list, left, q - 1);
		quick(list, q, right);
	}
}

// void radix(int list[], int n) {
// 	int i, b, d, factor = 1;
// 	QueueType queue[BUCKETS];

// 	for (b = 0; b < BUCKETS; b++) {
// 		init(&queue[b]);
// 	}

// 	for (d = 0; d < DIGITS; d++) {
// 		for (i = 0; i < n; i++) {
// 			enqueue(&queue[(list[i] / factor) % 10)], list[i]);
// 		}

// 		for (b = i = 0; b < BUCKETS; b++) {
// 			while (!is_empty(&queue[b]))
// 				list[i++] = dequeue(&queue[b]);
// 			factor *= 10;
// 		}
// 	}

// }

int main() {

}