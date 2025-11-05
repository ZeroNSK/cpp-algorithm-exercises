#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Node {
    std::string key;
    int h;
    Node* left;
    Node* right;
};

bool T_load(const std::string& file);
bool T_save(const std::string& file);
void T_insert(const std::string& k);
void T_erase(const std::string& k);
bool T_get(const std::string& k);
void T_print();
void clear(Node*& p);
extern Node* g;

#endif
