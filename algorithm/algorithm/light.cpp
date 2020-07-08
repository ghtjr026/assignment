#include <fstream>
#include <algorithm>
#include <vector>
#define MIN 9999999
using namespace std;

ifstream finp("light.inp");
ofstream fout("light.out");

typedef struct light {

	int first, second;

}light;

int n, k;
light lamp[100001], section[1001];
light B;

bool comp(light &A, light &B) {
	return A.second < B.second;
}

bool comp_sec(const light &A,const light &B) {
	return A.second < B.second;
}

void solution() {

	int cnt, right, Min;

	for (int i = 0; i < k; i++) {

		int index = -1;
		B.first = 0;
		int right = section[i].second;
		bool check_light = false, check = false;
		int cnt = 0;

		while (true) {

			Min = MIN;
			B.second = right;
			int temp = index;
			index = lower_bound(lamp, lamp + n, B, comp_sec) - lamp;

			if (temp == index) {
				check = true;
				break;
			}

			for (int j = index; j < n; j++) {
				if (lamp[j].first < section[i].second) {
					if (lamp[j].first <= section[i].first) {
						check_light = true;
						break;
					}
					if (Min > lamp[j].first) {
						Min = lamp[j].first;
						right = Min;
					}
				}
				else if (lamp[j].first > section[i].second) {
					break;
				}
			}
			cnt++;
			if (check_light || check) {
				break;
			}

		}
		if (check) {
			fout << -1 << '\n';
		}
		else {
			fout << cnt << '\n';
		}
		
	}
}

int main() {

	finp >> n;
	for (int i = 0; i < n; i++) {
		finp >> lamp[i].first >> lamp[i].second;
	}
	sort(lamp, lamp + n, comp);
	finp >> k;
	for (int i = 0; i < k; i++) {
		finp >> section[i].first >> section[i].second;
	}
	solution();

	finp.close();
	fout.close();
	return 0;
}