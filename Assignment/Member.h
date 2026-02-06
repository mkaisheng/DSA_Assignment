#ifndef MEMBER_H // 1. Guard starts here
#define MEMBER_H

#include <string>
#include <iostream>
#include "GameList.h"

using namespace std;

class Member {
private:
    string memberID;
    string name;
    string phoneNumber;

    GameNode* borrowedHead;

public:
    // Constructor
    Member(string id, string n, string phone);

    // Getters
    string getID() const;
    string getName() const;

   
	void borrowGame(GameNode* game);

    // We return the game, removing it from 'borrowedHead'
    void returnGame(string gameName);

    // Display the list of games this member has
    void printBorrowedGames();
};

#endif // !MEMBER_H  // 2. Guard ends here