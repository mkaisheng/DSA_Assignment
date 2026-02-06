#include "GameList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void deleteAVL(AVLNode* node);
GameList::GameList() {
    head = nullptr;
    avlRoot = nullptr;
}
GameList::~GameList() {
    GameNode* curr = head;
    while (curr) {
        GameNode* next = curr->next;
        delete curr;
        curr = next;
    }

    deleteAVL(avlRoot);
}
/* =========================
   Insert at Head
   ========================= */
void GameList::insertGame(GameNode* newNode) {
    newNode->next = head;
    head = newNode;

    if (!suppressRebuild)
        rebuildIndex();
}

/* =========================
   Load CSV
   ========================= */
void GameList::loadCSV(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return;
    }

    string line;
    getline(file, line); // skip header
    suppressRebuild = true;

    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines at end of file

        stringstream ss(line);
        GameNode* node = new GameNode();
        string temp;

        // SPECIAL CASE: HANDLE NAMES WITH COMMAS
        // Checks if the first character is a quote (")
        if (ss.peek() == '"') {
            ss.get();                     //get the open commas 
			getline(ss, node->name, '"'); // Read name until the closing quote
            ss.get();                     //get the closing comams
        }
        else {
			getline(ss, node->name, ','); // Regular name without quotes
        }
        

        try {
            // Read the rest of the numbers safely
            getline(ss, temp, ',');
            node->minPlayers = temp.empty() ? 0 : stoi(temp);

            getline(ss, temp, ',');
            node->maxPlayers = temp.empty() ? 0 : stoi(temp);

            getline(ss, temp, ',');
            node->maxPlayTime = temp.empty() ? 0 : stoi(temp);

            getline(ss, temp, ',');
            node->minPlayTime = temp.empty() ? 0 : stoi(temp);

            getline(ss, temp);
            node->yearPublished = temp.empty() ? 0 : stoi(temp);

            insertGame(node);
        }
        catch (...) {
            cout << "Skipping invalid line: " << node->name << endl;
            delete node;
        }
    }

    suppressRebuild = false;
    rebuildIndex();
    file.close();
}

/* =========================
   Display Games
   ========================= */
void GameList::displayGames() {
    int count = 0;
    GameNode* curr = head;

    while (curr != nullptr) {
        cout << curr->name << " ("
            << curr->minPlayers << "-"
            << curr->maxPlayers << " players, "
            << curr->yearPublished << ")\n";
        curr = curr->next;
        count++;
    }
}

/* =========================
   Count Nodes
   ========================= */
int GameList::countGames() {
    int count = 0;
    GameNode* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

void GameList::removeGame(const string& name) {
    if (!head) return;

    if (head->name == name) {
        GameNode* temp = head;
        head = head->next;
        delete temp;
        rebuildIndex();
        return;
    }

    GameNode* curr = head;
    while (curr->next && curr->next->name != name) {
        curr = curr->next;
    }

    if (curr->next) {
        GameNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        rebuildIndex();
    }
}



/* =========================
   Merge Sort Helpers
   ========================= */
static void splitList(GameNode* source, GameNode*& front, GameNode*& back) {
    GameNode* slow = source;
    GameNode* fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    front = source;
    back = slow->next;
    slow->next = nullptr;
}

static GameNode* mergeSorted(GameNode* a, GameNode* b) {
    if (!a) return b;
    if (!b) return a;

    GameNode* result = nullptr;

    if (a->name <= b->name) {
        result = a;
        result->next = mergeSorted(a->next, b);
    }
    else {
        result = b;
        result->next = mergeSorted(a, b->next);
    }

    return result;
}

/* =========================
   Merge Sort
   ========================= */
void GameList::mergeSort() {
    mergeSortInternal(head);
    rebuildIndex();
}


//AVL Tree
int height(AVLNode* n) {
    return n ? n->height : 0;
}

int getBalance(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insertAVL(AVLNode* node, GameNode* game) {
    if (!node) {
        return new AVLNode{
            game->name,
            game,
            nullptr,
            nullptr,
            nullptr,
            1
        };
    }
    if (game->name == node->key) {
        game->nextcopy = node->headOfCopies;
        node->headOfCopies = game;
        return node;
    }
    if (game->name < node->key)
        node->left = insertAVL(node->left, game);
    else
        node->right = insertAVL(node->right, game);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && game->name < node->left->key)
        return rotateRight(node);

    // Right Right
    if (balance < -1 && game->name > node->right->key)
        return rotateLeft(node);

    // Left Right
    if (balance > 1 && game->name > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && game->name < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//Binary Search from AVL tree
GameNode* GameList::searchAVL(const string& name) {
    AVLNode* curr = avlRoot;
    while (curr) {
        if (name == curr->key)
            return curr->gamePtr;
        else if (name < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return nullptr;
}

void deleteAVL(AVLNode* node) {
    if (!node) return;
    deleteAVL(node->left);
    deleteAVL(node->right);
    delete node;
}

void GameList::rebuildIndex() {
    // 1. Clear old AVL tree
    deleteAVL(avlRoot);
    avlRoot = nullptr;

    // 2. Rebuild from linked list
    GameNode* curr = head;
    while (curr != nullptr) {
        avlRoot = insertAVL(avlRoot, curr);
        curr = curr->next;
    }
}

void GameList::mergeSortInternal(GameNode*& node) {
    if (!node || !node->next)
        return;

    GameNode* a;
    GameNode* b;

    splitList(node, a, b);
    mergeSortInternal(a);
    mergeSortInternal(b);

    node = mergeSorted(a, b);
}