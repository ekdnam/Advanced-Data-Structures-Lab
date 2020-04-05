// Binary Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

# define MAX 25
class Tree;

class Node {
	friend class Tree;
	/*
		A Node of the binary Tree
		Has 3 data members:
		1) data: The data stored in the node
		2) *left: pointer to the left node
		3) *right: pointer to the right node
	*/
	int data;
	Node *right;
	Node *left;
public:
	Node() {
		data = -1;
		right = left = NULL;
	}
	Node(int data) {
		this->data = data;
		right = left = NULL;
	}
};

class Tree {
	char ch;
	Node *root;
	int depth;
	Node *temp;
	int top;
	Node *stack[MAX];
public:
	Tree() {
		ch = 'a';
		root = temp = NULL;
		depth = 0; top = -1;
		make_stack_null();
	}

	void make_stack_null() {
		top = -1;
		for (int i = 0; i < MAX; i++) {
			stack[i] = NULL;
		}
	}

	Node* make_tree(); // recursively calls itself to make the tree
	void create_tree(); // initial call to assign children to root
	
	void preorder_rec_call(); // call to recursive preorder func
	void preorder_rec(Node*);
	
	void inorder_rec_call(); // call to recursive inorder func
	void inorder_rec(Node*);
	
	void postorder_rec_call(); // call to recursive postorder func
	void postorder_rec(Node*);

	void preorder_non_rec_call(); // call to non recursive preorder func
	void preorder_non_rec(Node*);

	void inorder_non_rec_call(); // call to non recursive inorder func
	void inorder_non_rec(Node*);

	void postorder_non_rec_call(); // call to non recursive postorder func
	void postorder_non_rec(Node*);

	int get_depth(Node*);
	void call_depth();

	Node* assign_tree(Node*);

	Tree(const Tree &t);

	void operator =(const Tree &t);

	bool operator ==(const Tree &t);
	bool check_equality(Node*, Node*);

	void get_internal(Node*);
	void call_internal();

	void get_leaf(Node*);
	void call_leaf();

	void create_mirror(Node*);
	void call_mirror();
};

void Tree::postorder_non_rec_call() {
	if (root == NULL) {
		cout << "Tree is empty." << endl;
	}
	else {
		cout << "The postorder traversal of tree (non recursively) is: " << endl;
		postorder_non_rec(root);
		make_stack_null();
	}
}

void Tree::inorder_non_rec_call(){
	if (root == NULL) {
		cout << "Tree is empty." << endl;
	}
	else {
		cout << "The inorder traversal of tree (non recursively) is: " << endl;
		inorder_non_rec(root);
		make_stack_null();
	}
}

void Tree::preorder_non_rec_call() {
	if (root == NULL) {
		cout << "Tree is empty." << endl;
	}
	else {
		cout << "The preorder traversal of tree (non recursively) is: " << endl;
		preorder_non_rec(root);
		make_stack_null();
	}
}

void Tree::postorder_non_rec(Node *T) {
	int i = 0;
	while (1) {
		while (T) {
			i += 1;
			stack[i] = T;
			if (T->right) {
				i += 1;
				stack[i] = T->right;
				i += 1;
				stack[i] = NULL;
			}
			T = T->left;
		}
		if (i == 0) {
			return;
		}
		while (stack[i] && i != 0) {
			T = stack[i];
			cout << T->data << " ";
			i -= 1;
		}
		if (i != 0) {
			i -= 1;
		}
		if (i == 0) {
			return;
		}
		T = stack[i];
		i -= 1;
	}
}

void Tree::inorder_non_rec(Node *T) {
	int i = 0;
	while (1) {
		while (T) {
			i += 1;
			stack[i] = T;
			T = T->left;
		}
		if (i == 0) {
			return;

		}
		T = stack[i];
		i -= 1;
		cout << T->data << " ";
		T = T->right;
	}
}

void Tree::preorder_non_rec(Node *T) {
	int i = 0;
	while (1) {
		while (T) {
			cout << T->data << " ";
			if (T->right) {
				i = i + 1;
				stack[i] = T->right;
			}
			T = T->left;
		}
		if (i == 0)
			return;
		T = stack[i];
		i -= 1;

	}
}

void Tree::call_mirror() {
	create_mirror(root);
	temp = NULL;
}

void Tree::create_mirror(Node *x) {
	if (x == NULL) {
		return;
	}
	else {
		create_mirror(x->left);
		create_mirror(x->right);
		temp = x->left;
		x->left = x->right;
		x->right = temp;
	}
}

void Tree::call_internal() {
	if (root == NULL) {
		cout << "The tree is empty :(" << endl;
	}
	else {
		cout << "The internal nodes of the tree are: " << endl;
		get_internal(root);
	}
}

void Tree::get_internal(Node *x) {
	if (x->left == NULL && x->right == NULL) {
		return;
	}
	else {
		cout << x->data << " ";
		if (x->left != NULL) {
			get_internal(x->left);
		}
		if (x->right != NULL) {
			get_internal(x->right);
		}
	}
}

void Tree::call_leaf() {
	if (root == NULL) {
		cout << "The tree is empty :(" << endl;
	}
	else {
		cout << "The leaf nodes of the tree are: " << endl;
		get_leaf(root);
	}
}

void Tree::get_leaf(Node *x) {
	if (x->left == NULL && x->right == NULL) {
		cout << x->data << " ";
	}
	else {
		if (x->left != NULL) {
			get_leaf(x->left);
		}
		if (x->right != NULL) {
			get_leaf(x->right);
		}
	}
}

bool Tree::operator ==(const Tree &t) {
	if (root == NULL && t.root == NULL) {
		return 1;
	}
	else {
		return check_equality(root, t.root);
	}
}

bool Tree::check_equality(Node *left_tree, Node *right_tree) {
	if (left_tree == NULL && right_tree == NULL) {
		return 1;
	}
	if (left_tree != NULL && right_tree != NULL) {
		return ((left_tree->data == right_tree->data) && check_equality(left_tree->left, right_tree->right) && check_equality(left_tree->right, right_tree->right));
	}
	return 0;
}

Tree::Tree(const Tree &t) {
	root = assign_tree(t.root);
}

void Tree::operator =(const Tree &t) {
	root = assign_tree(t.root);
}

/*
Assign tree traverses the initial tree in an inorder fashion to create the new tree
*/

Node* Tree::assign_tree(Node *x) {
	if (x == NULL) {
		return NULL;
	}
	Node *new_node = new Node(x->data);
	
	new_node->left = assign_tree(x->left);
	
	new_node->right = assign_tree(x->right);

	return new_node;
}

void Tree::call_depth() {
	if (root == NULL) {
		cout << "As the tree is empty, depth is  zero." << endl;
		return;
	}
	depth = get_depth(root);
	cout << "The depth of tree is: " << depth << endl;
}

/*
get_depth()
1. If tree is empty then return 0
2. Else
	 (a) Get the max depth of left subtree recursively  i.e.,
		  call get_depth( tree->left-subtree)
	 (a) Get the max depth of right subtree recursively  i.e.,
		  call get_depth( tree->right-subtree)
	 (c) Get the max of max depths of left and right
		  subtrees and add 1 to it for the current node.
		 max_depth = max(max depth of left subtree,
							 max depth of right subtree)
							 + 1
	 (d) Return max_depth
*/

int Tree::get_depth(Node *x) {
	if (x == NULL) {
		return 0;
	}
	else {
		int d_left = 0, d_right = 0, ac_depth = 0;

		d_left = get_depth(x->left);
		d_right = get_depth(x->right);

		if (d_left > d_right) {
			ac_depth = d_left + 1;
			return ac_depth;
		}

		else {
			ac_depth = d_right + 1;
			return d_right;
		}


	}
}

void Tree::create_tree() {
	cout << "Creating tree..." << endl;
	
	cout << "Is the tree empty?(y/n)" << endl;
	cin >> ch;
	if (ch == 'n' || ch == 'N') {
		cout << "You are at the root of tree..." << endl;
		root = make_tree();
		return;
	}
	else {
		root = NULL;
	}
	

	
}

Node* Tree::make_tree() {
	int data;
	cout << "Enter data for node: ";
	cin >> data;
	
	Node *x = new Node(data);
	
	cout << "\nDoes left child of " << data << " exist?(y/n)";
	cin >> ch;
	if(ch == 'Y' || ch == 'y') {
		x->left = make_tree();
	}
	else {
		x->left = NULL;
	}
	
	cout << "\nDoes right child of " << data << " exist?(y/n)";
	cin >> ch;
	if (ch == 'Y' || ch == 'y') {
		x->right = make_tree();
	}
	else {
		x->right = NULL;
	}
	
	return x;
}

void Tree::preorder_rec_call() {
	if (root == NULL) {
		cout << "\nTree is empty :(" << endl;
	
		return;
	}
	cout << "\nPreorder traversal of tree (recursively) is: " << endl;
	preorder_rec(root);
}

void Tree::preorder_rec(Node *x) { // root -> left -> right
	if (x) {
		cout << x->data << " ";
		preorder_rec(x->left);
		preorder_rec(x->right);
	}
}

void Tree::inorder_rec_call() {
	if (root == NULL) {
		cout << "Tree is empty :(" << endl;
		return;
	}
	cout << "Inorder traversal of tree (recursively) is: " << endl;
	inorder_rec(root);
}

void Tree::inorder_rec(Node *x) { // left -> root -> right
	if (x) {
		inorder_rec(x->left);
		cout << x->data << " ";
		inorder_rec(x->right);
	}
}

void Tree::postorder_rec_call() {
	if (root == NULL) {
		cout << "Tree is empty :(" << endl;
		return;
	}
	cout << "Inorder traversal of tree (recursively) is: " << endl;
	postorder_rec(root);
}

void Tree::postorder_rec(Node *x) { // left -> right -> root
	if (x) {
		postorder_rec(x->left);
		postorder_rec(x->right);
		cout << x->data << " ";
	}
}

int main()
{
	Tree t;
	t.create_tree();

	t.preorder_rec_call();

	Tree new_tree = t;

	new_tree.preorder_rec_call();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
