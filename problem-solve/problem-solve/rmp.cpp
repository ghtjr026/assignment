#include <fstream>
#include <vector>
using namespace std;

ifstream finp("rmp.inp");
ofstream fout("rmp.out");

int arr[1000001];
int tree[4045001];
int result = 0;
bool flag;

int maketree(int idx, int start, int end) {

	if (start == end) {
		return tree[idx] = start;
	}

	int mid = (start + end) / 2;
	int left = maketree(idx * 2 + 1, start, mid);
	int right = maketree(idx * 2 + 2, mid + 1, end);

	if (arr[left] <= arr[right]) {
		return tree[idx] = left;
	}
	else {
		return tree[idx] = right;
	}

}

int isRange(int idx, int start, int end, int left, int right) {
	
	if (left > end || right < start) {
		return -1;
	}

	else if (left <= start && right >= end) {
		return tree[idx];
	}


	int mid = (start + end) / 2;
	int leftIdx = isRange(idx * 2 + 1, start, mid, left, right);
	int rightIdx = isRange(idx * 2 + 2, mid + 1, end, left, right);

	if (leftIdx == -1) {
		return rightIdx;
	}
	else if (rightIdx == -1) {
		return leftIdx;
	}

	if (arr[leftIdx] <= arr[rightIdx]) {
		return leftIdx;
	}
	else {
		return rightIdx;
	}

}

void change(int idx, int start, int end, int key) {

	if (start == end && start == key) {
		return ;
	}

	if (start <= key && key <= end) {
		int mid = (start + end) / 2;
		change(idx * 2 + 1, start, mid, key);
		change(idx * 2 + 2, mid + 1, end, key);
		if (arr[tree[idx * 2 + 1]] <= arr[tree[idx * 2 + 2]]) {
			tree[idx] = tree[idx * 2 + 1];
		}
		else {
			tree[idx] = tree[idx * 2 + 2];
		}
	}

}

int main() {

	ios_base::sync_with_stdio(0);
	finp.tie(0); fout.tie(0);

	int num;
	finp >> num;
	for (int i = 0; i < num; i++) {
		finp >> arr[i];
	}

	char type;
	int a = 0, b = num - 1;

	maketree(0, a, b);

	while (finp >> type >> a >> b) {

		switch (type) {
		case 'q':
			flag = false;
			result += (isRange(0, 0, num - 1, a, b) % 100000);
			result = result % 100000;
			break;
		case 'c':
			arr[a] = b;
			change(0, 0, num - 1, a);
			break;
		case 's':
			fout << result;
			break;
		}

	}

	return 0;
}
