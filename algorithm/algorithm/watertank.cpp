#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, h; // 세로 가로 높이
int water[1002][1002];
int row[1002][1002];
int col[1002][1002];
bool visited[1002][1002];

ifstream finp("watertank.inp");
ofstream fout("watertank.out");

void set_water() {

	for (int i = 0; i < m; i++) {
		if (row[0][i] != -1) {
			if(water[0][i] >= row[0][i]) water[0][i] = row[0][i];
		}
		if (row[n][i] != -1) {
			if (water[n - 1][i] >= row[n][i]) water[n - 1][i] = row[n][i];
		}
	}

	for (int i = 0; i < n; i++) {
		if (col[i][0] != -1) {
			if (water[i][0] >= col[i][0]) water[i][0] = col[i][0];
		}
		if (col[i][m] != -1) {
			if (water[i][m - 1] >= col[i][m]) water[i][m - 1] = col[i][m];
		}
	}

}

bool Range_Row(int i) {

	if (i > 0 && i < n) {
		return true;
	}
	else {
		return false;
	}

}

bool Range_Col(int j) {

	if (j > 0 && j < m) {
		return true;
	}
	else {
		return false;
	}

}

//direction 0: 위에서 왓다 1: 왼쪽에서 왓다 2: 오른쪽에서 왓다 3: 밑에서 왓다

void change_water(int hole, int direction, int i, int j) {

	int change = hole;
	water[i][j] = min(water[i][j], change);
	visited[i][j] = true;
	//위쪽 구멍이 있을경우
	if (Range_Row(i)) {
		if (row[i][j] != -1 && direction != 0 && visited[i-1][j] == false) {
			change = max(water[i][j], row[i][j]);
			
			change_water(change, 3, i - 1, j);

		}
	}
	//왼쪽 구멍이 있을경우
	if (Range_Col(j)) {
		if (col[i][j] != -1 && direction != 1 && visited[i][j - 1] == false) {
			change = max(water[i][j], col[i][j]);
			change_water(change, 2, i, j - 1);
		}
	}
	//오른쪽 구멍이 있을경우
	if (Range_Col(j + 1)) {
		if (col[i][j + 1] != -1 && direction != 2 && visited[i][j + 1] == false) {
			change = max(water[i][j], col[i][j + 1]);
			change_water(change, 1, i, j + 1);
		}
	}
	//아래쪽 구멍이 있을경우
	if (Range_Row(i + 1)) {
		if (row[i + 1][j] != -1 && direction != 3 && visited[i + 1][j] == false) {
			change = max(water[i][j], row[i + 1][j]);
			change_water(change, 0, i + 1, j);
		}
	}
	visited[i][j] = false;
}

void solve() {

	for (int i = 0; i < m; i++) {
		if (row[0][i] != -1) {
			change_water(row[0][i], 0, 0, i);
		}
		if (row[n][i] != -1) {
			change_water(row[n][i], 3, n - 1, i);
		}
	}

	for (int i = 0; i < n; i++) {
		if (col[i][0] != -1) {
			change_water(col[i][0], 1, i, 0);
		}
		if (col[i][m] != -1) {
			change_water(col[i][m], 2, i, m - 1);
		}
	}

}

int main() {

	int testcase;
	int result;
	finp >> testcase;
	while (testcase--) {

		result = 0;
		finp >> n >> m >> h;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				water[i][j] = h;
			}
		}

		for (int j = 0; j < n + 1; j++) {
			for (int i = 0; i < m; i++) {
				finp >> row[j][i];
			}
		}

		for (int j = 0; j < n; j++) {
			for (int i = 0; i < m + 1; i++) {
				finp >> col[j][i];
			}
		}

		set_water();
		solve();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				result += water[i][j];
			}
		}
		fout << result << '\n';

		for (int i = 0; i < 1002; i++) {
			for (int j = 0; j < 1002; j++) {
				row[i][j] = 0;
				col[i][j] = 0;
				water[i][j] = 0;
				visited[i][j] = false;
			}
		}

	}
	
	finp.close();
	fout.close();

	return 0;
}