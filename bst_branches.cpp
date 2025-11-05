#include <iostream>
#include <vector>
#include <algorithm>
#include "avltree.h"
#include "functions.h"
using namespace std;

// рекурсивный поиск узлов, у которых два ребёнка
void findBranches(Node* p, vector<string>& out) {
    if (!p) return;
    if (p->left && p->right)
        out.push_back(p->key);
    findBranches(p->left, out);
    findBranches(p->right, out);
}

void bstBranches() {
    clear(g); // очищаем дерево перед построением нового

    cout << "Введите последовательность целых чисел, заканчивающуюся 0:\n";
    int num;
    while (cin >> num && num != 0) {
        T_insert(to_string(num));
    }

    if (!g) {
        cout << "Дерево пустое.\n";
        return;
    }

    vector<string> nodes;
    findBranches(g, nodes);

    if (nodes.empty()) {
        cout << "Развилок нет.\n";
        return;
    }

    // сортируем по числовому значению
    sort(nodes.begin(), nodes.end(), [](const string& a, const string& b){
        return stoi(a) < stoi(b);
    });

    cout << "Вершины с двумя потомками:\n";
    for (auto& k : nodes)
        cout << k << " ";
    cout << endl;
}
