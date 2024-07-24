#include<bits/stdc++.h>
#define pii pair<int,int>
#define ff first
#define ss second
using namespace std;

void io() {
#ifndef  ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
	freopen("o.txt", "w", stdout);
#endif
}


class Node {
public:
	Node *parent, *left, *right;
	int data;
	int color;

	Node() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		color = 1;
	}
};

class RBTree {
private:
	int size;
	Node *root;

	void insertFix(Node *node) {

		while (node != root and node->parent->color == 1) {

			Node *uncle;
			if (node->parent == node->parent->parent->left) {
				uncle = node->parent->parent->right;

				if (uncle and uncle->color == 1) {

					node->parent->color = 0;
					uncle->color = 0;

					if (node->parent->parent != root) {
						node->parent->parent->color = 1;
					}
					node = node->parent->parent;
				}
				else {

					if (node == node->parent->right) {
						node = node->parent;
						leftRot(node);
					}
					node->parent->color = 0 ;
					node->parent->parent->color = 1;
					rightRot(node->parent->parent);
				}
			}
			else {
				uncle = node->parent->parent->left;

				if (uncle and uncle->color == 1) {
					node->parent->color = 0;
					uncle->color = 0;

					if (node->parent->parent != root) {
						node->parent->parent->color = 1;
					}
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRot(node);
					}
					node->parent->color = 0 ;
					node->parent->parent->color = 1;
					leftRot(node->parent->parent);
				}
			}
		}
	}

	void leftRot(Node *x) {
		Node *y = x->right;
		x->right = y->left;

		if (y->left) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			root = y ;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRot(Node *x) {
		Node *y = x->left;
		x->left = y->right;
		if (y->right) {
			y->right->parent = x;
		}
		y->parent = x->parent;

		if (x->parent == nullptr) {
			root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x ;
		x->parent = y;
	}


	Node *findPre(Node *root)
	{
		Node *pp = root->left;
		while (pp->right)
			pp = pp->right;

		return pp;
	}
	Node *findSuc(Node *root)
	{
		Node *pp = root->right;
		while (pp->left)
			pp = pp->left;

		return pp;
	}

public:
	RBTree() {
		size = 0;
		root = nullptr;
	}

	void insert(int val)
	{
		auto *node = new Node();
		node->data = val;

		if (root == nullptr) {
			root = node;
			node->color = 0;
			return;
		}

		Node *curr = root;

		while (curr) {
			if (curr->left and curr->data > val) {
				curr = curr->left;
			}
			else if (curr->right and curr->data < val) {
				curr = curr->right;
			}
			else {
				break;
			}
		}

		// cout << "Coming over here\n " << temp->data << endl;
		node->parent = curr;

		if (curr->data > val) {
			curr->left = node;
		}
		else {
			curr->right = node;
		}

		insertFix(node);
	}


	int getHeight(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(getHeight(node->left), getHeight(node->right));
	}

	int printHeight() {
		return getHeight(root);
	}



	void printTree() {

		cout << "------------\n";
		queue<Node *>q;

		if (!root) return;

		q.push(root);

		int level = 0;

		while (!q.empty()) {
			auto top = q.front();
			q.pop();

			if (top->color == 1) {
				cout << "R";
			}
			else {
				cout << "B";
			}
			cout << top->data << " ";

			if (top->left != nullptr) {
				q.push(top->left);
				if (top->left->color == 1)
					cout << "R" ;
				else
					cout << "B" ;
				cout << top->left->data;
				cout << " ";
			} else {
				cout << "NULL" << " ";
			}

			if (top->right != nullptr) {
				q.push(top->right);
				if (top->right->color == 1)
					cout << "R" ;
				else
					cout << "B" ;
				cout << top->right->data;
				cout << " ";
			} else {
				cout << "NULL" << " ";
			}

			cout << endl;

		}
		std::cout << std::endl;
		std::cout << "----------------" << std::endl;

	}

	void printInorder(Node *root) {
		if (!root) return;
		printInorder(root->left);
		cout << root->data << " ";
		printInorder(root->right);
	}

	void inorderTraversal() {
		printInorder(root);
	}


	void findPreSuc(Node* root, Node*& pre, Node*& suc, int key)
	{

		if (!root)
			return;
		if (root->data == key)
		{
			if (root->left)
				pre = findPre(root);

			if (root->right)
				suc = findSuc(root);
		}
		else if (root->data < key)
		{
			pre = root;
			findPreSuc(root->right, pre, suc, key);
		}
		else
		{
			suc = root;
			findPreSuc(root->left, pre, suc, key);
		}
	}

	pii findPair(int key) {
		Node *pre = nullptr;
		Node *succ = nullptr;
		findPreSuc(root, pre, succ, key);

		if (pre and succ) {
			return {pre->data, succ->data};
		}
		else if (pre) {
			return {pre->data, -1};
		}
		else {
			return { -1, succ->data};
		}

		return { -1, -1};
	}

	bool checkIfNodeIsPresent(int data, Node *root) {
		if (!root) return 0;
		if (root->data == data) return 1;
		if (root->data < data) return checkIfNodeIsPresent(data, root->right);
		return checkIfNodeIsPresent(data, root->left);
	}

	bool search(int data) {
		return checkIfNodeIsPresent(data, root);
	}

	Node* deleteNode(Node* root, int key) {

		bool found = search(key);
		if (!found) return nullptr;

		if (root)
			if (key < root->data) root->left = deleteNode(root->left, key);    //We frecursively call the function until we find the target node
			else if (key > root->data) root->right = deleteNode(root->right, key);
			else {
				if (!root->left && !root->right) return nullptr;         //No child condition
				if (!root->left || !root->right)
					return root->left ? root->left : root->right;    //One child contion -> replace the node with it's child
				//Two child condition
				Node* temp = root->left;                        //(or) TreeNode *temp = root->right;
				while (temp->right != nullptr) temp = temp->right;    //      while(temp->left != NULL) temp = temp->left;
				root->data = temp->data;                            //       root->val = temp->val;
				root->left = deleteNode(root->left, temp->data);  //        root->right = deleteNode(root->right, temp);
			}
		return root;
	}

	void deleteNodeInRBTree(int key) {
		Node *res = deleteNode(root, key);
		if (res == nullptr) {
			cout << "Node is not present in the tree\n";
		}
		else {
			cout << "Node is deleted successfully\n";
		}
	}

	int findMin(Node *root) {
		if (!root) return 1e9;
		int res = root->data;
		int lres = findMin(root->left);
		int rres = findMin(root->right);

		return min({res, lres, rres});

	}

	int findMax(Node *root) {

		if (!root) return -1e9;
		int res = root->data;
		int lres = findMax(root->left);
		int rres = findMax(root->right);

		return max({res, lres, rres});

	}

	int mini() {
		return findMin(root);
	}

	int maxi() {
		return findMax(root);
	}

};

int main() {

	RBTree rbTree;

	ifstream file("i.txt");
	int key;

	if (!file) {
		cerr << "Unable to open file keys.txt";
		exit(1);
	}

	while (file >> key) {
		rbTree.insert(key);
	}


	file.close();

	cout << "Existing Configuration of the tree\n";
	rbTree.printTree();

	while (1) {
		int ch;
		cout << "\n1. Insert \n2. Delete\n3. Minimum\n4. Maximum\n5. Predecessor & Successor\n6. Structure Of Tree\n7. Search\n8. Exit\n";
		cout << "Select an operation: ";
		cin >> ch;
		int n;

		switch (ch) {
		case 1: {
			cout << "Enter node to be inserted: ";
			cin >> n;
			rbTree.insert(n);
			cout << "Height of tree is: " << rbTree.printHeight() << endl;
			break;
		}

		case 2: {
			cout << "Enter node to be deleted: ";
			cin >> n;
			rbTree.deleteNodeInRBTree(n);
			cout << "Height of tree is: " << rbTree.printHeight() << endl;
			break;
		}

		case 3:
			cout << "Minimum: " << rbTree.mini() << endl;
			break;
		case 4:
			cout << "Maximum: " << rbTree.maxi() << endl;
			break;
		case 5: {
			cout << "Enter node for which Pred/Suc is required: ";
			cin >> n;
			pii res = rbTree.findPair(n);
			cout << "Predecessor " << res.ff << endl;
			cout << "Successor " << res.ss << endl;
			break;
		}

		case 6: {
			rbTree.printTree();
			cout << endl;
			cout << "Inorder Traversal : ";
			rbTree.inorderTraversal();
			break;
		}

		case 7: {
			cout << "Enter node to be searched: ";
			cin >> n;
			if (rbTree.search(n)) {
				cout << "Node " << n << " Found in Tree" << endl;
			}
			else {
				cout << "Node " << n << " Not Found in Tree" << endl;
			}
			break;
		}
		case 8:
			cout << "Thank you" << endl;
			return 0;
		default:
			cout << "Invalid" << endl;
		}
	}
}