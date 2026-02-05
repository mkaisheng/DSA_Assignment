#ifndef DICTIONARY_H

#endif // !DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#pragma once
using namespace std;

struct GameNode {
    int minPlayers;
    int maxPlayers;
    int minPlayTime;
    int maxPlayTime;
    int yearPublished;
    
    bool isBorrowed = false;       // True if taken
    string borrowedBy = "";        // Stores Member ID

    GameNode* next;
};

struct DictEntry {
    string name;       // key
    GameNode* head;        // list of duplicates
    DictEntry* next;       // collision chain
};

#define TABLE_SIZE 101

class Dictionary
{
private:
    DictEntry* items[TABLE_SIZE];
    int size;

    int hashFunction(const string& key);

public:
    Dictionary();
    ~Dictionary();

    void LoadCSV(const string& file);
    void insert(const string& name, int minP, int maxP, int minT, int maxT, int year);
    void search(const string& name);
    void clear();

    bool borrowGame(const string& gameName, const string& studentID);
    bool returnGame(const string& gameName, const string& studentID);
    void displayBorrowedGames();
    void saveToCSV(const string& filename);
    bool remove(const string& gameName);
};
