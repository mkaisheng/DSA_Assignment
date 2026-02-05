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

int Dictionary::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31) + c;
    }
    return abs(hash) % TABLE_SIZE;
}


void Dictionary::insert(const string& name, int minP, int maxP, int minT, int maxT, int year) {
    int index = hashFunction(name);
    DictEntry* entry = items[index];

    while (entry) {
        if (entry->name == name) {
            GameNode* newNode = new GameNode{
                minP, maxP, minT, maxT, year, false, "", entry->head
            };
            entry->head = newNode;
            return;
        }
        entry = entry->next;
    }

    DictEntry* newEntry = new DictEntry;
    newEntry->name = name;
    newEntry->head = new GameNode{ minP, maxP, minT, maxT, year, false, "", nullptr };
    newEntry->next = items[index];
    items[index] = newEntry;
}

void Dictionary::search(const string& name) {
    int index = hashFunction(name);
    DictEntry* entry = items[index];

    while (entry) {
        if (entry->name == name) {
            for (GameNode* curr = entry->head; curr; curr = curr->next) {
                cout << "Game: " << entry->name << endl;
                cout << "Players: " << curr->minPlayers << "-" << curr->maxPlayers << endl;
                cout << "Playtime: " << curr->minPlayTime << "-" << curr->maxPlayTime << endl;
                cout << "Year: " << curr->yearPublished << endl;
                cout << "Status: " << (curr->isBorrowed ? "Borrowed" : "Available") << endl;
                cout << "--------------------\n";
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

void Dictionary::LoadCSV(const string& file) {
    ifstream inFile(file);
    string line;

    if (!inFile) {
        cerr << "Unable to open file " << file << endl;
        return;
    }

    getline(inFile, line); // skip header

    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, minP, maxP, maxT, minT, year;

        getline(ss, name, ',');
        getline(ss, minP, ',');
        getline(ss, maxP, ',');
        getline(ss, maxT, ',');
        getline(ss, minT, ',');
        getline(ss, year, ',');

        try {
            insert(
                trim(name),
                stoi(trim(minP)),
                stoi(trim(maxP)),
                stoi(trim(minT)),
                stoi(trim(maxT)),
                stoi(trim(year))
            );
        }
        catch (...) {
            cout << "Invalid row skipped: " << line << endl;
        }
    }
}

bool Dictionary::borrowGame(const string& gameName, const string& studentID) {
    int index = hashFunction(gameName);
    DictEntry* entry = items[index];

    while (entry) {
        if (entry->name == gameName) {
            for (GameNode* copy = entry->head; copy; copy = copy->next) {
                if (!copy->isBorrowed) {
                    copy->isBorrowed = true;
                    copy->borrowedBy = studentID;
                    return true;
                }
            }
            return false;
        }
        entry = entry->next;
    }
    return false;
}


bool Dictionary::returnGame(const string& gameName, const string& studentID) {
    int index = hashFunction(gameName);
    DictEntry* entry = items[index];

    while (entry) {
        if (entry->name == gameName) {
            for (GameNode* copy = entry->head; copy; copy = copy->next) {
                if (copy->isBorrowed && copy->borrowedBy == studentID) {
                    copy->isBorrowed = false;
                    copy->borrowedBy.clear();
                    return true;
                }
            }
        }
        entry = entry->next;
    }
    return false;
}

bool Dictionary::remove(const string& gameName) {
    int index = hashFunction(gameName);

    DictEntry* curr = items[index];
    DictEntry* prev = nullptr;

    while (curr != nullptr) {
        if (curr->name == gameName) {

            // Delete all game copies
            GameNode* node = curr->head;
            while (node != nullptr) {
                GameNode* temp = node;
                node = node->next;
                delete temp;
            }

            // Remove DictEntry from chain
            if (prev == nullptr) {
                items[index] = curr->next;
            }
            else {
                prev->next = curr->next;
            }

            delete curr;
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    return false; // Game not found
}

void Dictionary::saveToCSV(const string& filename) {
    ofstream out(filename);

    if (!out.is_open()) {
        cerr << "Unable to write to file " << filename << endl;
        return;
    }

    // CSV header
    out << "name,minplayers,maxplayers,maxplaytime,minplaytime,yearpublished\n";

    for (int i = 0; i < TABLE_SIZE; i++) {
        DictEntry* entry = items[i];

        while (entry != nullptr) {
            GameNode* node = entry->head;

            while (node != nullptr) {
                out << entry->name << ","
                    << node->minPlayers << ","
                    << node->maxPlayers << ","
                    << node->maxPlayTime << ","
                    << node->minPlayTime << ","
                    << node->yearPublished << "\n";

                node = node->next;
            }

            entry = entry->next;
        }
    }

    out.close();
}


void Dictionary::displayBorrowedGames() {
    bool found = false;

    cout << "\n=== Borrowed Games Summary ===\n";

    for (int i = 0; i < TABLE_SIZE; i++) {
        DictEntry* entry = items[i];

        while (entry != nullptr) {
            GameNode* current = entry->head;

            while (current != nullptr) {
                if (current->isBorrowed) {
                    cout << "Game: " << entry->name << endl;
                    cout << "Borrowed by: " << current->borrowedBy << endl;
                    cout << "---------------------------\n";
                    found = true;
                }
                current = current->next;
            }
            entry = entry->next;
        }
    }

    if (!found) {
        cout << "No games are currently borrowed.\n";
    }
}