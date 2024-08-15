//
// Created by Akash Srivastava on 01/08/2024.
//

#ifndef ZOEKBOOM_H
#define ZOEKBOOM_H
#include <iostream>

#include "Node.h"

using std::cerr;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::pair;
using std::string;

class Zoekboom {
public:
    Node *root;

    Zoekboom() : root(nullptr) {}
    void insert(std::string key);
    bool contains(std::string key);
    void drawrecBinairy(std::ofstream &out, int &nullcounter, Node* node);
    void drawTree(Node* node, int depth);
    void drawDotTree(const char* filename);
    void drawTree();


    ~Zoekboom() {
        delete root;
    }

};



#endif //ZOEKBOOM_H
