/**
 * @file BST.h
 * @brief Definicja klasy BST (Binary Search Tree).
 * * Plik ten zawiera deklaracje klasy BST, w tym jej wewnetrzna strukture Node
 * oraz wszystkie metody do zarzadzania drzewem (dodawanie, usuwanie, wyszukiwanie, wyswietlanie).
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip> // Do printGraphical

using namespace std;

 // Uzywamy forward-declaration, aby uniknac cyklicznych zaleznosci
class FileHandler;

/**
 * @brief Implementacja drzewa binarnego poszukiwan (BST).
 * * Klasa przechowuje elementy w uporzadkowanej strukturze drzewa,
 * umozliwiajac szybkie wyszukiwanie, dodawanie i usuwanie elementow.
 */
class BST {
private:
    /**
     * @brief Struktura reprezentujaca pojedynczy wezel w drzewie BST.
     */
    struct Node {
        int data; ///< Wartosc przechowywana w wezle.
        Node* left; ///< Wskaznik na lewe dziecko.
        Node* right; ///< Wskaznik na prawe dziecko.

        /**
         * @brief Konstruktor wezla.
         * @param val Wartosc do przechowania w wezle.
         */
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    /// @brief Wskaznik na korzen drzewa.
    Node* root;

    // --- Metody pomocnicze (rekurencyjne) ---

    /**
     * @brief Prywatna, rekurencyjna metoda do wstawiania nowego wezla.
     * @param node Aktualnie przetwarzany wezel.
     * @param data Wartosc do wstawienia.
     * @return Wskaznik na (potencjalnie nowy) korzen poddrzewa.
     */
    Node* insert(Node* node, int data);

    /**
     * @brief Prywatna, rekurencyjna metoda do usuwania wezla.
     * @param node Aktualnie przetwarzany wezel.
     * @param data Wartosc do usuniecia.
     * @return Wskaznik na korzen poddrzewa po usunieciu.
     */
    Node* remove(Node* node, int data);

    /**
     * @brief Znajduje wezel o minimalnej wartosci w danym poddrzewie.
     * @param node Korzen poddrzewa do przeszukania.
     * @return Wskaznik na wezel z minimalna wartoscia.
     */
    Node* findMin(Node* node);

    /**
     * @brief Prywatna, rekurencyjna metoda do usuwania wszystkich wezlow drzewa.
     * @param node Aktualnie przetwarzany wezel.
     */
    void clear(Node* node);

    /**
     * @brief Prywatna, rekurencyjna metoda do znajdowania sciezki do elementu.
     * @param node Aktualnie przetwarzany wezel.
     * @param data Wartosc szukanego elementu.
     * @param path Wektor przechowujacy sciezke (przekazywany przez referencje).
     * @return true jesli element zostal znaleziony, false w przeciwnym razie.
     */
    bool findPath(Node* node, int data, vector<int>& path);

    // --- Metody wyswietlania ---

    /**
     * @brief Wyswietla drzewo metoda Preorder (Korzen, Lewo, Prawo).
     * @param node Aktualnie przetwarzany wezel.
     */
    void printPreorder(Node* node);

    /**
     * @brief Wyswietla drzewo metoda Inorder (Lewo, Korzen, Prawo).
     * @param node Aktualnie przetwarzany wezel.
     */
    void printInorder(Node* node);

    /**
     * @brief Wyswietla drzewo metoda Postorder (Lewo, Prawo, Korzen).
     * @param node Aktualnie przetwarzany wezel.
     */
    void printPostorder(Node* node);

    /**
     * @brief Wyswietla drzewo graficznie (w orientacji poziomej).
     * @param node Aktualnie przetwarzany wezel.
     * @param space Aktualne wciecie (liczba spacji).
     * @param count Liczba spacji dodawana na kazdym poziomie.
     */
    void printGraphical(Node* node, int space, int count);

    // --- Metody pomocnicze do zapisu/odczytu (wywolywane przez FileHandler) ---

    /**
     * @brief Zapisuje drzewo do pliku tekstowego (w kolejnosci Inorder).
     * @param node Aktualnie przetwarzany wezel.
     * @param outFile Strumien wyjsciowy pliku.
     */
    void saveToText(Node* node, ofstream& outFile);

    /**
     * @brief Serializuje (zapisuje binarnie) strukture drzewa (w kolejnosci Preorder).
     * @param node Aktualnie przetwarzany wezel.
     * @param outFile Strumien wyjsciowy pliku binarnego.
     */
    void serialize(Node* node, ofstream& outFile);

    /**
     * @brief Deserializuje (odczytuje binarnie) strukture drzewa.
     * @param inFile Strumien wejsciowy pliku binarnego.
     * @return Wskaznik na odtworzony wezel (lub nullptr).
     */
    Node* deserialize(ifstream& inFile);

public:
    /// @brief Konstruktor domyslny, tworzy puste drzewo.
    BST();

    /// @brief Destruktor, zwalnia pamiec po wszystkich wezlach.
    ~BST();

    /**
     * @brief Publiczna metoda dodajaca element do drzewa.
     * @param data Wartosc do dodania.
     */
    void insert(int data);

    /**
     * @brief Publiczna metoda usuwajaca element z drzewa.
     * @param data Wartosc do usuniecia.
     */
    void remove(int data);

    /**
     * @brief Publiczna metoda usuwajaca wszystkie elementy z drzewa.
     */
    void clear();

    /**
     * @brief Wyszukuje sciezke od korzenia do wezla o podanej wartosci.
     * @param data Wartosc do znalezienia.
     * @return Wektor (STL) zawierajacy wartosci wezlow na sciezce.
     * Pusty wektor, jesli elementu nie znaleziono.
     */
    vector<int> findPath(int data);

    /**
     * @brief Wyswietla menu wyboru metody wyswietlania drzewa i je wyswietla.
     */
    void display();

    /**
     * @brief Zaprzyjaznienie klasy FileHandler.
     * * Pozwala klasie FileHandler na dostep do prywatnych skladowych (root)
     * i prywatnych metod (serialize, deserialize, saveToText) klasy BST.
     */
    friend class FileHandler;
};
//test