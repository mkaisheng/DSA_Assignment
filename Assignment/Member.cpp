#include "Member.h"
#include "GameList.h" 
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;

// Constructor
Member::Member(string id, string n, string phone) {
    this->memberID = id;
    this->name = n;
    this->phoneNumber = phone;
    this->borrowedHead = nullptr;
}

string Member::getID() const { return memberID; }
string Member::getName() const { return name; }

//helper: get c urrent timestamp
string getCurrentTimestamp() {
    // Get current time using modern C++ chrono
    auto now = chrono::system_clock::now();
    auto now_time_t = chrono::system_clock::to_time_t(now);
    
    // Convert to local time safely
    tm local_tm;
    #ifdef _WIN32
        localtime_s(&local_tm, &now_time_t);
    #else
        localtime_r(&now_time_t, &local_tm);
    #endif
    
    // Format timestamp using put_time
    ostringstream oss;
    oss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

//helper: write to record file
void writeToRecord(const string& memberID, const string& memberName, 
                   const string& gameName, const string& action) {
    ofstream recordFile("record.txt", ios::app);
    if (!recordFile) {
        cout << "Warning: Could not open record.txt for writing.\n";
        return;
    }
    
    recordFile << "[" << getCurrentTimestamp() << "] "
               << "Member: " << memberName << " (ID: " << memberID << ") "
               << action << " game: \"" << gameName << "\"\n";
    
    recordFile.close();
}

//borrow game
void Member::borrowGame(GameNode* game) {
    if (!game) {
        cout << "Error: Game not found.\n";
        return;
    }
    
    if (game->isBorrowed) {
        cout << "Error: Game already borrowed.\n";
        return;
    }
    
    // Mark original game as borrowed
    game->isBorrowed = true;
    game->borrowedBy = memberID;
    
    // Create a NEW copy for the member's borrowed list
    GameNode* borrowedCopy = new GameNode();
    borrowedCopy->name = game->name;
    borrowedCopy->minPlayers = game->minPlayers;
    borrowedCopy->maxPlayers = game->maxPlayers;
    borrowedCopy->maxPlayTime = game->maxPlayTime;
    borrowedCopy->minPlayTime = game->minPlayTime;
    borrowedCopy->yearPublished = game->yearPublished;
    borrowedCopy->isBorrowed = true;
    borrowedCopy->borrowedBy = memberID;
    borrowedCopy->next = nullptr;
    borrowedCopy->nextcopy = nullptr;
    
    // Add to member's borrowed list (insert at head)
    borrowedCopy->next = borrowedHead;
    borrowedHead = borrowedCopy;
    
    // Record to file
    writeToRecord(memberID, name, game->name, "BORROWED");
    
    cout << "Success: " << name << " borrowed \"" << game->name << "\".\n";
}

//return game
void Member::returnGame(const string& gameName, GameList* gameList) {
    GameNode* curr = borrowedHead;
    GameNode* prev = nullptr;
    
    // Search for the game in member's borrowed list
    while (curr && curr->name != gameName) {
        prev = curr;
        curr = curr->next;
    }
    
    if (!curr) {
        cout << "Error: " << name << " does not have \"" << gameName << "\".\n";
        return;
    }
    
    // Remove from member's borrowed list
    if (!prev) {
        borrowedHead = curr->next;
    } else {
        prev->next = curr->next;
    }
    
    // Find the original game in the main GameList and mark as available
    if (gameList) {
        GameNode* originalGame = gameList->searchAVL(gameName);
        if (originalGame && originalGame->borrowedBy == memberID) {
            originalGame->isBorrowed = false;
            originalGame->borrowedBy = "";
        }
    }
    
    // Record to file
    writeToRecord(memberID, name, gameName, "RETURNED");
    
    delete curr;
    
    cout << "Success: \"" << gameName << "\" returned by " << name << ".\n";
}


void Member::printBorrowedGames() {
    cout << "Games borrowed by " << name << ":\n";
    if (!borrowedHead) {
        cout << "(None)\n";
        return;
    }
    
    GameNode* curr = borrowedHead;
    int count = 1;
    while (curr) {
        cout << count << ". " << curr->name 
             << " (" << curr->minPlayers << "-" << curr->maxPlayers 
             << " players, " << curr->yearPublished << ")\n";
        curr = curr->next;
        count++;
    }
    cout << "------------------------\n";
}


Member::~Member() {
    GameNode* curr = borrowedHead;
    while (curr) {
        GameNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void Member::recordGamePlay( const string& gameName, const string& participantIDs, const string& winnerID) {
    ofstream outFile("recordgames.txt", ios::app);

    if (!outFile) {
        cout << "Error opening recordgames.txt\n";
        return;
    }

    outFile << gameName << " , "
        << participantIDs << " , "
        << winnerID << endl;

    outFile.close();

    cout << "Game play recorded successfully.\n";
}