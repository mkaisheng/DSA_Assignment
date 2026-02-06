#include "Administrator.h"
#include <iostream>

using namespace std;

/* =========================================================
   Add Game (to Master List)
   ========================================================= */
void Administrator::addGame(GameNode*& gameHead) {
    GameNode* newNode = new GameNode();

    cout << "Enter Game Name: ";
    getline(cin, newNode->name);
    cout << "Min Players: "; cin >> newNode->minPlayers;
    cout << "Max Players: "; cin >> newNode->maxPlayers;
    cout << "Min Time (min): "; cin >> newNode->minPlayTime;
    cout << "Max Time (min): "; cin >> newNode->maxPlayTime;
    cout << "Year: "; cin >> newNode->yearPublished;
    cin.ignore(); // Clear buffer

    // Insert at Head of Master List
    newNode->next = gameHead;
    gameHead = newNode;

    cout << ">> Game added successfully.\n";
}

/* =========================================================
   Remove Game (from Master List)
   ========================================================= */
void Administrator::removeGame(GameNode*& gameHead) {
    if (!gameHead) return;

    string target;
    cout << "Enter name of game to remove: ";
    getline(cin, target);

    GameNode* curr = gameHead;
    GameNode* prev = nullptr;

    while (curr && curr->name != target) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << ">> Game not found.\n";
        return;
    }

    if (!prev) {
        gameHead = curr->next; // Removing head
    }
    else {
        prev->next = curr->next; // Removing middle/tail
    }

    delete curr;
    cout << ">> " << target << " deleted from system.\n";
}

/* =========================================================
   Add Member (to Member List)
   ========================================================= */
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

/* =========================================================
   Remove Member
   ========================================================= */
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

/* =========================================================
   Display Helpers
   ========================================================= */
void Administrator::displayAllGames(GameNode* gameHead) {
    cout << "\n--- Library Inventory ---\n";
    while (gameHead) {
        cout << "- " << gameHead->name << " (" << gameHead->yearPublished << ")\n";
        gameHead = gameHead->next;
    }
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