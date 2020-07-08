#include <fstream>
using namespace std;

ifstream finp("rbt.inp");
ofstream fout("rbt.out");

typedef struct treeNode {

	int key;
	char color;
	treeNode* left;
	treeNode* right;
	treeNode* parents;

}treeNode;

typedef struct Tree {
	treeNode* root;
}Tree;

Tree* tree;
treeNode* leaf;

treeNode* creatNode(int key) {

	treeNode* a = new treeNode();
	a->key = key;
	a->color = 'r';
	a->parents = NULL;
	a->left = a->right = leaf;
	return a;

}

void leftRotate(treeNode* x) {

	treeNode* y = x->right;
	x->right = y->left;
	y->left = x;
	if (x == tree->root) {
		tree->root = y;
	}
	else if (x->parents->right == x) {
		x->parents->right = y;
	}
	else {
		x->parents->left = y;
	}
	y->parents = x->parents;
	x->parents = y;
	x->right->parents = x;

}

void rightRotate(treeNode* x) {

	treeNode* y = x->left;
	x->left = y->right;
	y->right = x;
	if (x == tree->root) {
		tree->root = y;
	}
	else if (x->parents->right == x) {
		x->parents->right = y;
	}
	else {
		x->parents->left = y;
	}
	y->parents = x->parents;
	x->parents = y;
	x->left->parents = x;

}

void Insert(treeNode*& root, treeNode* x) {
	
	if (root == leaf) {
		root = x;
		return;
	}
	if (root->key > x->key) {
		Insert(root->left, x);
		root->left->parents = root;
	}
	else {
		Insert(root->right, x);
		root->right->parents = root;
	}

	return;
}

void rbtInsert(Tree* tree, int key) {

	treeNode* x = creatNode(key);
	Insert(tree->root, x);

	while (x != NULL && x != tree->root && x->parents->color == 'r') {

		if (x->parents == x->parents->parents->left) {
			treeNode* y = x->parents->parents->right;
			if (y->color == 'r') { //case1
				x->parents->color = 'b';
				y->color = 'b';
				x->parents->parents->color = 'r';
				x = x->parents->parents;
			}
			else {
				if (x == x->parents->right) { //case2
					x = x->parents;
					leftRotate(x);
				}
				x->parents->color = 'b';
				x->parents->parents->color = 'r';
				rightRotate(x->parents->parents);
			}
		}
		else {
			treeNode* y = x->parents->parents->left;
			if (y->color == 'r') {
				x->parents->color = 'b';
				y->color = 'b';
				x->parents->parents->color = 'r';
				x = x->parents->parents;
			}
			else {
				if (x == x->parents->left) {
					x = x->parents;
					rightRotate(x);
				}
				x->parents->color = 'b';
				x->parents->parents->color = 'r';
				leftRotate(x->parents->parents);
			}
		}

	}

	tree->root->color = 'b';
	tree->root->parents = NULL;
}

treeNode* findNode(Tree* tree, int key) {

	treeNode* root = tree->root;
	while (key != root->key) {
		if (key < root->key) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return root;

}

treeNode* Minimum(treeNode* x) {
	if (x != leaf) {
		while (x->left != leaf) {
			x = x->left;
		}
	}
	return x;
}

void rbtDeleteFixup(Tree* tree, treeNode* x) {
	while (x != tree->root && x->color == 'b') {
		tree->root->parents == NULL;
		treeNode* xParents = x->parents;
		if (x == x->parents->left) {
			treeNode* w = xParents->right;
			if (w->color == 'r') {
				w->color = 'b';
				w->parents->color = 'r';
				leftRotate(xParents);
				w = xParents->right;
			}
			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				x = xParents;
			}
			else if (w->right->color == 'b') {
				w->left->color = 'b';
				w->color = 'r';
				rightRotate(w);
				w = xParents->right;
			}
			if (w->right->color == 'r') {
				w->color = xParents->color;
				xParents->color = 'b';
				w->right->color = 'b';
				leftRotate(xParents);
				x = tree->root;
			}
		}
		else {
			treeNode* w = x->parents->left;
			if (w->color == 'r') {
				w->color = 'b';
				w->parents->color = 'r';
				rightRotate(xParents);
				w = xParents->left;
			}
			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				x = xParents;
			}
			else if (w->left->color == 'b') {
				w->right->color = 'b';
				w->color = 'r';
				leftRotate(w);
				w = xParents->left;
			}
			if (w->left->color == 'r') {
				w->color = xParents->color;
				xParents->color = 'b';
				w->left->color = 'b';
				rightRotate(xParents);
				x = tree->root;
			}
		}
		leaf->color = 'b';
	}
	x->color = 'b';
}

void rbtDelete(Tree* tree, int key) {

	treeNode* z = findNode(tree, key);
	treeNode* y = leaf, *x = leaf;

	if (z->left == leaf || z->right == leaf) {
		y = z;
	}
	else {
		y = Minimum(z->right);
	}

	if (y->left != leaf) {
		x = y->left;
	}
	else {
		x = y->right;
	}

	x->parents = y->parents;

	if (y->parents == NULL) {
		tree->root = x;
	}
	else if (y == y->parents->left) {
		y->parents->left = x;
	}
	else {
		y->parents->right = x;
	}

	if (y != z) {
		z->key = y->key;
	}

	if (y->color == 'b') {
		rbtDeleteFixup(tree, x);
	}

}

void treeSearch(Tree* tree, int key) {
	treeNode* root = tree->root;
	while (root != leaf && key != root->key) {
		if (key < root->key) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}

	fout << "color(" << key << "): ";
	if (root->color == 'r') {
		fout << "RED\n";
	}
	else {
		fout << "BLACK\n";
	}
}

int main() {

	char state; int num;
	tree = new Tree();

	leaf = new treeNode();
	leaf->key = -1;
	leaf->color = 'b';
	leaf->parents = NULL;
	leaf->left = leaf->right = leaf;
	

	tree->root = leaf;
	leaf->left = leaf->right = leaf;

	while (finp >> state >> num) {
		if (num == -1) break;
		switch (state) {

		case 'i': rbtInsert(tree, num); break;
		case 'd': rbtDelete(tree, num); break;
		case 'c': treeSearch(tree, num); break;

		}
	}

	return 0;
}