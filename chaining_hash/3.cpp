// �̹� ������ ���� hashMap�� ��� ��, map<String type, int count>�� 
// hash map<int type_key, int count>���� �����Ͽ� ������ Ǫ�� ����.
// ü�̴� �ؽô� key�ߺ��� ����ϹǷ�, key�ߺ��� ��� ���� ������ ��(strcmp)�� �ʿ��ϴ�.

/* �׵��� char copy �ڵ� �Ǽ��� �־ ������
	while (*a++ != 0) length++;
	ret = new char[length + 1];
	a -= length+1; // while loop���� a++�� �ѹ� �̻� �׻� ������
*/

#include<iostream>
#include<vector>
#include<map>
using namespace std;

typedef unsigned long long int ULLINT;

char* mystrcpy(const char* a) {
	char* ret = nullptr;
	int length = 0;
	while (*a++ != 0) length++;
	ret = new char[length + 1];
	a -= length+1;
	for (int i = 0; i < length; i++) {
		ret[i] = a[i];
	}
	ret[length] = 0;
	return ret;
}

bool mystrcmp(const char* src, const char* dest) {
	int sLength = 0;
	int dLength = 0;
	while (*src++ != 0) sLength++;
	while (*dest++ != 0) dLength++;
	src -= sLength+1;
	dest -= dLength+1;

	if (sLength != dLength) return false;

	for (int i = 0; i < sLength; i++)
	{
		if (src[i] != dest[i]) return false;
	}
	return true;
}

class Node {
public:
	const char* name;
	ULLINT count;
	Node* next;

	Node() : name(nullptr), count(0UL), next(nullptr) {

	}

	Node(const char* n) : Node() {
		name = mystrcpy(n);
	}

};

class ChainingHashMap {
public:
	Node* mHead;
	ULLINT mSize;
	ChainingHashMap(ULLINT sz) : mSize(sz) {
		mHead = new Node[mSize];
	}

	void insertNCount(const char* c) {
		ULLINT key = hashCode(c);
		Node* n = mHead[key].next;

		// searches data and count.
		while (n) {
			if (mystrcmp(c, n->name)) {
				n->count++;
				return;
			}
			n = n->next;
		}

		// no data found. creates new node.
		Node* newNode = new Node(c);
		newNode->next = mHead[key].next;
		newNode->count++;
		mHead[key].next = newNode;
	}

	int getAns() {
		int ret = 1;
		for (int i = 0; i < mSize; i++) {
			Node* n = mHead[i].next;
			while (n) {
				ret *= n->count + 1UL;
				n = n->next;
			}
		}
		return ret - 1;
	}

	ULLINT hashCode(const char* data) {
		ULLINT ret = 0UL;

		while (*data != 0) {
			ret = (ret << 3) + *data++;
		}
		return ret % mSize;
	}
};

int solution(vector<vector<string>> clothes) {
	int answer = 1;
	ChainingHashMap map(90);
	for (vector<vector<string>>::iterator it = clothes.begin(); it != clothes.end(); it++)
	{
		string type = it->at(1);
		map.insertNCount(type.c_str());
	}
	return map.getAns();
}


int main(void) {
	vector<vector<string>> input;
	for (int i = 0; i < 3; i++) {
		string a, b;
		cin >> a >> b;
		vector<string> in;
		in.push_back(a);
		in.push_back(b);
		input.push_back(in);
	}
	cout << solution(input);
	return 0;
}