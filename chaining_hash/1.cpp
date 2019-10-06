#include<iostream>
#include<string>
using namespace std;

struct Node {
	string data;
	Node* next;
	Node(string& in) : next(NULL) {
		data = in;
	}
	Node() : next(NULL) {
		
	}
};

class HashTable {
public:
	typedef unsigned long long int INT_KEY;
	HashTable(int key_size) : mKeySize(key_size) {
		mTable = new Node[mKeySize];
	}

	~HashTable() {
		delete[] mTable;
	}

	void insert(string& data) {
		INT_KEY key = hashFunc(data);
		Node* newNode = new Node(data);
		newNode->next = mTable[key].next;
		mTable[key].next = newNode;
	}

	void remove(string& data) {
		INT_KEY key = hashFunc(data);
		Node* n = mTable[key].next;
		Node* prev = &mTable[key];
		while (n != NULL) { // head node.
			if (n->data == data) {
				prev->next = n->next;
				delete n;
				return;
			}
			prev = n;
			n = n->next;
		}
	}

	void print() {
		for (int i = 0; i < mKeySize; i++) {
			Node* n = mTable[i].next;
			if (n == NULL) continue;

			while (n != NULL) {
				cout << "-> " << n->data;
				n = n->next;
			}
			cout << endl;
		}
	}

	string getAns() {
		for (int i = 0; i < mKeySize; i++) {
			Node* n = mTable[i].next;
			
			if (n != NULL) {
				return n->data;
			}
		}
	}

	INT_KEY hashFunc(string& data) {
		INT_KEY key = 0; // 4 byte, 32 bit
		const char* iter = data.c_str();  // <= int 25
		int t = 0;
		while (*iter != '\0')
		{
			// sampling
			if (t & 1)
				key = (key << 4) + (char)(*iter);
			else
				key = (key << 3) + (char)(*iter);

			iter++;
			t++;
		}

		return key % mKeySize;
	}
public:
	Node* mTable;
	const int mKeySize;
};


#include<vector>
int main(void) {
	HashTable table(300000);
	vector<string> input;
	
	vector<string>::iterator it;
	for (it = input.begin(); it != input.end(); it++) {
		table.insert(*it);
		cout << *it;
	}
	return 0;
}