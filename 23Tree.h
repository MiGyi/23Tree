#pragma once

using namespace std;

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

struct _23Node {
    int low = -1, high = -1;
    _23Node *left = nullptr, *mid = nullptr, *right = nullptr;

    bool isChild();
};

struct _23Tree {
    _23Node* Root = nullptr;

    ~_23Tree();
    void Self_Destruct(_23Node* &Root);

    void Insert(int x);
    _23Node* Split23Node(int x, _23Node* cur);
    _23Node* Promotion(_23Node *Prom, _23Node *cur);
    _23Node* _Insert(int x, _23Node* &cur);

    void Traversal(string s);
    void _Traversal(_23Node* Root, ofstream &fo);
};
