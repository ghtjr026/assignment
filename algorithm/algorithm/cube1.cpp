#include <fstream>
#include <string>
#include <vector>
using namespace std;

string turn_left(string com_cube) {

	char temp;

	temp = com_cube[1];
	com_cube[1] = com_cube[3];
	com_cube[3] = com_cube[4];
	com_cube[4] = com_cube[2];
	com_cube[2] = temp;

	return com_cube;

}

string set_top_roll(string com_cube) {

	char temp;

	temp = com_cube[0];
	com_cube[0] = com_cube[1];
	com_cube[1] = com_cube[5];
	com_cube[5] = com_cube[4];
	com_cube[4] = temp;

	return com_cube;

}

string set_top_lay(string com_cube) {

	char temp;

	temp = com_cube[0];
	com_cube[0] = com_cube[3];
	com_cube[3] = com_cube[5];
	com_cube[5] = com_cube[2];
	com_cube[2] = temp;

	return com_cube;
}



int main() {

	ifstream finp("cube.inp");
	ofstream fout("cube.out");

	string cubes, cube, com_cube;

	while (1) {

		getline(finp,cubes);
		int count = 1;

		for (int i = 1; i < cubes.size(); i++) {
			if (cubes[0] == cubes[i]) {
				count++;
			}
		}
		if (count == 12) {
			fout << "TRUE";
			break;
		}
		cube = cubes.substr(0, 6);
		com_cube = cubes.substr(6);

		int result = 0;
		

		for (int i = 1; i < 7; i++) {
			for (int j = 0; j < 4; j++) {
				int cnt = 0;
				for (int k = 0; k < 6; k++) {
					if (cube[k] == com_cube[k]) {
						cnt++;
					}
					else {
						break;
					}
				}
				if (cnt == 6) {
					result = 1;
				}
				com_cube = turn_left(com_cube);
			}
			if (i % 2 == 1) {
				com_cube = set_top_roll(com_cube);
			}
			else if (i % 2 == 0) {
				com_cube = set_top_lay(com_cube);
			}
			if (result == 1) {
				break;
			}
		}
		if (result == 0) {
			fout << "FALSE" << '\n';
		}
		else {
			fout << "TRUE" << '\n';
		}

		

	}

	return 0;
}