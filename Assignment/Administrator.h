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
	// We pass the GameList by reference
    void addGame(GameList& games);

    // Remove a game from the master list
    void removeGame(GameList& games);


    // === Member Management ===
    // We pass the head of the Member list
    void addMember(MemberNode*& memberHead);

    void removeMember(MemberNode*& memberHead);


    // === Reports ===
    // Displays all games currently in the system
    void displayAllGames(GameList& games);

    // Displays which members have borrowed which games
    void displayBorrowSummary(MemberNode* memberHead);
};

#endif // !ADMINISTRATOR_H