#include <fstream>
#include <vector>
using namespace std;

ifstream finp("crt.inp");
ofstream fout("crt.out");

typedef long long ll;
typedef struct crt {
	ll r, m;
};

vector<crt> Crt;
int testcase, k, R, A;

ll Gcd(ll a, ll b) {

	if (b == 0) return a;
	return Gcd(b, a % b);

}

void euclid(ll r1, ll r2) {
	ll q = -1, r = -1, s1 = 1, s2 = 0, s, t1 = 0, t2 = 1, t;

	while (r != 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2; r2 = r;

		s = s1 - q * s2;
		s1 = s2; s2 = s;

		t = t1 - q * t2;
		t1 = t2; t2 = t;
	}

	R = r1; A = s1;

}

void solve() {

	ll fR = Crt[0].r, fM = Crt[0].m;
	for (int i = 1; i < k; i++) {
		ll sR = Crt[i].r, sM = Crt[i].m;

		sR -= fR;
		while (1) {
			if (!(sR < 0)) break;
			sR += sM;
		}

		ll gcd = Gcd(Gcd(fM, sR),sM);

		sR /= gcd; sM /= gcd;
		euclid(fM / gcd, sM);
		if (R != 1) {
			fout << "-1\n";
			return;
		}

		sR *= A;
		if (sR > sM) {
			sR %= sM;
		}
		while (1) {
			if (!(sR < 0)) break;
			sR += sM;
		}

		fR += fM * sR;
		fM *= sM;
	}

	fout << fR << '\n';

}

int main() {

	finp >> testcase;
	while (testcase--) {

		finp >> k;
		Crt.clear(); Crt.resize(k);
		for (int i = 0; i < k; i++) {
			finp >> Crt[i].r >> Crt[i].m;
		}
		solve();

	}

	return 0;
}