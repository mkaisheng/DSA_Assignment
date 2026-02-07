#ifndef MEMBER_H

#define MEMBER_H
#include <string>
using namespace std;

// Forward declaration
class GameList;
struct GameNode;

class Member {
private:
    string memberID;
    string name;
    string phoneNumber;
    GameNode* borrowedHead;  // Head of member's borrowed games list

public:
    Member(string id, string n, string phone);
    ~Member();

    string getID() const;
    string getName() const;

    // Borrow and return operations
    void borrowGame(GameNode* game);
    void returnGame(const string& gameName, GameList* gameList);

    // Display
    void printBorrowedGames();
};

#endif