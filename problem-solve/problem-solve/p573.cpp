#include <fstream>
using namespace std;

ifstream finp("p573.inp");
ofstream fout("p573.out");

int main() {

	int h, u, d, f;
	while (1) {

		finp >> h >> u >> d >> f;
		if (h == 0) break;
		h *= 100;
		u *= 100;
		d *= 100;

		int dec = u * f * 0.01;
		int height = 0;
		int day = 1;
		bool result = true;
		while (1) {
			
			//climb
			height += u;
			if (height > h) {
				result = true;
				break;
			}
			//descend
			height -= d;
			if (height <= 0) {
				result = false;
				break;
			}

			u -= dec;
			if (u < 0) {
				u = 0;
			}
			day++;

		}

		if (result) {
			fout << "success on day " << day << '\n';
		}
		else {
			fout << "failure on day " << day << '\n';
		}

	}

	return 0;
}