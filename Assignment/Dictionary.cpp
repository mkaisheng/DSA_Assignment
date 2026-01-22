#include "Dictionary.h"

Dictionary::Dictionary() {
    size = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        items[i] = NULL;
    }
}

Dictionary::~Dictionary() {
	clear();
}

int Dictionary::hashFunction(const char* str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % TABLE_SIZE;
}

void Dictionary::insert(const char* name, int minP, int maxP, int minT, int maxT, int year) {
    int index = hashFunction(name);

    DictEntry* entry = items[index];

    // Check if name already exists
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            // Add to duplicate list
            GameNode* newNode = new GameNode;
            newNode->minPlayers = minP;
            newNode->maxPlayers = maxP;
            newNode->minPlayTime = minT;
            newNode->maxPlayTime = maxT;
            newNode->yearPublished = year;

            newNode->next = entry->head;
            entry->head = newNode;
            return;
        }
        entry = entry->next;
    }

    // Create new dictionary entry if key doesn't exist
    DictEntry* newEntry = new DictEntry;
    strcpy(newEntry->name, name);
    newEntry->head = NULL;

    GameNode* newNode = new GameNode;
    newNode->minPlayers = minP;
    newNode->maxPlayers = maxP;
    newNode->minPlayTime = minT;
    newNode->maxPlayTime = maxT;
    newNode->yearPublished = year;
    newNode->next = NULL;

    newEntry->head = newNode;

    newEntry->next = items[index];
    items[index] = newEntry;

    size++;
}

void Dictionary::search(const char* name) {
    int index = hashFunction(name);

    DictEntry* entry = items[index];

    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            GameNode* curr = entry->head;

            while (curr != NULL) {
                cout << "Game: " << name << endl;
                cout << "Players: " << curr->minPlayers << " - " << curr->maxPlayers << endl;
                cout << "Playtime: " << curr->minPlayTime << " - " << curr->maxPlayTime << endl;
                cout << "Year: " << curr->yearPublished << endl;
                cout << "--------------------" << endl;

                curr = curr->next;
            }
            return;
        }
        entry = entry->next;
    }

    cout << "Game not found.\n";
}

void Dictionary::clear() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        DictEntry* entry = items[i];

        while (entry != NULL) {
            GameNode* node = entry->head;

            // Delete duplicate nodes
            while (node != NULL) {
                GameNode* tempNode = node;
                node = node->next;
                delete tempNode;
            }

            DictEntry* tempEntry = entry;
            entry = entry->next;
            delete tempEntry;
        }

        items[i] = NULL;
    }
}