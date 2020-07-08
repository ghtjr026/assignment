#include <fstream>
#include <vector>
using namespace std;

ifstream finp("point_in_a_polygon.inp");
ofstream fout("point_in_a_polygon.out");

typedef struct polygon {

	int x, y;

};

vector<polygon> Point;

int ccw(polygon r, polygon p, polygon q) {
	return (p.x - r.x) * (q.y - r.y) - (p.y - r.y) * (q.x - r.x);
}

bool leftturn(polygon a, polygon b, polygon c) {
	return ccw(a, b, c) > 0;
}

bool collinear(polygon a, polygon b, polygon c) {
	return ccw(a, b, c) == 0;
}

bool between(polygon a, polygon b, polygon c) {

	if (!collinear(a, b, c)) {
		return false;
	}
	if (a.x != b.x) {
		return a.x <= c.x && c.x <= b.x || b.x <= c.x && c.x <= a.x;
	}
	else {
		return a.y <= c.y && c.y <= b.y || b.y <= c.y && c.y <= a.y;
	}

}

void solve(int n, polygon pivot) {

	int crossing = 0;

	for (int i = 0; i < n; i++) {
		int ipuls1 = (i + 1) % n;

		if (between(Point[i], Point[ipuls1], pivot)) {
			fout << 1 << '\n';
			return;
		}if ((Point[i].y < pivot.y && Point[ipuls1].y >= pivot.y && leftturn(Point[i], Point[ipuls1], pivot))
			|| Point[ipuls1].y < pivot.y && Point[i].y >= pivot.y && leftturn(Point[ipuls1], Point[i], pivot)) {
			crossing++;
		}

	}
	if (crossing % 2) {
		fout << 1 << '\n';
	}
	else {
		fout << 0 << '\n';
	}

}

int main() {

	int n;
	finp >> n;
	while (n--) {
		int x, y;
		finp >> x >> y;
		Point.push_back({ x, y });
	}

	int p;
	finp >> p;
	while (p--) {
		int x, y;
		finp >> x >> y;
		polygon pivot = { x, y };

		solve(Point.size(), pivot);

	}


	return 0;
}