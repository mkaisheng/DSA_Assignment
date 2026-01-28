#include "Dictionary.h"

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

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
    if (hash < 0) hash = -hash;
    return hash % TABLE_SIZE;
}

void Dictionary::insert(const char* name, int minP, int maxP, int minT, int maxT, int year) {
    int index = hashFunction(name);

    DictEntry* entry = items[index];

    // Check if name already exists
    while (entry != NULL) {
        if (entry->name == name) {
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

    // Create new dictionary entry
    DictEntry* newEntry = new DictEntry;
    newEntry->name = name;  // std::string handles copy safely
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
        if (entry->name == string(name)){
            GameNode* curr = entry->head;

            while (curr != NULL) {
                cout << "Game: " << entry->name << endl;
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

void Dictionary::LoadCSV(string file) {
    string line;
    ifstream inFile(file);

    if (!inFile.is_open()) {
        cerr << "Unable to open file " << file << endl;
        return;
    }

    // Skip header
    getline(inFile, line);

    while (getline(inFile, line)) {
        stringstream ss(line);

        string name, minP, maxP, maxT, minT, year;

        getline(ss, name, ',');
        getline(ss, minP, ',');
        getline(ss, maxP, ',');
        getline(ss, maxT, ',');
        getline(ss, minT, ',');
        getline(ss, year, ',');

        // Trim spaces
        name = trim(name);
        minP = trim(minP);
        maxP = trim(maxP);
        minT = trim(minT);
        maxT = trim(maxT);
        year = trim(year);

        try {
            insert(
                name.c_str(),
                stoi(minP),
                stoi(maxP),
                stoi(minT),
                stoi(maxT),
                stoi(year)
            );
        }
        catch (...) {
            cout << "Invalid stoi row skipped: " << line << endl;
        }
    }

    inFile.close();
}
