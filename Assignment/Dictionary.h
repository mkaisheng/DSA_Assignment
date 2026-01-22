#include <string>
#include <iostream>
#pragma once
using namespace std;

struct GameNode {
    int minPlayers;
    int maxPlayers;
    int minPlayTime;
    int maxPlayTime;
    int yearPublished;

    GameNode* next;
};

struct DictEntry {
    char name[100];        // key
    GameNode* head;        // list of duplicates
    DictEntry* next;       // collision chain
};

#define TABLE_SIZE 101

class Dictionary
{
private:
    DictEntry* items[TABLE_SIZE];
    int size;

    int hashFunction(const char* str);

public:
    Dictionary();
    ~Dictionary();

    void insert(const char* name, int minP, int maxP, int minT, int maxT, int year);
    void search(const char* name);
    void clear();
};