#ifndef ADMINISTRATOR_H

#endif // !ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Dictionary.h"
#include "LinkedList.h"
#include "Member.h"
using namespace std;
static const string GAME_CSV = "games.csv";
static const string ADMIN_LOG = "Report.txt";

class Administrator {
public:
    // Game management
    void addGame(Dictionary& games);
    void removeGame(Dictionary& games);

    // Member management
    void addMember(LinkedList& members);
    void removeMember(LinkedList& members);

    // Reports
    void displayBorrowSummary(Dictionary& games);
   

};  