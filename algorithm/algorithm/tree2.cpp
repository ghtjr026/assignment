#include <fstream>
#include <vector>
using namespace std;

vector<int> pre, in, post;
int visited[1000000];
int check[3];

ifstream finp("tree2.inp");
ofstream fout("tree2.out");

void Input(vector<int>& arr, int n) {
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		finp >> arr[i];
	}
}

int find_root_in(int root, int size) {

	int point = 0;
	for (int i = 0; i < size; i++) {
		if (in[i] == root) {
			point = i;
			break;
		}
	}

	return point;
}

int find_root_post(int root, int size) {

	int point = 0;
	for (int i = 0; i < size; i++) {
		if (post[i] == root) {
			point = i;
			break;
		}
	}

	return point;

}

int find_root_pre(int root, int size) {

	int point = 0;
	for (int i = 0; i < size; i++) {
		if (pre[i] == root) {
			point = i;
			break;
		}
	}

	return point;

}

int left_size(int point) {

	int count = 0;

	for (int i = point - 1; i > -1; i--) {
		if (visited[in[i]] == 1) {
			break;
		}
		count++;
	}

	return count;

}

int right_size(int point, int size) {

	int count = 0;

	for (int i = point + 1; i < size; i++) {
		if (visited[in[i]] == 1) {
			break;
		}
		count++;
	}

	return count;

}

void find_pre(int root, int point, int size) {

	pre.push_back(root);

	visited[root] = 1;

	int left = left_size(point);
	int right = right_size(point, size);

	int post_point = find_root_post(root, size);

	if (left != 0) {
		int left_point = 0;
		for (int i = 0; i < size; i++) {
			if (in[i] == post[post_point - right - 1]) {
				left_point = i;
				break;
			}
		}
		find_pre(in[left_point], left_point, size);
	}
	if (right != 0) {
		int right_point = 0;
		for (int i = 0; i < size; i++) {
			if (in[i] == post[post_point - 1]) {
				right_point = i;
				break;
			}
		}
		find_pre(in[right_point], right_point, size);
	}

}

void find_post(int root, int point, int size) {

	visited[root] = 1;

	int left = left_size(point);
	int right = right_size(point, size);

	int pre_point = find_root_pre(root, size);

	if (left != 0) {
		int left_point = 0;
		for (int i = 0; i < size; i++) {
			if (in[i] == pre[pre_point + 1]) {
				left_point = i;
				break;
			}
		}
		find_post(in[left_point], left_point, size);
	}
	if (right != 0) {
		int right_point = 0;
		for (int i = 0; i < size; i++) {
			if (in[i] == pre[pre_point + left + 1]) {
				right_point = i;
				break;
			}
		}
		find_post(in[right_point], right_point, size);
	}

	post.push_back(root);

}

int main() {

	int node_num, test = 2, root;

	finp >> node_num;

	while (test--) {

		int type;
		finp >> type;

		switch (type) {
		case -1: //pre
			Input(pre, node_num);
			root = pre[0];
			check[0] = 1;
			break;
		case 0: // in
			Input(in, node_num);
			check[1] = 1;
			break;
		case 1: // post
			Input(post, node_num);
			root = post[node_num - 1];
			check[2] = 1;
			break;
		}

	}


	int i; // 구해야하는 order i = 0: pre i = 2: post
	for (i = 0; i < 3; i++) {
		if (check[i] == 0) {
			break;
		}
	}

	int point = find_root_in(root, node_num);
	if (i == 0) {
		find_pre(root, point, node_num);
		for (int i = 0; i < node_num; i++) {
			fout << pre[i] << '\n';
		}
	}
	else if (i == 2) {
		find_post(root, point, node_num);
		for (int i = 0; i < node_num; i++) {
			fout << post[i] << '\n';
		}
	}

	pre.clear();
	in.clear();
	post.clear();

	finp.close();
	fout.close();

	return 0;
}