#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef struct Paper {

	int x, y;
	int x1, y1;

}Paper;

Paper paper[2000];
Paper oldest_paper[2000];
int board[8000][8000];
int x_sort[8000], y_sort[8000];
int oldest_x[8000], oldest_y[8000];
int area[2000];

ifstream finp("paper.inp");
ofstream fout("paper.out");

void Sort(int testcase) {

	oldest_x[0] = x_sort[0];
	oldest_y[0] = y_sort[0];
	int x_cnt = 1, y_cnt = 1;

	for (int i = 1; i < testcase * 2; i++) {
		
		int j;
		for (j = 0; j < i; j++) {

			if (x_sort[i] == oldest_x[j]) {
				break;
			}

		}
		if (j == i) {
			oldest_x[x_cnt] = x_sort[i];
			x_cnt++;
		}

		for (j = 0; j < i; j++) {
			if (y_sort[i] == oldest_y[j]) {
				break;
			}
		}
		if (j == i) {
			oldest_y[y_cnt] = y_sort[i];
			y_cnt++;
		}
	}

}

void set_oldest_paper(int testcase) {

	for (int i = 0; i < testcase; i++) {
		for (int j = 0;; j++) {
			if (oldest_x[j] == -1) break;
			if (oldest_x[j] == paper[i].x) {
				oldest_paper[i].x = j;
			}
			if (oldest_x[j] == paper[i].x1) {
				oldest_paper[i].x1 = j;
			}
		}
		for (int j = 0;; j++) {
			if (oldest_y[j] == -1) break;
			if (oldest_y[j] == paper[i].y) {
				oldest_paper[i].y = j;
			}
			if (oldest_y[j] == paper[i].y1) {
				oldest_paper[i].y1 = j;
			}
		}
	}

}

void drawing(int testcase) {

	for (int i = 0; i < testcase; i++) {
		for (int j = oldest_paper[i].y; j < oldest_paper[i].y1; j++) {
			for (int k = oldest_paper[i].x; k < oldest_paper[i].x1; k++) {
				board[j][k] = i + 1;
			}
		}
	}

}

void checking(int testcase) {

	int hide = 0, half = 0, all = 0;
	
	for (int i = 0; i < testcase; i++) {
		int visable = 0, invisable = 0;
		for (int j = oldest_paper[i].y; j < oldest_paper[i].y1; j++) {
			for (int k = oldest_paper[i].x; k < oldest_paper[i].x1; k++) {
				if (board[j][k] == i + 1) {
					visable++;
				}
				else {
					invisable++;
				}
			}
		}

		if (invisable == 0) {
			all++;
		}
		else if (visable == 0) {
			hide++;
		}
		else {
			half++;
		}
	}

	fout << hide << ' ' << half << ' ' << all;

}

int main() {

	int testcase;
	finp >> testcase;

	int x, y, x1, y1;

	memset(oldest_x, -1, sizeof(oldest_x));
	memset(oldest_y, -1, sizeof(oldest_y));

	for (int i = 0; i < testcase; i++) {

		finp >> x >> y >> x1 >> y1;
		paper[i].x = x;
		paper[i].y = y;
		paper[i].x1 = x + x1;
		paper[i].y1 = y + y1;

	}

	for (int i = 0, j = 0; i < testcase; i++, j += 2) {

		x_sort[j] = paper[i].x;
		x_sort[j + 1] = paper[i].x1;
		y_sort[j] = paper[i].y;
		y_sort[j + 1] = paper[i].y1;

	}

	sort(x_sort, x_sort + (testcase * 2));
	sort(y_sort, y_sort + (testcase * 2));
	Sort(testcase);
	set_oldest_paper(testcase);
	drawing(testcase);
	checking(testcase);


	return 0;
}