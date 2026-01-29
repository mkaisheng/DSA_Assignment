#include "LinkedList.h"

LinkedList::LinkedList() {
	head = nullptr;
}

LinkedList::~LinkedList() {
	clear();
}

void LinkedList::insert(string value) {
	ListNode* newNode = new ListNode();
	newNode->value = value;
	newNode->next = head;
	head = newNode;
}

bool LinkedList::search(string value) {
	ListNode* current = head;
	while (current != nullptr) {
		if (current->value == value) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void LinkedList::remove(string value) {
	if (head == nullptr) return;

	if (head->value == value) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
		return;
	}

	ListNode* current = head;
	while (current->next != nullptr) {
		if (current->next->value == value) {
			ListNode* temp = current->next;
			current->next = current->next->next;
			delete temp;
			return;
		}
		current = current->next;
	}
}

void LinkedList::clear() {
	ListNode* current = head;
	while (current != nullptr) {
		ListNode* temp = current;
		current = current->next;
		delete temp;
	}
	head = nullptr;
}

void LinkedList::printList() {
	ListNode* current = head;
	while (current != nullptr) {
		cout << current->value << " -> ";
		current = current->next;
	}
	cout << "nullptr" << endl;
}

