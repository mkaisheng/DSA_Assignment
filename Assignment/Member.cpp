#include "Member.h"
#include "GameList.h" 
#include <iostream>

using namespace std;

// Constructor
Member::Member(string id, string n, string phone) {
    this->memberID = id;
    this->name = n;
    this->phoneNumber = phone;
    this->borrowedHead = nullptr;
}

string Member::getID() const { return memberID; }
string Member::getName() const { return name; }

/* =========================================================
   Borrow Game
   Uses GameList::searchAVL (Fast Search)
   Uses GameList::insertGame (To add to member's list)
   ========================================================= */
void Member::borrowGame(GameNode* game) {

    if (!game) {
        cout << "Error: Game not found.\n";
        return;
    }

    if (game->isBorrowed) {
        cout << "Error: Game already borrowed.\n";
        return;
    }

    // Mark game as borrowed
    game->isBorrowed = true;
    game->borrowedBy = memberID;

    // Add to member's borrowed list (simple linked list insert)
    game->next = borrowedHead;
    borrowedHead = game;

    cout << "Success: " << name << " borrowed " << game->name << ".\n";
}
/* =========================================================
   Return Game
   Uses GameList::removeGame
   ========================================================= */
void Member::returnGame(string gameName) {

    GameNode* curr = borrowedHead;
    GameNode* prev = nullptr;

    while (curr && curr->name != gameName) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Error: " << name << " does not have '" << gameName << "'.\n";
        return;
    }

    // Remove from member list
    if (!prev)
        borrowedHead = curr->next;
    else
        prev->next = curr->next;

    // Mark as returned
    curr->isBorrowed = false;
    curr->borrowedBy = "";
    curr->next = nullptr;

    cout << "Success: " << gameName << " returned.\n";
}


void Member::printBorrowedGames() {
    cout << "Games borrowed by " << name << ":\n";

    if (!borrowedHead) {
        cout << "(None)\n";
        return;
    }

    GameNode* curr = borrowedHead;
    while (curr) {
        cout << "- " << curr->name << "\n";
        curr = curr->next;
    }
    cout << "------------------------\n";
}