#include <iostream>
#include <limits>
#include "GameList.h"
#include "Member.h"
#include "Administrator.h"

using namespace std;

void displaymemberchoices() {
    cout << "\n--- Borrowing Application ---\n";
    cout << "1. Borrow Game\n";
    cout << "2. Return Game\n";
    cout << "3. Display Borrowed Games\n";
    cout << "4. Display all games \n";
    cout << "0. Back to Main Menu\n"; // Changed from Exit to Back
    cout << "Enter choice: ";
}

void displayadminchoices() {
    cout << "\n--- Admin Menu ---\n";
    cout << "1. Add Game\n";
    cout << "2. Remove Game\n";
    cout << "3. Add a Member\n";
	cout << "4. Dispay all members\n";
    cout << "5. Display Borrowed Games\n";
	cout << "6. Display all games \n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter choice: ";
}

void displayUserMenu() {
    cout << "\n--- User Menu ---\n";
    cout << "1. Admin \n";
    cout << "2. Member\n";
    cout << "0. Exit Program\n";
    cout << "Enter choice: ";
}

int main() {
    GameList games;
    games.loadCSV("games.csv");

    // Create a Member
    Member member("M001", "John Doe", "123-456-7890");

	Administrator admin;

    GameNode* gameHead = nullptr;
    MemberNode* memberHead = nullptr;

    int choice;
    do {
        displayUserMenu();
        if (!(cin >> choice)) { // Simple input validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            // === NESTED LOOP FOR ADMIN MENU ===
            int adminChoice;
            do {
                displayadminchoices();
                if (!(cin >> adminChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (adminChoice) {
                case 1: {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    admin.addGame(games);
                    break;
                }
                case 2: {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    admin.removeGame(games);
                    break;
                }
                case 3: {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    admin.addMember(memberHead);
                    break;
                }
                case 4: {
                    if (!memberHead) {
                        cout << "(No members registered)\n";
                    }
                    else {
                        MemberNode* curr = memberHead;
                        while (curr) {
                            cout << "ID: " << curr->data->getID()
                                << " , Name: " << curr->data->getName()
                                << endl;
                            curr = curr->next;
                        }
                    }
                    break;
                }
                case 5: {
                    admin.displayBorrowSummary(memberHead);
                    break;
                }
                case 6: {
                    games.displayGames();
                    cout << "number of games: " << games.countGames() << endl;
                    break;
                }
                case 0:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (adminChoice != 0);
            break;
        }
        case 2: {
            int memberChoice;
            // === NESTED LOOP FOR MEMBER MENU ===
            do {
                displaymemberchoices();
                if (!(cin >> memberChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (memberChoice) {
                case 1: {
                    cout << "Enter the name of the game to borrow: ";
                    string gameName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, gameName);

                    if (!gameName.empty()) {
                        GameNode* game = games.searchAVL(gameName);
                        if (game) {
                            member.borrowGame(game);
                        }
                        else {
                            cout << "Game not found in library.\n";
                        }
                    }
                    else {
                        cout << "No game name entered.\n";
                    }
                    break;
                }
                case 2: {
                    cout << "Enter the name of the game to return: ";
                    string gameName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, gameName);

                    if (!gameName.empty()) {
                        member.returnGame(gameName);
                    }
                    else {
                        cout << "No game name entered.\n";
                    }
                    break;
                }
                case 3:
                    member.printBorrowedGames();
                    break;
                case 4:
                    games.displayGames();
                    cout << "number of games: " << games.countGames() << endl;
                    break;
                case 0:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (memberChoice != 0);
            // === END NESTED LOOP ===
            break; // Break out of Case 2 (back to main menu)
        }
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}