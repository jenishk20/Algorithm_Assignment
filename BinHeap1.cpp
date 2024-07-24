#include<bits/stdc++.h>
using namespace std;

class BinHeapNode {
public:
	int key, degree;
	BinHeapNode *parent , *child, *sibling;

	BinHeapNode(int key) {
		this->key = key;
		this->degree = 0;
		this->parent = nullptr;
		this->child = nullptr;
		this->sibling = nullptr;
	}
};

class BinomialHeap {

private:
	BinHeapNode* findMinNode() {
		if (!head) return nullptr;

		BinHeapNode* minNode = head;
		BinHeapNode* next = head->sibling;
		while (next) {
			if (next->key < minNode->key) {
				minNode = next;
			}
			next = next->sibling;
		}
		return minNode;
	}

	BinHeapNode* mergeTrees(BinHeapNode* b1, BinHeapNode* b2) {
		if (b1->key > b2->key) {
			swap(b1, b2);
		}
		b2->parent = b1;
		b2->sibling = b1->child;
		b1->child = b2;
		b1->degree++;
		return b1;
	}

public:
	BinHeapNode *head;
	BinomialHeap() {
		head = nullptr;
	}

	void insert(int key) {
		BinomialHeap *tempHeap = new BinomialHeap();
		tempHeap->head = new BinHeapNode(key);
		unioni(tempHeap);
	}

	BinHeapNode *unionHeaps(BinHeapNode *h1, BinHeapNode *h2) {
		if (!h1) return h2;
		if (!h2) return h1;

		BinHeapNode *newHead = nullptr;
		BinHeapNode *tail = nullptr;
		BinHeapNode* a = h1;
		BinHeapNode* b = h2;

		if (a->degree <= b->degree) {
			newHead = a;
			a = a->sibling;
		} else {
			newHead = b;
			b = b->sibling;
		}
		tail = newHead;

		while (a && b) {
			if (a->degree <= b->degree) {
				tail->sibling = a;
				a = a->sibling;
			} else {
				tail->sibling = b;
				b = b->sibling;
			}
			tail = tail->sibling;
		}

		tail->sibling = a ? a : b;

		return newHead;
	}

	void unioni(BinomialHeap *newHeap) {

		head = unionHeaps(head, newHeap->head);
		BinHeapNode* prev = nullptr;
		BinHeapNode* curr = head;
		BinHeapNode* next = head->sibling;

		while (next) {
			if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)) {
				prev = curr;
				curr = next;
			} else {
				if (curr->key <= next->key) {
					curr->sibling = next->sibling;
					curr = mergeTrees(curr, next);
				} else {
					if (!prev) {
						head = next;
					} else {
						prev->sibling = next;
					}
					next = mergeTrees(next, curr);
					curr = next;
				}
			}
			next = curr->sibling;
		}
	}

	BinHeapNode* findNode(BinHeapNode* node, int key) {
		if (!node) return nullptr;

		if (node->key == key) return node;

		BinHeapNode* foundNode = findNode(node->child, key);
		if (foundNode) return foundNode;

		return findNode(node->sibling, key);
	}



	int getMin() {
		BinHeapNode* minNode = findMinNode();
		return minNode ? minNode->key : INT_MIN;
	}

	void extractMin() {
		if (!head) return;

		BinHeapNode* minNode = findMinNode();
		BinHeapNode* prevMin = nullptr;
		BinHeapNode* curr = head;

		while (curr->sibling && curr->sibling != minNode) {
			curr = curr->sibling;
		}

		if (curr->sibling == minNode) {
			prevMin = curr;
		}

		if (prevMin) {
			prevMin->sibling = minNode->sibling;
		} else {
			head = minNode->sibling;
		}

		BinHeapNode* child = minNode->child;
		BinHeapNode* newHead = nullptr;
		while (child) {
			BinHeapNode* next = child->sibling;
			child->sibling = newHead;
			child->parent = nullptr;
			newHead = child;
			child = next;
		}

		BinomialHeap* tempHeap = new BinomialHeap();
		tempHeap->head = newHead;
		unioni(tempHeap);

		delete minNode;
	}


	void decreaseKey(int oldKey, int newKey) {
		if (newKey > oldKey) {
			cout << "New key is greater than current key" << endl;
			return;
		}

		BinHeapNode* node = findNode(head, oldKey);
		if (!node) {
			cout << "Node with key " << oldKey << " not found." << endl;
			return;
		}

		node->key = newKey;
		BinHeapNode* parent = node->parent;

		while (parent && node->key < parent->key) {
			swap(node->key, parent->key);
			node = parent;
			parent = parent->parent;
		}
	}


	void deleteNode(int key) {
		BinHeapNode* node = findNode(head, key);
		if (!node) {
			cout << "Node with key " << key << " not found." << endl;
			return;
		}
		decreaseKey(key, INT_MIN);
		extractMin();
	}

	void printTree(BinHeapNode* node) {
		if (node == nullptr) return;

		queue<BinHeapNode*> q;
		q.push(node);

		while (!q.empty()) {
			BinHeapNode* curr = q.front();
			q.pop();

			cout << "Key: " << curr->key << ", Degree: " << curr->degree;

			if (curr->parent) {
				cout << ", Parent: " << curr->parent->key;
			} else {
				cout << ", Parent: None";
			}

			if (curr->sibling) {
				cout << ", Sibling: " << curr->sibling->key;
			} else {
				cout << ", Sibling: None";
			}

			if (curr->child) {
				cout << ", Child: " << curr->child->key;
				q.push(curr->child);
			} else {
				cout << ", Child: None";
			}

			cout << endl;

			if (curr->child) {
				BinHeapNode* child = curr->child->sibling;
				while (child) {
					q.push(child);
					child = child->sibling;
				}
			}
		}
	}

	void printHeap() {
		if (!head) {
			cout << "Heap is empty" << endl;
			return;
		}

		cout << "Heap:\n";
		BinHeapNode* curr = head;
		while (curr) {
			cout << "Binomial Tree, B" << curr->degree << ":\n";
			printTree(curr);
			curr = curr->sibling;
		}
	}
};

int main() {


	BinomialHeap heap;
	BinomialHeap *heap1 = new BinomialHeap();
	BinomialHeap *heap2 = new BinomialHeap();


	heap1->insert(10);
	heap1->insert(9);
	heap1->insert(11);
	heap1->insert(2);
	heap1->insert(7);
	heap1->insert(4);
	heap1->insert(8);

	heap2->insert(3);
	heap2->insert(6);
	heap2->insert(14);

	cout << "Heap 1 elements \n";
	heap1->printHeap();
	cout << endl;

	cout << "Heap 2 elements \n";
	heap2->printHeap();

	cout << endl;
	heap1->unioni(heap2);

	cout << "Heaps after union\n";

	heap1->printHeap();

	cout << "\n Considering the operations after merging the heap\n";

	while (1) {
		int ch;
		cout << "\n1. Insert a element to heap \n2. Delete an element from heap\n3. Minimum\n4. Extract Min\n5. Structure Of Tree\n6. Decrease Key\n7. Exit\n";
		cout << "Select an operation: ";
		cin >> ch;
		int n;

		switch (ch) {
		case 1: {
			cout << "Enter node to be inserted: ";
			cin >> n;
			heap.insert(n);
			break;
		}

		case 2: {
			cout << "Enter node to be deleted: ";
			cin >> n;
			heap.deleteNode(n);
			break;
		}

		case 3:
			cout << "Minimum: " << heap.getMin() << endl;
			break;
		case 4:
			heap.extractMin();
			cout << "Minimum Node is deleted\n";
			break;
		case 5: {
			cout << "Configuration of Heap is as follows : \n";
			heap.printHeap();
			break;
		}

		case 6: {
			int oldKey, newKey;
			cout << "Enter the element and its updated key : ";
			cin >> oldKey >> newKey;
			heap.decreaseKey(oldKey, newKey);
			break;
		}
		case 7:
			cout << "Thank you" << endl;
			return 0;
		default:
			cout << "Invalid" << endl;
		}
	}

}