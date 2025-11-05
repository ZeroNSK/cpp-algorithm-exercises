#include <iostream>
#include <unordered_set>
#include <fstream>
#include <string>
#include "functions.h"
using namespace std;

void setATD() {
    string fileName = "set_data.txt";
    unordered_set<int> s;
    string cmd;
    int x;

    ifstream fin(fileName);
    if (fin.is_open()) {
        while (fin >> x) s.insert(x);
        fin.close();
        cout << "Загружено " << s.size() << " элементов из " << fileName << endl;
    } else {
        cout << "Файл не найден, создано новое множество.\n";
    }

    cout << "Введите команды (SETADD x, SETDEL x, SET_AT x). Для выхода: end\n";

    while (cin >> cmd && cmd != "end") {
        if (cmd == "SETADD") {
            cin >> x;
            s.insert(x);
        } else if (cmd == "SETDEL") {
            cin >> x;
            s.erase(x);
        } else if (cmd == "SET_AT") {
            cin >> x;
            cout << (s.count(x) ? "Есть\n" : "Нет\n");
        } else {
            cout << "Неизвестная команда\n";
        }
    }

    ofstream fout(fileName, ios::trunc);
    for (int val : s) fout << val << " ";
    fout.close();
    cout << "Множество сохранено в " << fileName << endl;
}
