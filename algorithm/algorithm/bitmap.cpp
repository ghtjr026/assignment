#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

ifstream finp("bitmap.inp");
ofstream fout("bitmap.out");

vector<char> result;
char bitmap[201][201];
char D_bitmap[201][201];
char D_bit[40001];
int D_bit_start = -1;

char isSame(int x, int y, int row, int col) {

	char type = bitmap[y][x];

	for (int i = y; i < col; i++) {
		for (int j = x; j < row; j++) {
			if (type != bitmap[i][j]) {
				type = '2';
				return type;
			}
		}
	}

	return type;
}

void BtoD(int x, int y, int row, int col) { //x,y 는 좌료 row, col map의 크기

	char check = isSame(x, y, row, col);

	if (check == '2') {
		
		result.push_back('D');

		int row_mid, col_mid; //크기 좌표 지정
		if ((row - x) % 2 == 0) {
			row_mid = x + (row - x) / 2;
		}
		else {
			row_mid = x + 1 + (row - x) / 2;
		}
		if ((col - y) % 2 == 0) {
			col_mid = y + (col - y) / 2;
		}
		else {
			col_mid = y + 1 + (col - y) / 2;
		}

		int n2 = 0, n3 = 0;
		BtoD(x, y, row_mid, col_mid);
		if (row - x != 1) {
			BtoD(row_mid, y, row, col_mid);
			n2 = 1;
		}
		if (col - y != 1) {
			BtoD(x, col_mid, row_mid, col);
			n3 = 1;
		}
		if (n2 == 1 && n3 == 1) {
			BtoD(row_mid, col_mid, row, col);
		}
	}
	else if (check == '1') {
		result.push_back('1');
	}
	else {
		result.push_back('0');
	}


}

void drawing(int x, int y, int row, int col, char num) {

	for (int i = y; i < col; i++) {
		for (int j = x; j < row; j++) {
			D_bitmap[i][j] = num;
		}
	}

}

void DtoB(int x, int y, int row, int col) {

	D_bit_start++;

	if (D_bit[D_bit_start] != 'D') {
		drawing(x, y, row, col, D_bit[D_bit_start]);
	}
	else {

		int row_mid, col_mid;
		if ((row - x) % 2 == 0) {
			row_mid = x + (row - x) / 2;
		}
		else {
			row_mid = x + 1 + (row - x) / 2;
		}
		if ((col - y) % 2 == 0) {
			col_mid = y + (col - y) / 2;
		}
		else {
			col_mid = y + 1 + (col - y) / 2;
		}

		int n2 = 0, n3 = 0;
		DtoB(x, y, row_mid, col_mid);
		if (row - x != 1) {
			DtoB(row_mid, y, row, col_mid);
			n2 = 1;
		}
		if (col - y != 1) {
			DtoB(x, col_mid, row_mid, col);
			n3 = 1;
		}
		if (n2 == 1 && n3 == 1) {
			DtoB(row_mid, col_mid, row, col);
		}

	}
}

int main() {

	while (1) {

		char type;
		int x, y;
		
		finp >> type;
		if (type == '#') {
			break;
		}
		else if (type == 'B') {

			for (int i = 0; i < 201; i++) {
				memset(bitmap[i], '0', sizeof(char) * 201);
			}
			
			finp >> y >> x;
			fout << 'D' << ' ' << y << ' ' << x;
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					finp >> bitmap[i][j];
				}
			}
			
			BtoD(0, 0, x, y);
			for (int i = 0; i < result.size(); i++) {
				if (i % 50 == 0) {
					fout << '\n';
				}
				fout << result[i];

			}

			fout << '\n';

		}
		else {

			memset(D_bit, '0', sizeof(char) * 40001);
			for (int i = 0; i < 201; i++) {
				memset(D_bitmap[i], '0', sizeof(char) * 201);
			}

			finp >> y >> x;
			fout << 'B' << ' ' << y << ' ' << x << '\n';
			string Line;
			int L = 0;
			while (1){
				finp >> Line;
				for (int i = L * 50; i < L * 50 + Line.size(); i++) {
					D_bit[i] = Line[i % 50];
				}
				L++;
				if (Line.size() != 50) {
					break;
				}
			}

			D_bit_start = -1;
			DtoB(0, 0, x, y);
			int cnt = 0;
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					fout << D_bitmap[i][j];
					cnt++;
					if (cnt == 50) {
						fout << '\n';
						cnt = 0;
					}
				}
			}
			if(x*y % 50 != 0) {
				fout << '\n';
			}
		}
		result.clear();

	}

	return 0;
}