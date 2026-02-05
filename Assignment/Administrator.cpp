#include "Administrator.h"

void Administrator::addGame(Dictionary& games) {
    string name;
    int minP, maxP, minT, maxT, year;

    cin.ignore();
    cout << "Enter game name: ";
    getline(cin, name);

    cout << "Min players: ";
    cin >> minP;
    cout << "Max players: ";
    cin >> maxP;
    cout << "Min playtime: ";
    cin >> minT;
    cout << "Max playtime: ";
    cin >> maxT;
    cout << "Year published: ";
    cin >> year;

    games.insert(name, minP, maxP, minT, maxT, year);
    games.saveToCSV(GAME_CSV);
    cout << "Game added successfully.\n";
}

void Administrator::removeGame(Dictionary& games) {
    string name;

    cin.ignore();
    cout << "Enter game name to remove: ";
    getline(cin, name);

    if (games.remove(name)) {
        games.saveToCSV(GAME_CSV);
        cout << "Game removed successfully.\n";
    }
    else {
        cout << "Game not found.\n";
    }
}


void Administrator::addMember(LinkedList& members) {
    string id, name, phone;

    cin.ignore();
    cout << "Member ID: ";
    getline(cin, id);

    cout << "Name: ";
    getline(cin, name);
        
    cout << "Phone number: ";
    getline(cin, phone);

    // Only store ID in LinkedList
    members.insert(id);

    cout << "Member added successfully.\n";
}
void Administrator::removeMember(LinkedList& members) {
    string id;

    cin.ignore();
    cout << "Enter member ID to remove: ";
    getline(cin, id);

    if (members.search(id)) {
        members.remove(id);
        cout << "Member removed successfully.\n";
    }
}


void Administrator::displayBorrowSummary(Dictionary& games) {
    games.displayBorrowedGames();
}