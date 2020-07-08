#include <fstream>
#include <algorithm>
using namespace std;

ifstream finp("final4.inp");
ofstream fout("final4.out");

typedef struct point {

	long long x, y;

}point;

unsigned long long grid[1001][1001];

void solve(point pivot, point &goal, bool flag) {
	
	if (flag) {
		for (int k = 1; k <= pivot.x; k++) {

			for (int l = 1; l <= pivot.y; l++) {
				grid[k][l] = grid[k - 1][l] + grid[k][l - 1] % 1000000007;
			}

		}
	}

	//경유지 가로 세로를 같은 값으로 변경
	for (int i = pivot.x; i <= goal.x; i++) {
		grid[i][pivot.y] = grid[pivot.x][pivot.y] % 1000000007;
	}
	for (int j = pivot.y; j <= goal.y; j++) {
		grid[pivot.x][j] = grid[pivot.x][pivot.y] % 1000000007;
	}

	for (int i = pivot.x + 1; i <= goal.x; i++) {

		for (int j = pivot.y + 1; j <= goal.y; j++) {

			grid[i][j] = grid[i - 1][j] + grid[i][j - 1] % 1000000007;

		}

	}
}

void init() {
	
	for (int r = 0; r < 501; r++) {
		for (int e = 0; e < 501; e++) {
			grid[r][e] = 1;
		}
	}

}

int main() {

	int t;
	finp >> t;
	while (t--) {

		init();
		point a, b, goal;

		finp >> goal.x >> goal.y >> a.x >> a.y >> b.x >> b.y;

		unsigned long long result = 0;

		//경유지가 같을 때
		if (a.x == b.x && a.y == b.y) {
			solve(a, goal, true);
			result += grid[goal.x][goal.y] % 1000000007;

			fout << result % 1000000007 << '\n';
		}
		//한점만 경유 가능
		else if ((a.x < b.x && a.y > b.y) || (a.x > b.x && a.y < b.y)) {

			solve(a, goal, true);
			result += grid[goal.x][goal.y] % 1000000007;
			init();
			solve(b, goal, true);
			result += grid[goal.x][goal.y] % 1000000007;

			fout << result % 1000000007 << '\n';
		}
		//두 점 다 경유 가능
		else {
			solve(a, goal, true);
			result += grid[goal.x][goal.y] % 1000000007;
			init();
			solve(b, goal, true);
			result += grid[goal.x][goal.y] % 1000000007;

			init();
			if (a.x <= b.x && a.y < b.y) {
				solve(a, b, true);
				solve(b, goal, false);
				result -= grid[goal.x][goal.y] % 1000000007;
			}
			else {
				solve(b, a, true);
				solve(a, goal, false);
				result -= grid[goal.x][goal.y] % 1000000007;
			}

			fout << result % 1000000007 << '\n';
		}

		

	}

	return 0;
}