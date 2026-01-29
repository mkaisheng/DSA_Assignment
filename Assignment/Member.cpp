#include "Member.h"

Member::Member(string id, string n, string phone) {
	memberID = id;
	name = n;
	phoneNumber = phone;
}

string Member::getID() {
	return memberID;
}

string Member::getName() {
	return name;
}

void Member::borrowGame(Dictionary dict, string gameName) {
	if (dict.borrowGame(gameName, memberID)) {
		borrowedGames.insert(gameName);
		cout << name << " successfully borrowed " << gameName << "." << endl;
	}
	else {
		cout << gameName << " is not available for borrowing." << endl;
	}
}

void Member::returnGame(Dictionary dict, string gameName) {
	if (dict.returnGame(gameName, memberID)) {
		borrowedGames.remove(gameName);
		cout << name << " successfully returned " << gameName << "." << endl;
	}
	else {
		cout << name << " did not borrow " << gameName << "." << endl;
	}
}

void Member::printBorrowedGames() {
	borrowedGames.printList();
}



