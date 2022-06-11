#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#include "23Tree.h"

bool _23Node::isChild() {
    return left == nullptr && mid == nullptr && right == nullptr;
}

_23Tree::~_23Tree() {
    Self_Destruct(Root);
}

void _23Tree::Self_Destruct(_23Node* &Root) {
    if (Root == nullptr) return;
    Self_Destruct(Root->left);
    Self_Destruct(Root->mid);
    Self_Destruct(Root->right);
    delete Root;
    Root = nullptr;
}

void _23Tree::Insert(int x) {
    _Insert(x, Root);
}

_23Node* _23Tree::Split23Node(int x, _23Node* cur) {

    if (cur->high == -1) {
        cur->high = x;
        if (cur->low > cur->high) swap(cur->low, cur->high);
        return nullptr;
    }

    int l = min({x, cur->low, cur->high}), m = max(cur->low, min(cur->high, x)), r = max({x, cur->low, cur->high});

    cur->low = m; cur->high = -1;
    cur->left = new _23Node; cur->left->low = l;
    cur->mid = new _23Node; cur->mid->low = r;
    return cur;
}

_23Node* _23Tree::Promotion(_23Node *Prom, _23Node *cur) {

    if (cur->high == -1) {

        cur->high = Prom->low;
        if (cur->low > Prom->low) {
            swap(cur->low, cur->high);
            cur->right = cur->mid;
            cur->mid = Prom->mid;
            cur->left = Prom->left;
        }
        else {
            cur->right = Prom->mid;
            cur->mid = Prom->left;
        }

        Prom->left = Prom->mid = Prom->right = nullptr;
        delete Prom;
        return Prom = nullptr;
    }

    if (Prom->low < cur->low) {
        _23Node* res = new _23Node;
        res->low = cur->low;
        res->left = Prom;
        res->mid = cur;
        cur->low = cur->high;
        cur->high = -1;
        cur->left = cur->mid;
        cur->mid = cur->right;
        cur->right = nullptr;
        return res;
    }
    else if (Prom->low > cur->low && Prom->low < cur->high) {
        _23Node* res = new _23Node;
        res->low = Prom->low;
        res->left = cur;
        res->mid = Prom;
        Prom->low = cur->high;
        cur->high = -1;
        cur->mid = Prom->left;
        Prom->left = Prom->mid;
        Prom->mid = cur->right;
        cur->right = nullptr;
        return res;
    }
    else {
        _23Node* res = new _23Node;
        res->low = cur->high;
        res->left = cur;
        res->mid = Prom;
        cur->high = -1;
        cur->right = nullptr;
        return res;
    }

    return nullptr;
}

_23Node* _23Tree::_Insert(int x, _23Node* &cur) {

    if (cur == nullptr) {
        cur = new _23Node({x, -1, nullptr, nullptr, nullptr});
        return nullptr;
    }

    if (cur->isChild()) {
        return Split23Node(x, cur);
    }

    _23Node* Prom = nullptr;
    if (cur->low > x) Prom = _Insert(x, cur->left);
    else if ((cur->low < x && cur->high == -1) || x < cur->high) Prom = _Insert(x, cur->mid);
    else Prom = _Insert(x, cur->right);

    if (Prom == nullptr) return nullptr;
    _23Node* Temp = Promotion(Prom, cur);
    if (cur == Root) {
        if (Temp) Root = Temp;
        return Temp = nullptr;
    }
    return Temp;
}

void _23Tree::Traversal(string s) {
    ofstream fo(s);
    _Traversal(Root, fo);
    fo.close();
}

void _23Tree::_Traversal(_23Node* Root, ofstream &fo) {
    if (Root == nullptr) return;
    _Traversal(Root->left, fo);
    fo << Root->low << " ";
    _Traversal(Root->mid, fo);
    if (Root->high != -1) fo << Root->high << " ";
    _Traversal(Root->right, fo);
}
