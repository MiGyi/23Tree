#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#include "23Tree.h"

int main()
{
    ifstream fi("input.txt");

    int num;
    _23Tree Tree;
    while (fi >> num) {
        Tree.Insert(num);
    }
    fi.close();
    Tree.Traversal("output.txt");
    return 0;
}
