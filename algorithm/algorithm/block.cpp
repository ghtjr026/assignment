#include <cstring>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct rec { 
	int x;
	int y;
	int p;
	int q;
};

int T, N;
int node_size, h;
int* nodes;
int maxWidth , maxHeight;

ifstream finp("block.inp");
ofstream fout("block.out");

bool comp_y(rec& A, rec& B) { 
	return A.y < B.y; 
}

bool comp_x(rec& A, rec& B) { 
	return A.x < B.x; 
}

void reset() {

	memset(nodes, 0, sizeof(int) * node_size);

}

int getHeight(const int index, const int s, const int e, const int& l, const int& r) {

	if (l > e || r < s)
		return 0;
	else if (l <= s && e <= r)
		return nodes[index];

	int mid = (s + e) / 2;
	
	return max(getHeight(index * 2, s, mid, l, r), getHeight(index * 2 + 1, mid + 1, e, l, r));

}

void update(const int& changed_indexL, const int& changed_indexR, const int& diff, const int index, const int s, const int e) {

	if (changed_indexR < s || changed_indexL > e)
		return;
	
	nodes[index] = max(nodes[index], diff);
	
	if (s != e) {
		
		int mid = (s + e) / 2;
		update(changed_indexL, changed_indexR, diff, index * 2, s, mid);
		update(changed_indexL, changed_indexR, diff, index * 2 + 1, mid + 1, e);
	
	}

}

void set_temp_x(vector<rec> & R, vector<int> & temp) {

	for (int i = 0; i < N; i++)
	{
		temp.push_back(R[i].x);
		temp.push_back(R[i].p);
	}

}

void set_Sort_x(vector<int> & Sort, vector<int> & temp) {

	for (int i = 0; i < 2 * N; i++)
	{
		if (i >= 1 && Sort.back() == temp[i])
			continue;
		Sort.push_back(temp[i]);
	}

}

void set_temp_y(vector<rec>& R, vector<int>& temp) {

	for (int i = 0; i < N; i++)
	{
		temp.push_back(R[i].y);
		temp.push_back(R[i].q);
	}

}

void set_Sort_y(vector<int>& Sort, vector<int>& temp) {

	for (int i = 0; i < 2 * N; i++)
	{
		if (i >= 1 && Sort.back() == temp[i])
			continue;
		Sort.push_back(temp[i]);
	}

}


int step1(vector<rec> & R, int h, int node_size, int* nodes) {
	
	vector<int> temp;
	set_temp_x(R, temp);
	sort(temp.begin(), temp.end());
	vector<int> Sort;
	set_Sort_x(Sort, temp);

	reset();

	int ret = 0, sortedSIZE = Sort.size() - 1;
	for (int i = 0; i < N; i++)
	{
		rec& r = R[i];
		int bottom = r.y, up = r.q - r.y;

		vector<int>::iterator left = lower_bound(Sort.begin(), Sort.end(), r.x);
		vector<int>::iterator right = lower_bound(Sort.begin(), Sort.end(), r.p);
		const int lidx = left - Sort.begin();
		const int ridx = right - Sort.begin() - 1;

		int h = getHeight(1, 0, sortedSIZE, lidx, ridx);
		if (h < r.y)
			r.y = h, r.q = h + up, ++ret;

		update(lidx, ridx, r.q, 1, 0, sortedSIZE);
	}
	return (ret > 0);
}

int step2(vector<rec> & R, int h, int node_size, int* nodes) {

	vector<int> temp;
	set_temp_y(R, temp);
	sort(temp.begin(), temp.end());
	vector<int> Sort;
	set_Sort_y(Sort, temp);

	reset();

	int ret = 0, sortedSIZE = Sort.size() - 1;
	for (int i = 0; i < N; i++)
	{
		rec& r = R[i];
		int bottom = r.x, up = r.p - r.x;

		vector<int>::iterator left = lower_bound(Sort.begin(), Sort.end(), r.y);
		vector<int>::iterator right = lower_bound(Sort.begin(), Sort.end(), r.q);
		const int lidx = left - Sort.begin();
		const int ridx = right - Sort.begin() - 1;

		int h = getHeight(1, 0, sortedSIZE, lidx, ridx);
		if (h < r.x)
			r.x = h, r.p = h + up, ++ret;
		update(lidx, ridx, r.p, 1, 0, sortedSIZE);
	}
	return (ret > 0);
}

void getmax(vector<rec> R) {

	for (int i = 0; i < N; i++)
	{
		maxWidth = max(maxWidth, R[i].p);
		maxHeight = max(maxHeight, R[i].q);
	}

}

int main()
{
	finp >> T;
	while (T--)
	{
		finp >> N;
		vector<rec> R(N);
		h = (int)ceil(log2(N * 2));
		node_size = 1 << (h + 1);
		nodes = new int[node_size];
		
		for (int i = 0; i < N; i++) {
			finp >> R[i].x >> R[i].y >> R[i].p >> R[i].q;
		}

		int noMoved = 0;
		sort(R.begin(), R.end(), comp_y);
		noMoved |= step1(R, h, node_size, nodes);
		sort(R.begin(), R.end(), comp_x);
		noMoved |= step2(R, h, node_size, nodes);
		
		while (noMoved) {
			noMoved = 0;
			sort(R.begin(), R.end(), comp_y);
			noMoved |= step1(R, h, node_size, nodes);
			sort(R.begin(), R.end(), comp_x);
			noMoved |= step2(R, h, node_size, nodes);
		}

		maxWidth = 0;
		maxHeight = 0;
		
		getmax(R);
		
		fout << maxWidth << ' ' << maxHeight << '\n';
	}
}