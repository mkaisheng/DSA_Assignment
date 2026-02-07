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

    void addGame(GameList& games);

    void removeGame(GameList& games);


    void addMember(MemberNode*& memberHead);
    void removeMember(MemberNode*& memberHead);


    void displayAllGames(GameList& games);
    void displayBorrowSummary(MemberNode* memberHead);
};

#endif 