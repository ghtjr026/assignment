#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

ifstream finp("inv.inp");
ofstream fout("inv.out");

vector<int> arr;
long long int result;

void merge(int low, int mid, int high) {

	int i, j, k;
	int* U = (int*)malloc(sizeof(int) * (high + 1));
	i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high) {
		if (arr[i] <= arr[j]) {
			U[k] = arr[i++];
		}
		else {
			U[k] = arr[j++];
			result += (mid - i + 1);
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++, k++) {
			U[k] = arr[j];
		}
	}
	else {
		for (; i <= mid; i++, k++) {
			U[k] = arr[i];
		}
	}

	for (int t = low; t <= high; t++) {
		arr[t] = U[t];
	}

	free(U);

}

void mergesort(int low, int high) {

	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(low, mid);
		mergesort(mid + 1, high);
		merge(low, mid, high);
	}

}

int main() {

	int testcase;
	finp >> testcase;

	while (testcase--) {

		int size;
		finp >> size;
		arr.resize(size);
		result = 0;

		for (int i = 0; i < size; i++) {
			finp >> arr[i];
		}

		mergesort(0, size - 1);

		fout << result << '\n';

	}

	return 0;
}