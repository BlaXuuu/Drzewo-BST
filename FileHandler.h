/**
 * @file FileHandler.h
 * @brief Definicja klasy FileHandler.
 * * Klasa ta odpowiada za operacje wejscia/wyjscia na plikach (tekstowych i binarnych)
 * w celu zapisywania i odczytywania struktury drzewa BST.
 */

#pragma once

#include <string>
#include "BST.h" // Potrzebujemy pelnej definicji BST

using namespace std;

 /**
  * @brief Klasa obslugujaca operacje plikowe dla drzewa BST.
  * * Umozliwia zapisywanie stanu drzewa do plikow tekstowych i binarnych
  * oraz odczytywanie danych (zastepujac lub dodajac do) drzewa.
  * Jest zaprzyjazniona z klasa BST, aby miec dostep do jej prywatnych metod.
  */
class FileHandler {
public:
    /**
     * @brief Zapisuje drzewo do pliku tekstowego (w kolejnosci Inorder).
     * @param tree Referencja do obiektu drzewa BST, ktore ma byc zapisane.
     * @param filename Nazwa pliku wyjsciowego.
     * @return true jesli zapis sie powiodl, false w przeciwnym razie.
     */
    bool saveToText(BST& tree, const string& filename);

    /**
     * @brief Zapisuje (serializuje) cala strukture drzewa do pliku binarnego.
     * @param tree Referencja do obiektu drzewa BST.
     * @param filename Nazwa binarnego pliku wyjsciowego.
     * @return true jesli zapis sie powiodl, false w przeciwnym razie.
     */
    bool saveToBinary(BST& tree, const string& filename);

    /**
     * @brief Wczytuje (deserializuje) cala strukture drzewa z pliku binarnego.
     * @warning Ta operacja usuwa (czysci) istniejace drzewo przed wczytaniem.
     * @param tree Referencja do obiektu drzewa BST, ktore ma byc zastapione.
     * @param filename Nazwa binarnego pliku wejsciowego.
     * @return true jesli odczyt sie powiodl, false w przeciwnym razie.
     */
    bool loadFromBinary(BST& tree, const string& filename);

    /**
     * @brief Wczytuje liczby z pliku tekstowego i dodaje je do drzewa.
     * @note Ta operacja dodaje elementy do istniejacego drzewa (nie czysci go).
     * @param tree Referencja do obiektu drzewa BST.
     * @param filename Nazwa pliku tekstowego z danymi (liczby oddzielone bialymi znakami).
     * @return true jesli odczyt sie powiodl, false w przeciwnym razie.
     */
    bool loadFromText(BST& tree, const string& filename);
};
