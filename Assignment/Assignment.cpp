#include "Dictionary.h"

int main()
{
    Dictionary dict;

    dict.LoadCSV("games.csv");

    dict.search("Uno");
    dict.search("Azul");
}

