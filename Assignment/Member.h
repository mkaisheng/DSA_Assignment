#include "Dictionary.h"
#include "LinkedList.h"
class Member
{
private:
	string memberID;
	string name;
	string phoneNumber;
	
	LinkedList borrowedGames;
public:
	Member(string id, string n, string phone);
	string getID();
	string getName();

	void borrowGame(Dictionary dict,string gameName);
	void returnGame(Dictionary dict, string gameName);
	void printBorrowedGames();
};

