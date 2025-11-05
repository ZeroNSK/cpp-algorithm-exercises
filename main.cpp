#include <iostream>
#include "functions.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int n;
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Стек — бейсбольная игра\n";
        cout << "2. АТД Множество\n";
        cout << "3. Черепахи\n";
        cout << "4. Гистограмма\n";
        cout << "5. Вывод развилок (BST)\n";
        cout << "6. Самая длинная подстрока\n";
        cout << "7. LFU-кэш\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> n;
        switch (n) {
            case 1: stackGame(); break;
            case 2: setATD(); break;
            case 3: turtles(); break;
            case 4: histogram(); break;
            case 5: bstBranches(); break;
            case 6: substringUnique(); break;
            case 7: lfuCache(); break;
            case 0: return 0;
            default: cout << "Неверный ввод\n";
        }
    }
}
