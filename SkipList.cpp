#include<bits/stdc++.h>
using namespace std;


void io() {
#ifndef  ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
	freopen("o.txt", "w", stdout);
#endif
}

class Node {
public:
	int value;
	Node *top, *down, *left, *right;

	Node(int val) : value(val), top(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

class SkipList {
private:
	vector<Node*> headers;
	int maxLevel;
	float probability;

	bool coinToss() {
		return rand() % 2 == 1;
	}

public:
	SkipList(int maxLevel) : maxLevel(maxLevel) {
		headers.resize(maxLevel);
		int minf = numeric_limits<int>::min();
		int pinf = numeric_limits<int>::max();


		for (int i = 0; i < maxLevel; ++i) {
			headers[i] = new Node(minf);
			Node* infNode = new Node(pinf);
			headers[i]->right = infNode;
			infNode->left = headers[i];
			if (i > 0) {
				headers[i]->down = headers[i - 1];
				headers[i - 1]->top = headers[i];
				infNode->down = headers[i - 1]->right;
				headers[i - 1]->right->top = infNode;
			}
		}
	}

	Node* search(int value) {
		Node* current = headers.back();
		bool found = false;
		cout << "\033[1;31m" << "Search Path -> " << "\033[0m";


		bool be = false;

		while (true) {
			// Move to the right as far as possible while staying within bounds
			while (current->right->value != std::numeric_limits<int>::max() && current->right->value <= value) {


				current = current->right;
				std::cout << current->value << " -> ";
			}

			if (current->value == value) {
				break;
			}
			// Move down to the next level if possible
			if (current->down != nullptr) {
				current = current->down;
				std::cout << "down -> ";
			} else {
				break;
			}
		}

		if (current->value == value) {
			found = true;
		}

		std::cout << (found ? "found" : "not found") << std::endl;

		return found ? current : nullptr;
	}

	void display() {
		for (int i = maxLevel - 1; i >= 0; --i) {
			Node* node = headers[i];
			cout << "Level " << i + 1 << ": ";
			while (node != nullptr) {
				cout << node->value << " ";
				node = node->right;
			}
			cout << endl;
		}
	}

	Node *insert_node_at_level(int level, int key) {

		Node *curr = headers[level];

		// cout << "Inserting " << key << "at " << level << endl;

		while (curr and curr->value < key and curr->right->value <= key) {
			curr = curr->right;
		}

		Node *temp = new Node(key);
		temp->right = curr->right;
		temp->left = curr;
		curr->right->left = temp;
		curr->right = temp;

		return temp;

	}

	void insert(int data) {
		vector<Node*> update(maxLevel);
		Node* current = headers.back();

		// Find the position to insert
		for (int i = maxLevel - 1; i >= 0; --i) {
			while (current->right->value != numeric_limits<int>::max() && current->right->value < data) {
				current = current->right;
			}
			update[i] = current;
			if (i > 0) {
				current = current->down;
			}
		}

		current = current->right;
		if (current->value == data) {
			cout << "Value " << data << " already exists." << endl;
			return;
		}

		Node *prev = insert_node_at_level(0, data);

		for (int level = 1; level < maxLevel; level++) {

			if (coinToss()) {

				Node *temp = insert_node_at_level(level, data);
				temp->down = prev;
				prev->top = temp;
				prev = temp;
			}
			else {
				break;
			}
		}
	}

	void remove(int value) {

		Node* current = headers.back();
		bool found = false;

		Node *isPresent = search(value);
		if (!isPresent) {
			cout << "Value is not present in the skiplist\n";
			return;
		}
		for (int i = maxLevel - 1; i >= 0; --i) {

			Node *temp = current;

			// while (temp) {
			// 	cout << temp->value << " ";
			// 	temp = temp->right;
			// }
			// cout << endl;
			while (current->right->value != numeric_limits<int>::max() && current->right->value < value) {
				current = current->right;
			}
			if (current->right->value == value) {
				found = true;
				current = current->right;
				current->left->right = current->right;
				current->right->left = current->left;
				Node* temp = current;
				current = current->left;
				delete temp;
			}
			if (i > 0) {
				current = current->down;
			}
		}

		if (!found) {
			cout << "Value " << value << " not found." << endl;
		}
	}



};


int main() {

	srand(time(0));

	// io();

	int levelsInSkipList;

	// cin >> levelsInSkipList;

	SkipList skiplist(5);
	skiplist.insert(3);
	skiplist.insert(6);
	skiplist.insert(7);
	skiplist.insert(9);
	skiplist.insert(12);
	skiplist.insert(19);
	skiplist.insert(17);
	skiplist.insert(26);
	skiplist.insert(21);



	cout << "Initial Configuration\n";
	skiplist.display();
	cout << endl;


	// int q;
	// cin >> q;
	while (true) {
		int type;
		cin >> type;

		if (type == 1) {
			int key;
			cin >> key;
			skiplist.insert(key);
			skiplist.display();
			cout << endl;
		}
		else if (type == 2) {
			int key;
			cin >> key;

			auto res = skiplist.search(key);
			if (res) {
				cout << key << " Found\n";
			}
			else {
				cout << key << " Not found\n";
			}
		}
		else if (type == 3) {
			int key;
			cin >> key;

			cout << "\033[1;31m" << "Configuration before delete" << "\033[0m\n";

			skiplist.display();
			cout << endl;

			skiplist.remove(key);
			cout << "\033[1;31m" << "Configuration after delete" << "\033[0m\n";

			skiplist.display();
			cout << endl;

		}
		else {
			break;
		}

	}






}