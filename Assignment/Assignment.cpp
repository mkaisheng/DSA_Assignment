
#include <iostream>
#include "Administrator.h"
#include "Dictionary.h"
#include "LinkedList.h"

using namespace std;

int main() {
    Dictionary games;
    LinkedList members;
    Administrator admin;

    // Load games at start
    games.LoadCSV("games.csv");

    int choice;

    do {
        cout << "\n=== Board Game Library System ===\n";
        cout << "1. Add Game\n";
        cout << "2. Remove Game\n";
        cout << "3. Add Member\n";
        cout << "4. Remove Member\n";
        cout << "5. Display Borrow Summary\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            admin.addGame(games);
            break;
        case 2:
            admin.removeGame(games);
            break;
        case 3:
            admin.addMember(members);
            break;
        case 4:
            admin.removeMember(members);
            break;
        case 5:
            admin.displayBorrowSummary(games);
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}


