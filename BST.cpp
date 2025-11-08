/**
 * @file BST.cpp
 * @brief Implementacja metod klasy BST.
 */

#include "BST.h"
#include <iostream>

using namespace std;

 // --- Konstruktor i Destruktor ---

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear(root);
}

// --- Prywatne metody pomocnicze ---

void BST::clear(Node* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

BST::Node* BST::insert(Node* node, int data) {
    if (node == nullptr) {
        return new Node(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    // Jesli data == node->data, nie robimy nic (brak duplikatow)
    return node;
}

BST::Node* BST::findMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BST::Node* BST::remove(Node* node, int data) {
    if (node == nullptr) {
        return node;
    }

    if (data < node->data) {
        node->left = remove(node->left, data);
    }
    else if (data > node->data) {
        node->right = remove(node->right, data);
    }
    else {
        // Znaleziono wezel do usuniecia

        // Case 1: Brak dziecka lub jedno dziecko
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 2: Dwoje dzieci
        Node* temp = findMin(node->right); // Znajdz nastepnika (najmniejszy w prawym poddrzewie)
        node->data = temp->data; // Skopiuj dane nastepnika do tego wezla
        node->right = remove(node->right, temp->data); // Usun nastepnika
    }
    return node;
}

bool BST::findPath(Node* node, int data, vector<int>& path) {
    if (node == nullptr) {
        return false;
    }

    path.push_back(node->data);

    if (node->data == data) {
        return true;
    }

    if ((data < node->data && findPath(node->left, data, path)) ||
        (data > node->data && findPath(node->right, data, path))) {
        return true;
    }

    // Jesli nie znaleziono w poddrzewach, usun bieżący wezel ze sciezki (backtracking)
    path.pop_back();
    return false;
}

// --- Metody wyswietlania ---

void BST::printPreorder(Node* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

void BST::printInorder(Node* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

void BST::printPostorder(Node* node) {
    if (node == nullptr) return;
    printPostorder(node->left);
    printPostorder(node->right);
    cout << node->data << " ";
}

void BST::printGraphical(Node* node, int space, int count) {
    if (node == nullptr) {
        return;
    }
    space += count;

    printGraphical(node->right, space, count);

    cout << endl;
    for (int i = count; i < space; i++) {
        cout << " ";
    }
    cout << node->data << "\n";

    printGraphical(node->left, space, count);
}

// --- Metody pomocnicze do zapisu/odczytu ---

void BST::saveToText(Node* node, ofstream& outFile) {
    if (node == nullptr) {
        return;
    }
    // Zapisujemy Inorder, aby plik tekstowy byl posortowany
    saveToText(node->left, outFile);
    outFile << node->data << "\n";
    saveToText(node->right, outFile);
}

void BST::serialize(Node* node, ofstream& outFile) {
    // Uzywamy Preorder do serializacji, aby zachowac strukture
    if (node == nullptr) {
        // Zapisz znacznik 'false' oznaczajacy null
        bool marker = false;
        outFile.write(reinterpret_cast<const char*>(&marker), sizeof(bool));
        return;
    }
    // Zapisz znacznik 'true' oznaczajacy wezel
    bool marker = true;
    outFile.write(reinterpret_cast<const char*>(&marker), sizeof(bool));
    // Zapisz dane wezla
    outFile.write(reinterpret_cast<const char*>(&(node->data)), sizeof(int));

    serialize(node->left, outFile);
    serialize(node->right, outFile);
}

BST::Node* BST::deserialize(ifstream& inFile) {
    bool marker;
    inFile.read(reinterpret_cast<char*>(&marker), sizeof(bool));

    // Jesli odczyt sie nie powiodl (np. koniec pliku) lub marker to false
    if (!inFile || !marker) {
        return nullptr;
    }

    int data;
    inFile.read(reinterpret_cast<char*>(&data), sizeof(int));

    Node* node = new Node(data);
    node->left = deserialize(inFile);
    node->right = deserialize(inFile);

    return node;
}


// --- Publiczne metody (wrappery) ---

void BST::insert(int data) {
    root = insert(root, data);
}

void BST::remove(int data) {
    root = remove(root, data);
}

void BST::clear() {
    clear(root);
    root = nullptr;
}

vector<int> BST::findPath(int data) {
    vector<int> path;
    findPath(root, data, path);
    return path;
}

void BST::display() {
    if (root == nullptr) {
        cout << "Drzewo jest puste." << endl;
        return;
    }

    int choice;
    cout << "\n--- Wybierz metode wyswietlania ---\n";
    cout << "1. Preorder (Korzen, Lewo, Prawo)\n";
    cout << "2. Inorder (Lewo, Korzen, Prawo)\n";
    cout << "3. Postorder (Lewo, Prawo, Korzen)\n";
    cout << "4. Graficznie (orientacja pozioma)\n";
    cout << "Wybór: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Preorder: ";
        printPreorder(root);
        break;
    case 2:
        cout << "Inorder: ";
        printInorder(root);
        break;
    case 3:
        cout << "Postorder: ";
        printPostorder(root);
        break;
    case 4:
        cout << "Drzewo (obrocone o 90 stopni w lewo):\n";
        printGraphical(root, 0, 10);
        break;
    default:
        cout << "Nieprawidlowy wybor." << endl;
        break;
    }
    cout << endl;
}
