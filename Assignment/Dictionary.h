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

    int hashFunction(string str);

public:
    Dictionary();
    ~Dictionary();

    void LoadCSV(string file);
    void insert(string name, int minP, int maxP, int minT, int maxT, int year);
    void search(string name);
    void clear();
    bool borrowGame(string gameName, string studentID);
    bool returnGame(string gameName, string studentID);
};