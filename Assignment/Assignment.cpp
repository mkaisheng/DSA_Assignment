#include <iostream>
#include <limits>
#include "GameList.h"
#include "Member.h"

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
            cout << "Admin functionality not implemented yet.\n";
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