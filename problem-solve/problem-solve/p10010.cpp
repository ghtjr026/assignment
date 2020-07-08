#include <fstream>
#include <string>
using namespace std;

ifstream finp("p10010.inp");
ofstream fout("p10010.out");

int row, col, word;
char board[51][51];
int dir[8][2] = { {-1, 0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
string name;

bool Range(int i, int j) {
	if (i < row && i >= 0 && j < col && j >= 0) {
		return true;
	}
	else {
		return false;
	}
}

void findstr(int i, int j, string Name) {

	for (int k = 0; k < 8; k++) {
		int ni = i;
		int nj = j;
		bool check = false;
		for (int l = 0; l < Name.length(); l++) {
			
			if (Range(ni, nj)) {
				if (board[ni][nj] == Name[l]) {
					ni += dir[k][0];
					nj += dir[k][1];
					check = true;
				}
				else {
					check = false;
					break;
				}
			}
			else {
				check = false;
				break;
			}
		}
		if (check == true) {
			fout << i + 1 << ' ' << j + 1 << '\n';
			break;
		}

	}

}

int main() {

	int testcase;
	finp >> testcase;
	while (testcase--) {

		char letter;
		finp >> row >> col;

		for (int i = 0; i < row; i++) {
			
			for (int j = 0; j < col; j++) {
				
				finp >> letter;
				if (letter < 'a') letter += 32;
				board[i][j] = letter;

			}
		
		}

		finp >> word;
		for (int i = 0; i < word; i++) {
			finp >> name;
			
			for (int j = 0; j < name.length(); j++) {
				if (name[j] < 'a') {
					name[j] += 32;
				}
			}

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (board[i][j] == name[0]) {
						findstr(i, j, name);
					}
				}
			}

		}

		fout << '\n';

	}

	return 0;
}




