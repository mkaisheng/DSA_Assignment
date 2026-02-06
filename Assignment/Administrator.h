#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <iostream>
#include "GameList.h" 
#include "Member.h"   

using namespace std;

static const string GAME_CSV = "games.csv";
static const string ADMIN_LOG = "Report.txt";

// Define a Node for the list of Members
struct MemberNode {
    Member* data;      // Pointer to the Member object
    MemberNode* next;  // Pointer to the next member node
};

class Administrator {
public:
    // === Game Management ===
    // We pass the pointer by reference (GameNode*&) so the Admin can change the real head
    void addGame(GameNode*& gameHead);

    // Remove a game from the master list
    void removeGame(GameNode*& gameHead);


    // === Member Management ===
    // We pass the head of the Member list
    void addMember(MemberNode*& memberHead);

    void removeMember(MemberNode*& memberHead);


    // === Reports ===
    // Displays all games currently in the system
    void displayAllGames(GameNode* gameHead);

    // Displays which members have borrowed which games
    void displayBorrowSummary(MemberNode* memberHead);
};

#endif // !ADMINISTRATOR_H