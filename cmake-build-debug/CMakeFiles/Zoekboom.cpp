//
// Created by Akash Srivastava on 01/08/2024.
//

#include "Zoekboom.h"

#include <fstream>

#include "iostream"

void Zoekboom::insert(std::string key) {
    if (root == nullptr) {
        root = new Node(key);
    }
    else {
        Node *newNode = new Node(key);
        Node *current = root;
        Node *parent = nullptr;
        int splitbit = 0;

        while (current != nullptr) {
            parent = current;
            if (key[splitbit] == '0') {
                current = current->leftChild;
            } else if (key[splitbit] == '1') {
                current = current->rightChild;
            }
            splitbit++;
        }
        newNode->parent = parent;
        if (key[splitbit - 1] == '0') {
            parent->leftChild = newNode;
        } else {
            parent->rightChild = newNode;
        }
    }
}

bool Zoekboom::contains(std::string key) {
    Node *current = root;
    bool gevonden = false;
    int i = 0;
    while (current != nullptr) {
        if (current->value == key) {
            gevonden = true;
        } if (key[i] == '0') {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
        i++;
    }
    return gevonden;
}

void Zoekboom::drawTree() {
    drawTree(root, 0);
}

void Zoekboom::drawTree(Node* node, int depth) {
    std::string prefix = "     ";

    if (node) {
        for (int i = 0; i < depth; i++) {
            std::cout << prefix;
        }

        std::cout << node->value << std::endl;

        drawTree(node->leftChild, depth + 1);
        drawTree(node->rightChild, depth + 1);
    }
}

void Zoekboom::drawDotTree(const char* filename) {
    ofstream out(filename);
    if (out.is_open()) {
        out << "digraph {" << std::endl;
        int nullcounter = 0;
        drawrecBinairy(out, nullcounter, root);
        out << "}" << std::endl;
        out.close();
    } else {
        std::cerr << "Could not open file " << filename << " for writing." << std::endl;
    }
}

void Zoekboom::drawrecBinairy(std::ofstream &out, int &nullcounter, Node* node) {
    if (node) {
        out << "    " << node->value << " [label=\"" << node->value << "\"];" << std::endl;

        if (node->leftChild) {
            out << "    " << node->value << " -> " << node->leftChild->value << ";" << std::endl;
            drawrecBinairy(out, nullcounter, node->leftChild);
        } else {
            out << "    null" << nullcounter << " [shape=point];" << std::endl;
            out << "    " << node->value << " -> null" << nullcounter << ";" << std::endl;
            nullcounter++;
        }

        if (node->rightChild) {
            out << "    " << node->value << " -> " << node->rightChild->value << ";" << std::endl;
            drawrecBinairy(out, nullcounter, node->rightChild);
        } else {
            out << "    null" << nullcounter << " [shape=point];" << std::endl;
            out << "    " << node->value << " -> null" << nullcounter << ";" << std::endl;
            nullcounter++;
        }
    }
}

