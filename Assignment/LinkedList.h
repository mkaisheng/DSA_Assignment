
#include <string>
#include <iostream>

using namespace std;

struct ListNode {
	string value;
	ListNode* next;
};

class LinkedList
{
private:
	ListNode* head;
public:
	LinkedList();
	~LinkedList();
	void insert(string value);
	bool search(string value);
	void remove(string value);
	void clear();
	void printList();
};

