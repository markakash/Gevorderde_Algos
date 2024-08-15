#include <iostream>
#include "cmake-build-debug/CMakeFiles/Zoekboom.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Zoekboom tree;

    tree.insert("00001");
    tree.insert("10011");
    tree.insert("00101");
    tree.insert("10010");
    tree.insert("00011");
    tree.insert("01000");
    tree.insert("01001");
    tree.insert("01110");
    tree.insert("00111");


    bool gevonden = tree.contains("11111");
    if (gevonden) {
        std::cout << "We found it " << std::endl;
    } else {
        std::cout << "We didn't find it" << std::endl;
    }


    tree.drawTree();
    tree.drawDotTree("tree.dot");
    return 0;
}
