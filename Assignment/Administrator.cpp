#include "Administrator.h"
#include <iostream>

using namespace std;

//add game
void Administrator::addGame(GameList& games) {
    GameNode* newNode = new GameNode();

    cout << "Enter Game Name: ";
    getline(cin, newNode->name);
    cout << "Min Players: "; cin >> newNode->minPlayers;
    cout << "Max Players: "; cin >> newNode->maxPlayers;
    cout << "Min Time (min): "; cin >> newNode->minPlayTime;
    cout << "Max Time (min): "; cin >> newNode->maxPlayTime;
    cout << "Year: "; cin >> newNode->yearPublished;
    cin.ignore(); // Clear buffer

    games.insertGame(newNode);

    cout << ">> Game added successfully.\n";
}


//Remove Game (from Master List)

void Administrator::removeGame(GameList& games) {

    string target;
    cout << "Enter name of game to remove: ";
    getline(cin, target);
    games.removeGame(target);
    cout << ">> " << target << " deleted from system.\n";
}


 //Add Member (to Member List)
void Administrator::addMember(MemberNode*& memberHead) {
    string id, name, phone;

    cout << "Enter Member ID: "; getline(cin, id);
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Phone: "; getline(cin, phone);

    // Create the Member Object
    Member* newMemberObj = new Member(id, name, phone);

    // Create the List Node wrapper
    MemberNode* newNode = new MemberNode();
    newNode->data = newMemberObj;
    newNode->next = memberHead; // Insert at front

    memberHead = newNode;
    cout << ">> Member " << name << " registered.\n";
}

//remove member
void Administrator::removeMember(MemberNode*& memberHead) {
    if (!memberHead) return;

    string id;
    cout << "Enter Member ID to remove: ";
    getline(cin, id);

    MemberNode* curr = memberHead;
    MemberNode* prev = nullptr;

    while (curr && curr->data->getID() != id) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << ">> Member not found.\n";
        return;
    }

    if (!prev) {
        memberHead = curr->next;
    }
    else {
        prev->next = curr->next;
    }

    // Clean up memory
    delete curr->data; // Delete the Member object
    delete curr;       // Delete the Node wrapper
    cout << ">> Member removed.\n";
}

void Administrator::displayAllGames(GameList& games) {
    cout << "\n--- Library Inventory ---\n";
    games.displayGames();
}

void Administrator::displayBorrowSummary(MemberNode* memberHead) {
    cout << "\n=== BORROWING REPORT ===\n";
    while (memberHead) {
        cout << "Member: " << memberHead->data->getName() << "\n";
        memberHead->data->printBorrowedGames();
        cout << "------------------------\n";
        memberHead = memberHead->next;
    }
}