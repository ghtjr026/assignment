#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

ifstream finp("ladder.inp");
ofstream fout("ladder.out");

typedef struct ladder {

	int x, y;
	int x1, y1;

}lad;

lad low[50][10000]; // input
int low_[50][10000]; // 세로줄 높이별 정렬
int low_cnt[50]; //세로줄별 사용된 점의 개수
int result[50];

void change_idx(int x, int high, int x1, int high1, int j) {

	for (int i = 0; i < low_cnt[x]; i++) {
		if (low_[x][i] == high) {
			low[x][j].y = i;
		}
	}

	for (int i = 0; i < low_cnt[x1]; i++) {
		if (low_[x1][i] == high1) {
			low[x][j].y1 = i;
		}
	}

}

void merge(int low_, int mid, int high, int i) {

	int t, j, k;
	lad U[10000];
	t = low_, j = mid + 1, k = low_;
	while (t <= mid && j <= high) {
		if (low[i][t].y <= low[i][j].y) {
			U[k].x = low[i][t].x;
			U[k].y = low[i][t].y;
			U[k].x1 = low[i][t].x1;
			U[k].y1 = low[i][t].y1;
			t++;
		}
		else {
			U[k].x = low[i][j].x;
			U[k].y = low[i][j].y;
			U[k].x1 = low[i][j].x1;
			U[k].y1 = low[i][j].y1;
			j++;
		}
		k++;
	}
	if (t > mid) {
		for (; j <= high; j++, k++) {
			U[k].x = low[i][j].x;
			U[k].y = low[i][j].y;
			U[k].x1 = low[i][j].x1;
			U[k].y1 = low[i][j].y1;
		}
	}
	else {
		for (; t <= mid; t++, k++) {
			U[k].x = low[i][t].x;
			U[k].y = low[i][t].y;
			U[k].x1 = low[i][t].x1;
			U[k].y1 = low[i][t].y1;
		}
	}
	for (int f = low_; f <= high; f++) {
		low[i][f].x = U[f].x;
		low[i][f].y = U[f].y;
		low[i][f].x1 = U[f].x1;
		low[i][f].y1 = U[f].y1;
	}

}

void mergesort(int low, int high, int i) {

	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(low, mid, i);
		mergesort(mid + 1, high, i);
		merge(low, mid, high, i);
	}

}

int find_result(int sel, int high1) {

	int temp = 0;
	int high = high1;

	if (high == low_cnt[sel]) {
		temp = low[sel][high - 1].x;
		return temp;
	}

	find_result(low[sel][high].x1, (low[sel][high].y1)+1);

}

int main() {

	int ladder_n;
	finp >> ladder_n;

	//input
	int x, high, x1, high1;

	while (1) {

		finp >> x >> high >> x1 >> high1;
		if (x == 0 && high == 0 && x1 == 0 && high1 == 0) break;

		low[x][low_cnt[x]].x = x;
		low[x][low_cnt[x]].y = high;
		low[x][low_cnt[x]].x1 = x1;
		low[x][low_cnt[x]].y1 = high1;
		low_cnt[x]++;
		low[x1][low_cnt[x1]].x = x1;
		low[x1][low_cnt[x1]].y = high1;
		low[x1][low_cnt[x1]].x1 = x;
		low[x1][low_cnt[x1]].y1 = high;
		low_cnt[x1]++;

	}

	//세로줄 높이별 정렬
	for (int i = 0; i < ladder_n; i++) { 
		for (int j = 0; j < low_cnt[i]; j++) {
			low_[i][j] = low[i][j].y;
		}
		sort(low_[i], low_[i] + low_cnt[i]);
	}

	//인덱스화
	for (int i = 0; i < ladder_n; i++) {
		for (int j = 0; j < low_cnt[i]; j++) {
			change_idx(low[i][j].x, low[i][j].y, low[i][j].x1, low[i][j].y1, j);
		}
	}

	//세로줄별 정렬시키기
	for (int i = 0; i < ladder_n; i++) {
		mergesort(0, low_cnt[i] - 1, i);
	}

	//find result
	//int temp;
	for (int i = 0; i < ladder_n; i++) {
		result[i] = find_result(i, 0);
		//result[temp] = i;
	}

	for (int i = 0; i < ladder_n; i++) {
		fout << result[i] << ' ';
	}

	return 0;
}