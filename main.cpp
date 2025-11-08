/**
 * @file main.cpp
 * @brief Glowny plik programu z interfejsem uzytkownika (menu).
 * * Zawiera funkcje main() oraz funkcje pomocnicze do obslugi
 * konsolowego menu nawigacyjnego dla drzewa BST.
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits> // Do czyszczenia bufora cin

#include "BST.h"
#include "FileHandler.h"

using namespace std; // Dla uproszczenia kodu

 /**
  * @brief Czysci bufor wejsciowy (stdin) w przypadku blednego wprowadzenia danych.
  * * Usuwa flagi bledu strumienia cin i ignoruje wszystkie znaki
  * az do napotkania znaku nowej linii.
  */
void clearInputBuffer() {
    cin.clear(); // Wyczysc flagi bledu
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj reszte linii
}

/**
 * @brief Wyswietla glowne menu programu na standardowym wyjsciu (konsola).
 */
void printMenu() {
    cout << "\n--- MENU DRZEWA BST --- \n"
        << "1. Dodaj element\n"
        << "2. Usun element\n"
        << "3. Wyczysc cale drzewo\n"
        << "4. Szukaj drogi do elementu\n"
        << "5. Wyswietl drzewo (Pre/In/Post/Graficznie)\n"
        << "-----------------------\n"
        << "6. Zapisz drzewo do pliku tekstowego (drzewo.txt)\n"
        << "7. Wczytaj liczby z pliku tekstowego (dane.txt)\n"
        << "8. Zapisz drzewo binarnie (drzewo.bin)\n"
        << "9. Wczytaj drzewo binarnie (drzewo.bin)\n"
        << "-----------------------\n"
        << "0. Wyjscie\n"
        << "-----------------------\n"
        << "Twoj wybor: ";
}

/**
 * @brief Glowna funkcja programu, obslugujaca petle zdarzen menu.
 * @return 0 po pomyslnym zakonczeniu programu.
 */
int main() {
    BST myTree;
    FileHandler fileHandler;
    int choice;
    bool running = true;

    while (running) {
        printMenu();

        if (!(cin >> choice)) {
            cout << "Bledne dane. Prosze podac liczbe.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1: { // Dodaj element
            int val;
            cout << "Podaj liczbe do dodania: ";
            if (!(cin >> val)) {
                cout << "Bledna wartosc.\n";
                clearInputBuffer();
                break;
            }
            myTree.insert(val);
            cout << "Dodano " << val << " do drzewa.\n";
            break;
        }
        case 2: { // Usun element
            int val;
            cout << "Podaj liczbe do usuniecia: ";
            if (!(cin >> val)) {
                cout << "Bledna wartosc.\n";
                clearInputBuffer();
                break;
            }
            myTree.remove(val);
            cout << "Usunieto (lub probowano usunac) " << val << " z drzewa.\n";
            break;
        }
        case 3: { // Wyczysc drzewo
            myTree.clear();
            cout << "Drzewo zostalo wyczyszczone.\n";
            break;
        }
        case 4: { // Znajdz sciezke
            int val;
            cout << "Podaj liczbe do znalezienia sciezki: ";
            if (!(cin >> val)) {
                cout << "Bledna wartosc.\n";
                clearInputBuffer();
                break;
            }
            vector<int> path = myTree.findPath(val);
            if (path.empty()) {
                cout << "Element " << val << " nie zostal znaleziony w drzewie.\n";
            }
            else {
                cout << "Sciezka do " << val << ": ";
                for (size_t i = 0; i < path.size(); ++i) {
                    cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
                }
                cout << endl;
            }
            break;
        }
        case 5: { // Wyswietl drzewo
            myTree.display();
            break;
        }
        case 6: { // Zapisz do pliku tekstowego
            if (fileHandler.saveToText(myTree, "drzewo.txt")) {
                cout << "Drzewo zapisane (inorder) do drzewo.txt\n";
            }
            else {
                cout << "Nie udalo sie zapisac pliku tekstowego.\n";
            }
            break;
        }
        case 7: { // Wczytaj z pliku tekstowego
            if (fileHandler.loadFromText(myTree, "dane.txt")) {
                cout << "Wczytano liczby z dane.txt i dodano do drzewa.\n";
            }
            else {
                cout << "Nie udalo sie wczytac pliku tekstowego. Upewnij sie, ze plik 'dane.txt' istnieje.\n";
            }
            break;
        }
        case 8: { // Zapisz do pliku binarnego
            if (fileHandler.saveToBinary(myTree, "drzewo.bin")) {
                cout << "Drzewo zapisane binarnie do drzewo.bin\n";
            }
            else {
                cout << "Nie udalo sie zapisac pliku binarnego.\n";
            }
            break;
        }
        case 9: { // Wczytaj z pliku binarnego
            if (fileHandler.loadFromBinary(myTree, "drzewo.bin")) {
                cout << "Wczytano drzewo z pliku binarnego drzewo.bin. Poprzednia zawartosc zostala nadpisana.\n";
            }
            else {
                cout << "Nie udalo sie wczytac pliku binarnego.\n";
            }
            break;
        }
        case 0: { // Wyjscie
            running = false;
            cout << "Do widzenia!\n";
            break;
        }
        default: {
            cout << "Nieprawidlowa opcja. Spr�buj ponownie.\n";
            break;
        }
        } // koniec switch

        if (running && choice != 0) {
            cout << "\nNacisnij Enter, aby kontynuowac...";
            clearInputBuffer(); // Wyczysc ewentualne pozostalosci po cin >> choice
            cin.get(); // Czekaj na Enter
        }

    } // koniec while

    return 0;
}


