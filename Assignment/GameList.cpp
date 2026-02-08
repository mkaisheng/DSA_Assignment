#include "GameList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


void deleteAVL(AVLNode* node); //declare so that functions above deleteAVL knows that this function exist

//Janelle//
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
	} //deletes all nodes in linked list

	deleteAVL(avlRoot); //deletes all nodes in AVL tree
}


//insert game 
void GameList::insertGame(GameNode* newNode) {
    newNode->next = head;
    head = newNode;

	if (!suppressRebuild) //supress rebuild is essentially a flag to prevent rebuilding the AVL tree during bulk inserts 
        rebuildIndex(); //e.g if i want to insert more than 1 game , i have supress rebuild on so it doesnt constantly rebulild
}

//load games.csv
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

		// special case to handle quoted names with commas (e,g "Catan, The")
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

//display
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

//count number of nodes ( ie.how many games)
int GameList::countGames() {
    int count = 0;
    GameNode* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

//remove game from the name given
void GameList::removeGame(const string& name) {
    if (!head) return;

	// Special case: removing head
    if (head->name == name) {
        GameNode* temp = head;
        head = head->next;
        delete temp;
        rebuildIndex(); //rebuild the avl tree
        return;
    }

    GameNode* curr = head;
    while (curr->next && curr->next->name != name) {
        curr = curr->next;
    }
	//traverse until the name is found
    if (curr->next) {
        GameNode* temp = curr->next;
        curr->next = temp->next;
        delete temp; //connect the previous node from deleted to the next node from deleted and delete the chosen node
		rebuildIndex(); //rebuild the avl tree
    }
}
//display game from players
void GameList::displayGamesByPlayers(int numPlayers) {
    cout << "\n--- Games for " << numPlayers << " Players ---\n";

    GameNode* curr = head;
    bool found = false;

    while (curr) {
        if (curr->minPlayers <= numPlayers &&
            numPlayers <= curr->maxPlayers) {

            cout << curr->name << " ("
                << curr->minPlayers << " - "
                << curr->maxPlayers << " players, "
                << curr->yearPublished << ")\n";

            found = true;
        }
        curr = curr->next;
    }

    if (!found) {
        cout << "No games available for this number of players.\n";
    }
}



//KAI SHENG S10268302J//
//Merge sort helpers
static void splitList(GameNode* source, GameNode*& front, GameNode*& back) {
    GameNode* slow = source;
	GameNode* fast = source->next; //start fast one step ahead

    while (fast) { 
        fast = fast->next;
        if (fast) {
            slow = slow->next; //?
            fast = fast->next;
        }
    }

    front = source;
	back = slow->next; //breaks the list into two seperate lists
    slow->next = nullptr;
}

//merges 2 ALREADY sorted lists together
GameNode* GameList::mergeSorted(GameNode* a, GameNode* b) {
    if (!a) return b; //base cases
    if (!b) return a; //if one list is empty return the other

    bool takeA = false;

    switch (currentSort) {
    case SortMode::NAME:
        takeA = (a->name <= b->name);
        break;

    case SortMode::MIN_PLAYERS:
        takeA = (a->minPlayers <= b->minPlayers);
        break;

    case SortMode::MAX_PLAYERS:
        takeA = (a->maxPlayers <= b->maxPlayers);
        break;

    case SortMode::YEAR:
        takeA = (a->yearPublished <= b->yearPublished);
        break;
    }

	if (takeA) { //if a is smaller or equal to b based on current sort mode
		a->next = mergeSorted(a->next, b); //recursively merge the rest
        return a;
    }
    else {
        b->next = mergeSorted(a, b->next);
        return b;
    }
}

//merge sort
void GameList::mergeSort(SortMode mode) {
    currentSort = mode; 
    mergeSortInternal(head);
    rebuildIndex(); // AVL rebuilt after sorting
}

void GameList::mergeSortInternal(GameNode*& node) {
	if (!node || !node->next) //base case : 0 or 1 nodes
        return;

    GameNode* a;
    GameNode* b;

    splitList(node, a, b);
	mergeSortInternal(a); //recursively call to split the list 
    mergeSortInternal(b); 

	node = mergeSorted(a, b); //recursively called to merge the 2 sorted lists
}


//AVL Tree//
//The AVL tree uses a search through name . It doesnt break when it is sorted by year / max players as it does comparisions based on the alphabetical value (ascii table) 
int height(AVLNode* n) {
    return n ? n->height : 0; //return height of node n( return 0 if no nodes)
}

int getBalance(AVLNode* n) {
	return n ? height(n->left) - height(n->right) : 0; //return balance factor of node n ( return 0 if no nodes)
}


//Rotate right for imbalanced tree leaning to the left
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left; //x becomes new root ( ie. left of y is the new root)
    AVLNode* T2 = x->right; //t2 stored temporarily
    
    //perform rotation here
	x->right = y; //insert y to the right of x
	y->left = T2; //t2 becomes left child of y

    //update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; //x is new subtree root
}


//Rotate left for imbalanced tree leaning to the right
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right; // y is the root
    AVLNode* T2 = y->left;

	//perform rotation here
    y->left = x; //insert x to the left of root
	x->right = T2; //t2 becomes right child of x

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}
//Insert into AVL tree
AVLNode* insertAVL(AVLNode* node, GameNode* game) {
	if (!node) { //base case : empty tree
        return new AVLNode{
            game->name,
            game,
            nullptr,
            nullptr,
            nullptr,
            1
        };
    } 
	//if game with same name already exists , insert into linked list of copies
    if (game->name == node->key) {
        game->nextcopy = node->headOfCopies;
        node->headOfCopies = game;
        return node;
    }

	//bst insertion : traverse left or right based on comparison of names
    if (game->name < node->key)
        node->left = insertAVL(node->left, game);
    else
        node->right = insertAVL(node->right, game);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node); //checks for imbalance

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
    if (!node) return; //post order deletion
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

