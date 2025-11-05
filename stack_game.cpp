#include <iostream>
#include <vector>
#include <string>
#include "functions.h"
using namespace std;

void stackGame() {
    vector<int> s;
    string op;

    cout << "Введите операции (число, +, D, C). Для выхода введите 'q':\n";

    while (true) {
        cin >> op;
        if (op == "q" || op == "Q") break;

        if (op == "C" && !s.empty()) s.pop_back();
        else if (op == "D" && !s.empty()) s.push_back(s.back() * 2);
        else if (op == "+" && s.size() >= 2)
            s.push_back(s[s.size() - 1] + s[s.size() - 2]);
        else if ((isdigit(op[0])) || (op[0] == '-' && op.size() > 1))
            s.push_back(stoi(op));
        else
            cout << "Неверная операция: " << op << endl;
    }

    int sum = 0;
    for (int v : s) sum += v;

    cout << "Сумма очков: " << sum << endl;
}
