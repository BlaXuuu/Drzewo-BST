/**
 * @file FileHandler.cpp
 * @brief Implementacja metod klasy FileHandler.
 */

#include "FileHandler.h"
#include <fstream>
#include <iostream>

using namespace std;

bool FileHandler::saveToText(BST& tree, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        return false;
    }
    // Wywolujemy prywatna metode pomocnicza z klasy BST
    tree.saveToText(tree.root, outFile);
    outFile.close();
    return true;
}

bool FileHandler::saveToBinary(BST& tree, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Blad: Nie mozna otworzyc pliku binarnego do zapisu: " << filename << endl;
        return false;
    }
    // Wywolujemy prywatna metode pomocnicza z klasy BST
    tree.serialize(tree.root, outFile);
    outFile.close();
    return true;
}

bool FileHandler::loadFromBinary(BST& tree, const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Blad: Nie mozna otworzyc pliku binarnego do odczytu: " << filename << endl;
        return false;
    }

    // Usuwamy stare drzewo przed wczytaniem nowego
    tree.clear();
    // Wywolujemy prywatna metode pomocnicza z klasy BST
    tree.root = tree.deserialize(inFile);

    inFile.close();
    return true;
}

bool FileHandler::loadFromText(BST& tree, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Blad: Nie mozna otworzyc pliku tekstowego do odczytu: " << filename << endl;
        return false;
    }

    int number;
    // Czytamy liczby z pliku i dodajemy do drzewa
    // Dziala to zarowno dla pustego, jak i istniejacego drzewa.
    while (inFile >> number) {
        tree.insert(number);
    }

    inFile.close();
    return true;
}
//test