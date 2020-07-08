#include <fstream>
using namespace std;

ifstream finp("final6.inp");
ofstream fout("final6.out");

typedef long long ll;

ll num[3];

ll Gcd(ll a, ll b) {

	if (b == 0) return a;
	return Gcd(b, a % b);

}

ll solve(ll a, ll b, ll n) {

	ll fR = a, fM = b, sM = n;
	ll gcd = Gcd(Gcd(fR, sM), fM);

	return gcd;
	
}


int main() {

	int t;
	finp >> t;

	ll a, b, n;
	
	while (finp >> a >> b >> n) {

		int Size = a * b;

		while (b > n) {
			b = b - n;
		}

		if (solve(a, b, n)) {

			bool flag = false;
			int cnt = 0;
			for (int i = 0; i < Size; i++) {

				if (cnt == 2) {
					flag = true;
					break;
				}

				if (a * i % n == b) {
					num[cnt] = i;
					cnt++;
				}

			}

			if (!flag) {
				fout << "-1";
			}
			else {
				fout << num[0] << ' ' << num[1];
			}
			fout << '\n';
		}


	}

	return 0;
}