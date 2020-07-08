#include <fstream>
#include <algorithm>
using namespace std;

ifstream finp("go.inp");
ofstream fout("go.out");

char board[20][20];
int visit[20][20];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int cnt, B_cnt, W_cnt, n;
bool B, W;

void DFS(int row, int col) {

	cnt++;
	visit[row][col] = 1;
	for (int i = 0; i < 4; i++) {

		int y = row + dy[i];
		int x = col + dx[i];

		if (y > -1 && x > -1 && y < n && x < n) {
			if (board[y][x] == 'B') {
				B = true;
			}
			else if (board[y][x] == 'W') {
				W = true;
			}
			else if (board[y][x] == '.') {
				if (visit[y][x] != 1) {
					DFS(y,x);
				}
			}
		}

	}
	
}

void add() {

	if (B == true && W == false) {
		B_cnt += cnt;
	}
	else if (B == false && W == true) {
		W_cnt += cnt;
	}
	cnt = 0;
	B = false, W = false;

}

int main() {

	finp >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			finp >> board[i][j];
			if (board[i][j] == 'B' || board[i][j] == 'W') {
				visit[i][j] = 1;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visit[i][j] != 1) {
				DFS(i, j);
				add();
			}
		}
	}

	fout << B_cnt << ' ' << W_cnt;

	finp.close();
	fout.close();
	return 0;
}