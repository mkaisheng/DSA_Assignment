
#include <string>
#include <iostream>
#pragma once

using namespace std;

/// GameNode to store game information
struct GameNode {
	string name;

	int minPlayers;
	int maxPlayers;
	int minPlayTime;
	int maxPlayTime;
	int yearPublished;

	bool isBorrowed = false;       // True if taken
	string borrowedBy = "";        // Stores Member ID

	GameNode* next = nullptr;
	GameNode* nextcopy = nullptr;
};

//AVL Node to search

struct AVLNode {
	string key;            // game name
	GameNode* gamePtr;     // pointer to linked list node
	GameNode* headOfCopies;
	AVLNode* left = nullptr;
	AVLNode* right = nullptr;
	int height = 1;
};
//Merge sort node to sort by preferences

enum class SortMode {
	NAME,
	MIN_PLAYERS,
	MAX_PLAYERS,
	YEAR
};

class GameList
{
private:
	GameNode* head;
	AVLNode* avlRoot;
	bool suppressRebuild = false;
	SortMode currentSort = SortMode::NAME;

	void mergeSortInternal(GameNode*& node);
	GameNode* mergeSorted(GameNode* a, GameNode* b);
public:
	GameList();
	~GameList();

	//admin functions
	void insertGame( GameNode* newNode);
	 void loadCSV(const string& filename);
	 void displayGames();
	 GameNode* searchAVL(const string& name);
	 int countGames();
	 void removeGame(const string& name);
	 void mergeSort(SortMode mode);
	 void displayGamesByPlayers(int numPlayers);

	void rebuildIndex();

};
