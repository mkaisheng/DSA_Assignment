
#include <string>
#include <iostream>
#pragma once

using namespace std;

/// Janelle
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


//Kai Sheng (AVL node to search and Sort Mode to enable sorting prefrences)
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

//Janelle
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

	 //Janelle
	 void insertGame( GameNode* newNode);
	 void loadCSV(const string& filename);
	 void displayGames();
	 int countGames();
	 void removeGame(const string& name);
	 void displayGamesByPlayers(int numPlayers);

	 //Kai Sheng
	 GameNode* searchAVL(const string& name);
	 void mergeSort(SortMode mode);
	 void rebuildIndex();
};
