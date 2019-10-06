// 입력 데이터가 고유한 값을 지향하는가? 사람이름. 전화번호 등
// 입력 데이터의 해싱이 용이한가? 각 데이터의 값이 크지 않다


// 의식의 흐름
// 입력 수가 100만이므로 해시사이즈는 300만개로 충분
// 데이터의 길이가 20개이므로 한 데이터당 20번의 서치O(1)를 해도 최악 데이터에 대해 최대 서치 비용은 2천만번이면 끝낼 수 있다.
// ULLINT는 64비트, 각 3비트 사용 해도 약 20%오차가 발생하나 모든 데이터 구분이 가능하고 중복이 잘 없는 데이터

// 코드 짜다보면서 발견한 것
// prefix 및 input data 들을 저장하다보니 해시되는 양이 최악 100만*20 = 2천만개까지 발생하므로, 해시테이블 사이즈(6천만?)가 클 수록 좋아짐.

#include <string>
#include <vector>
#include<iostream>

using namespace std;
typedef unsigned long long int ULLINT;

inline bool IsEqual(const char* a, const char* b) {
	int aLength = 0;
	int bLength = 0;
	while (*a++ != '\0') aLength++;
	while (*b++ != '\0') bLength++;
	if (aLength != bLength) return false;

	a -= aLength;
	b -= bLength;
	
	for (int i = 0; i < aLength; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

class Node {
public:
	char* data;
	Node* next;
	bool isPrefix;
	Node() : data(0), next(nullptr), isPrefix(true) {

	}
	Node(const char* in, const int& length) {
		data = new char[length+1];
		for (int i = 0; i < length; i++)
			data[i] = in[i];
		data[length] = '\0';
		next = nullptr;
		isPrefix = true;
	}
	//delete data, next
};

class HashTable {
public:
	Node* head;
	
	HashTable(int sz) : MAX_SIZE(sz) {
		head = new Node[sz];
	}

	// check prefix and insert the node
	bool checkAndInsert(const char* data) {
		int length = 0;
		const char* d = data;
		while (*d++ != '\0') length++;
		
		// check whether it is prefix of others or not.
		// 123
		// 12 // true
		if (searchPrefix(data)) return false;
		insert(data, length, false); // put real data, not as prefix.


		// mark all sub-prefixes
		for (int i = 1; i < length; i++)
		{
			// TODO search함수를 재사용
			ULLINT key = hashCodeOf(data, i);
			Node* newNode = new Node(data, i);
			// search sub prefix each
			Node*& n = head[key].next;
			bool exist = false;
			while (n) {
				if (IsEqual(newNode->data, n->data)) {
					exist = true;
					if (n->isPrefix) {
						break; // have already identical prefix. nothing to do.
					}
					else {
						// there is a prefix of the this word.
						// 12
						// 123 // 12 is exists.
						delete newNode;
						return false; 
					}
				}
				n = n->next;
			} 
			if (!exist)
			{// no prefix data. lets input the prefix.

				insert(data, i);
			}
		}
		return true;
	}

	void insert(const char* data, int len, bool isPrefix = true) {
	
		ULLINT key = hashCodeOf(data, len);
		Node*& next = head[key].next;
		Node* newNode = new Node(data, len);
		newNode->next = next;
		newNode->isPrefix = isPrefix;
		next = newNode;
	}

	bool searchPrefix(const char* data) {
		int length = 0;
		const char* d = data;
		while (*d++ != '\0') length++;
		ULLINT key = hashCodeOf(data, length);
		Node*& n = head[key].next;
		while (n) { // exist?
			// check data
			if (IsEqual(data, n->data)) {
				if (n->isPrefix)
					return true;
			}
			n = n->next;
		}
		return false;
	}

	inline ULLINT hashCodeOf(const char*& data, const int& length) {
		ULLINT key = 0;
		const char* iter = data;
		for (int i = 0; i < length; i++) {
			key = (key << 3) + *iter++;
		}
		return key % MAX_SIZE;
	}

	void print() {
		for (int i = 0; i < MAX_SIZE; i++) {
			Node* n = head[i].next;
			int cnt = 0;
			while (n) {
				cout << " -> " << n->data;
				n = n->next;
				cnt++;
			}
			if (cnt > 0) cout << endl;
		}
	}
public:
	int MAX_SIZE;
};

bool solution(vector<string> phone_book) {
	bool answer = true;
	typedef vector<string>::iterator It;
	HashTable tb(40000001);
	for (It it = phone_book.begin(); it != phone_book.end(); it++) {
		const char* n = it->c_str();
		tb.checkAndInsert(n);
	}
	return answer;
}


// local test
int main(void) {
	HashTable tb(4000001);
	for (int i = 0; i < 10; i++) {
		char c[20]{'\0', };
		cin >> c;
		cout << tb.checkAndInsert(c);
		tb.print();
	}
	return 0;
}