#include <iostream>
#include <set>
//1. сравнить два дерева, что абсолютно один. структуры и элементы одинаковые
//2. сравнить что мнво элементов совпадает со мнвом в других.те стркутура разная, а значения одинаковые
using namespace std;

struct Node { 

	int data;
	Node* left;
	Node* right;
	Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct BinaryTree {

	public : 

		BinaryTree() : root(nullptr) {}

		Node* root;

		void insert(int val) {
			insertHelper(root, val);
		}

		int search(int val) {
			return searchHelper(root, val);
		}

		bool is_empty() {
			return isEmptyHelper(root);
		}
		
		bool absolute_compare_with(BinaryTree a) {
			return absoluteCompareHelper(root, a.root);
		}

		bool compare_with_bynums(BinaryTree a) {
			return set_of_elem_tree(root) == set_of_elem_tree(a.root);
		}
		

	private: 

		bool isEmptyHelper(Node*& node) {
			return node == nullptr;
		}

		void insertHelper(Node*& node, int val) {
			if (node == nullptr) {
				node = new Node(val);
			}
			else if (node->data > val) {
				insertHelper(node->left, val);
			}
			else {
				insertHelper(node->right, val);
			}
		}

		int searchHelper(Node*& node, int val,int deep = 0) {
			if (!isEmptyHelper(node)) {

				if (node->data == val) {
					return deep;
				}

				if (node->data > val) {
					return searchHelper(node->left, val,++deep);
				}
				else {
					return searchHelper(node->right, val, ++deep);
				}
			}
			else{
				return -1;
			}
		}

		bool absoluteCompareHelper(Node* root1, Node* root2) {
			if (root1 == nullptr && root2 == nullptr) {
				return true;
			}
			else if (root1 == nullptr || root2 == nullptr) {
				return false;
			}
			else if (root1->data != root2->data) {
				return false;
			}
			else {
				return absoluteCompareHelper(root1->left, root2->left) && absoluteCompareHelper(root1->right, root2->right);
			}
		}

		void dfs(Node* root, set<int> &a ) {
			if (root == nullptr) {
				return;
			}
			a.insert(root->data);
			dfs(root->left, a);
			dfs(root->right, a);
		}

		set<int> set_of_elem_tree(Node* root) {
			set<int> elems;
			dfs(root, elems);
			return elems;
		}
		
};



int main() {
	BinaryTree tree1; //изначальное дерево
	BinaryTree tree2; //те же элементы изначального дерева, но в другом порядке
	BinaryTree tree3; //другое дерево
	BinaryTree tree4, tree5;
	tree1.insert(5);
	tree1.insert(3);
	tree1.insert(7);
	tree1.insert(1);
	tree1.insert(9);

	tree2.insert(5);
	tree2.insert(3);
	tree2.insert(1);
	tree2.insert(9);
	tree2.insert(7);

	tree3.insert(5);
	tree3.insert(3);
	tree3.insert(6);
	tree3.insert(1);
	tree3.insert(9);

	cout << tree1.absolute_compare_with(tree1) << " " << tree1.compare_with_bynums(tree2) << " " << tree1.compare_with_bynums(tree3) << endl;
	cout << tree4.compare_with_bynums(tree1);
	return 0;
}