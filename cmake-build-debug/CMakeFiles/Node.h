//
// Created by Akash Srivastava on 01/08/2024.
//

#ifndef NODE_H
#define NODE_H

#include "iostream"



class Node {
public:
    std::string value;
    Node *leftChild;
    Node *rightChild;
    Node *parent;

    Node(std::string value) : value(value), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {};

    ~Node() {
        delete leftChild;
        delete rightChild;
    }
};



#endif //NODE_H
