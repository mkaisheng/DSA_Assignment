# Board Game Library Management System

A C++ console application designed to manage a board game lending library. This system allows administrators to manage inventory and members, while members can search for, borrow, return, and record gameplay sessions.

## 📋 Table of Contents

* [Features](https://www.google.com/search?q=%23-features)
* [Data Structures & Algorithms](https://www.google.com/search?q=%23-data-structures--algorithms)
* [File Structure](https://www.google.com/search?q=%23-file-structure)
* [Data Files](https://www.google.com/search?q=%23-data-files)

## 🚀 Features

### Administrator Menu

* **Manage Inventory**: Add new games to the library or remove existing ones.
* **Manage Members**: Register new members or remove them from the system.
* **View Reports**: Display a full list of registered members and a summary of currently borrowed games.
* **Library Overview**: View the entire catalog of games available in the system.

### Member Menu

* **Borrow & Return**: Members can borrow games (if available) and return them. The system tracks availability in real-time.
* **Smart Search**: Quickly find specific games by name using an optimized search algorithm.
* **Sorting & Filtering**: Display games sorted by Name, Year, or Player Count, or filter to see only games that support a specific number of players.
* **Record Gameplay**: Log details of game sessions, including participants and the winner.
* **Personal History**: View a list of games currently held by the logged-in member.

## 🧠 Data Structures & Algorithms

This project implements advanced data structures from scratch (no STL containers for core logic) to ensure efficiency:

1. **AVL Tree (Self-Balancing Binary Search Tree)**
* **Usage**: Used to index games by name.
* **Benefit**: Provides `O(log n)` time complexity for searching games, ensuring fast lookups even with a large library.


2. **Doubly/Singly Linked Lists**
* **Usage**: The primary storage for the `GameList` (inventory) and the list of `Members`.
* **Benefit**: Allows for dynamic memory management and efficient insertion/deletion of items.


3. **Merge Sort**
* **Usage**: Used to sort the game library by various criteria (Name, Min Players, Max Players, Year).
* **Benefit**: A stable, `O(n log n)` sorting algorithm that works efficiently with linked lists.



## 📂 File Structure

* **`Assignment.cpp`**: Main entry point containing the menu logic for Admins and Members.
* **`Administrator.cpp/h`**: Handles administrative tasks like adding/removing games and users.
* **`GameList.cpp/h`**: Manages the linked list of games, the AVL tree index, and sorting logic.
* **`Member.cpp/h`**: Manages member details and borrowing/returning actions.
* **`Dictionary.h`**: (Helper file for data definitions).


## 💾 Data Files

The system persists data using the following files:

* **`games.csv`**: The master database of all board games (Name, Players, Time, Year).
* **`Record.txt`**: A log file that automatically tracks every borrow and return transaction with timestamps.
* **`recordgames.txt`**: Stores the history of gameplay sessions recorded by members.

