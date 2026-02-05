#include <iostream>
#include <limits>
#include "Administrator.h"
#include "Dictionary.h"
#include "LinkedList.h"

using namespace std;

int main() {
    Dictionary games;
    LinkedList members;
    Administrator admin;
	Member member("M001", "John Doe", "123-456-7890");

    // Load games at start
    games.LoadCSV("games.csv");

    int choice;

    do {
        cout << "\n=== Board Game Library System ===\n";
        cout << "1. Administrator\n";
        cout << "2. Memeber\n";
        cout << "3. Search Game\n";
        cout << "4. Display Game Based On Number Of Players\n";
		cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            int aChoice;
            do {
                cout << "\n--- Administrator Menu ---\n";
                cout << "1. Add Game\n";
                cout << "2. Remove Game\n";
                cout << "3. Add Member\n";
                cout << "4. Display Borrow/Return Summary\n";
                cout << "0. Back to Main Menu\n";
                cout << "Enter choice: ";
                cin >> aChoice;

                switch (aChoice) {
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
                    admin.displayBorrowSummary(games);
                    break;
                case 0:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (aChoice != 0);
            break;
        }
        case 2:
        {
            int mChoice;
            do {
                cout << "\n--- Member Menu ---\n";
                cout << "1. Borrow Game\n";
                cout << "2. Return Game\n";
                cout << "3. Display Borrow/Return Summary\n";
                cout << "0. Back to Main Menu\n";
                cout << "Enter choice: ";
                cin >> mChoice;

                switch (mChoice) {
                case 1: {
                    cout << "Enter the name of the game to borrow: ";
                    string gameName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, gameName);
                    if (!gameName.empty()) {
                        member.borrowGame(games, gameName);
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
                        member.returnGame(games, gameName);
                    }
                    else {
                        cout << "No game name entered.\n";
                    }
                    break;
                }
                case 3:
                    member.printBorrowedGames();
                    break;
                case 0:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (mChoice != 0);
            break;
        }
        case 3: {
            cout << "Enter game name to search: ";
            string gameName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, gameName);
            games.search(gameName);
            break;
		}
        case 4: {
            int numPlayers;
            cout << "Enter number of players: ";
            cin >> numPlayers;
			games.displayGamesByPlayers(numPlayers);
            break;
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


