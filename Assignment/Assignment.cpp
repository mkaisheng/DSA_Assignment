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
    cout << "4. Display all games\n";
    cout << "5. Record a Played Game\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter choice: ";
}

void displayadminchoices() {
    cout << "\n--- Admin Menu ---\n";
    cout << "1. Add Game\n";
    cout << "2. Remove Game\n";
    cout << "3. Add a Member\n";
    cout << "4. Display all members\n";
    cout << "5. Display Borrowed Games\n";
    cout << "6. Display all games\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter choice: ";
}

void displayUserMenu() {
    cout << "\n--- User Menu ---\n";
    cout << "1. Admin\n";
    cout << "2. Member\n";
	cout << "3. Search for a Game\n";
    cout << "0. Exit Program\n";
    cout << "Enter choice: ";
}
void displaySortMenu() {
    cout << "\n--- Sort Games By ---\n";
    cout << "1. Name (A-Z)\n";
    cout << "2. Minimum Players\n";
    cout << "3. Maximum Players\n";
    cout << "4. Year Published\n";
    cout << "0. Cancel\n";
    cout << "Enter choice: ";
}

int main() {
    // Load game library
    GameList games;
    games.loadCSV("games.csv");

    // Create administrator
    Administrator admin;

    // Member list (linked list of members)
    MemberNode* memberHead = nullptr;

    // Currently active member (for member menu)
    Member* activeMember = nullptr;

    int choice;
    do {
        displayUserMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            // === ADMIN MENU ===
            int adminChoice;
            do {
                displayadminchoices();
                if (!(cin >> adminChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }

                switch (adminChoice) {
                case 1: {
                    // Add Game
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    admin.addGame(games);
                    break;
                }
                case 2: {
                    // Remove Game
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    admin.removeGame(games);
                    break;
                }
                case 3: {
                    // Add Member
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    admin.addMember(memberHead);
                    break;
                }
                case 4: {
                    // Display all members
                    if (!memberHead) {
                        cout << "(No members registered)\n";
                    }
                    else {
                        cout << "\n--- Registered Members ---\n";
                        MemberNode* curr = memberHead;
                        int count = 1;
                        while (curr) {
                            if (curr->data) {  // Check if member data exists
                                cout << count << ". ID: " << curr->data->getID()
                                    << ", Name: " << curr->data->getName() << endl;
                            }
                            curr = curr->next;
                            count++;
                        }
                    }
                    break;
                }
                case 5: {
                    // Display Borrowed Games Summary
                    admin.displayBorrowSummary(memberHead);
                    break;
                }
                case 6: {
                    displaySortMenu();

                    int sortChoice;
                    cin >> sortChoice;

                    switch (sortChoice) {
                    case 1:
                        games.mergeSort(SortMode::NAME);
                        break;
                    case 2:
                        games.mergeSort(SortMode::MIN_PLAYERS);
                        break;
                    case 3:
                        games.mergeSort(SortMode::MAX_PLAYERS);
                        break;
                    case 4:
                        games.mergeSort(SortMode::YEAR);
                        break;
                    case 0:
                        cout << "Showing current order.\n";
                        break;
                    default:
                        cout << "Invalid choice. Showing current order.\n";
                    }

                    cout << "\n--- Game Library ---\n";
                    games.displayGames();
                    cout << "\nTotal games: " << games.countGames() << endl;

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
            // === MEMBER MENU ===
            // First, check if any members exist
            if (!memberHead) {
                cout << "\nNo members registered. Please contact admin to create a member account.\n";
                break;
            }

            // Display member selection
            cout << "\n--- Select Your Account ---\n";
            MemberNode* curr = memberHead;
            int count = 1;
            while (curr) {
                if (curr->data) {  // Check if member data exists
                    cout << count << ". " << curr->data->getName()
                        << " (ID: " << curr->data->getID() << ")\n";
                    count++;
                }
                curr = curr->next;
            }

            // If no valid members found
            if (count == 1) {
                cout << "\nNo valid members registered. Please contact admin.\n";
                break;
            }

            cout << "Enter member number: ";

            int memberSelection;
            if (!(cin >> memberSelection) || memberSelection < 1 || memberSelection >= count) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid selection.\n";
                break;
            }

            // Find selected member
            curr = memberHead;
            int currentCount = 1;
            activeMember = nullptr;
            while (curr && currentCount <= memberSelection) {
                if (curr->data) {
                    if (currentCount == memberSelection) {
                        activeMember = curr->data;
                        break;
                    }
                    currentCount++;
                }
                curr = curr->next;
            }

            if (!activeMember) {
                cout << "Error: Could not find selected member.\n";
                break;
            }

            cout << "Logged in as: " << activeMember->getName() << endl;

            // Now show member menu
            int memberChoice;
            do {
                displaymemberchoices();
                if (!(cin >> memberChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }

                switch (memberChoice) {
                case 1: {
                    // Borrow Game
                    cout << "Enter the name of the game to borrow: ";
                    string gameName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, gameName);

                    if (!gameName.empty()) {
                        GameNode* game = games.searchAVL(gameName);
                        if (game) {
                            activeMember->borrowGame(game);
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
                    // Return Game
                    cout << "Enter the name of the game to return: ";
                    string gameName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, gameName);

                    if (!gameName.empty()) {
                        // FIXED: Now passes GameList pointer
                        activeMember->returnGame(gameName, &games);
                    }
                    else {
                        cout << "No game name entered.\n";
                    }
                    break;
                }
                case 3: {
                    // Display Borrowed Games
                    activeMember->printBorrowedGames();
                    break;
                }
                case 4: {
                    displaySortMenu();

                    int sortChoice;
                    cin >> sortChoice;

                    switch (sortChoice) {
                    case 1:
                        games.mergeSort(SortMode::NAME);
                        break;
                    case 2:
                        games.mergeSort(SortMode::MIN_PLAYERS);
                        break;
                    case 3:
                        games.mergeSort(SortMode::MAX_PLAYERS);
                        break;
                    case 4:
                        games.mergeSort(SortMode::YEAR);
                        break;
                    case 0:
                        cout << "Showing current order.\n";
                        break;
                    default:
                        cout << "Invalid choice. Showing current order.\n";
                    }

                    cout << "\n--- Game Library ---\n";
                    games.displayGames();
                    cout << "\nTotal games: " << games.countGames() << endl;

                }
                case 5: {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    string gameName;
                    cout << "Enter the name of the game you played: ";
                    getline(cin, gameName);

                    string participants;
                    cout << "Enter the IDs of all members who played (comma separated): ";
                    getline(cin, participants);

                    string winner;
                    cout << "Enter the ID of the winner: ";
                    getline(cin, winner);

                    // Append to recordgames.txt
                    activeMember->recordGamePlay(gameName, participants, winner);
                    break;
                }
                case 0:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (memberChoice != 0);
            break;
        }
        case 3: {
            cout << "Enter the name of the game to search: ";
            string gameName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, gameName);
            if (!gameName.empty()) {
                GameNode* game = games.searchAVL(gameName);
                string borrowed = "No";
                if (game) {
                    if (game->isBorrowed == 1)
                        borrowed = "Yes";
                    cout << "Name: " << game->name;
                    cout << "\nPlayers: " << game->minPlayers << " - " << game->maxPlayers;
                    cout << "\nPlay time: " << game->minPlayTime << " mins - " << game->maxPlayTime << " mins";
                    cout << "\nYear published: " << game->yearPublished;
                    cout << "\nBorrowed: " << borrowed;
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
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    // Cleanup member list
    MemberNode* curr = memberHead;
    while (curr) {
        MemberNode* next = curr->next;
        if (curr->data) {
            delete curr->data;  // Delete the Member object
        }
        delete curr;        // Delete the MemberNode
        curr = next;
    }

    return 0;
}