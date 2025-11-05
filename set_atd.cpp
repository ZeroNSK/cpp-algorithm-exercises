#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int HASH_TABLE = 1009;

struct Node {
    string val;
    Node* next;
};

struct CustomHash {
    Node** buckets;
    int tableSize;
};

unsigned long hashFunc(const string& str) {
    unsigned long hash = 5381;
    for (char c : str)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

void initializeSet(CustomHash& set) {
    set.tableSize = HASH_TABLE;
    set.buckets = new Node*[set.tableSize];
    for (int i = 0; i < set.tableSize; i++)
        set.buckets[i] = nullptr;
}

void freeSet(CustomHash& set) {
    for (int i = 0; i < set.tableSize; i++) {
        Node* curr = set.buckets[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    delete[] set.buckets;
}

bool checkElem(const CustomHash& set, const string& elem) {
    int idx = hashFunc(elem) % set.tableSize;
    Node* curr = set.buckets[idx];
    while (curr) {
        if (curr->val == elem) return true;
        curr = curr->next;
    }
    return false;
}

void addElem(CustomHash& set, const string& elem) {
    if (checkElem(set, elem)) {
        cout << "Элемент \"" << elem << "\" уже есть в множестве\n";
        return;
    }
    int idx = hashFunc(elem) % set.tableSize;
    Node* newNode = new Node{elem, set.buckets[idx]};
    set.buckets[idx] = newNode;
    cout << "лемент \"" << elem << "\" добавлен\n";
}

void removeElem(CustomHash& set, const string& elem) {
    int idx = hashFunc(elem) % set.tableSize;
    Node* curr = set.buckets[idx];
    Node* prev = nullptr;

    while (curr) {
        if (curr->val == elem) {
            if (prev) prev->next = curr->next;
            else set.buckets[idx] = curr->next;
            delete curr;
            cout << "Элемент \"" << elem << "\" удалён\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Элемент \"" << elem << "\" не найден\n";
}

// Загрузка множества из файла
bool loadFromFile(CustomHash& set, const string& path) {
    ifstream fin(path);
    if (!fin.is_open()) {
        cout << "Файл не найден: " << path << "\n";
        return false;
    }

    string word;
    while (fin >> word)
        addElem(set, word);

    fin.close();
    cout << "Данные успешно загружены из " << path << endl;
    return true;
}


void printSet(const CustomHash& set) {
    bool empty = true;
    cout << "\nТекущее множество:\n";
    for (int i = 0; i < set.tableSize; i++) {
        Node* curr = set.buckets[i];
        while (curr) {
            cout << "  • " << curr->val << endl;
            curr = curr->next;
            empty = false;
        }
    }
    if (empty) cout << "(пусто)\n";
}

int main() {
    CustomHash mySet;
    initializeSet(mySet);

    string file, cmd, elem;
    cout << "Введите путь к файлу данных: ";
    getline(cin, file);

    if (!loadFromFile(mySet, file))
        cout << "Создано пустое множество.\n";

    printSet(mySet);

    while (true) {
        cout << "\nВведите команду (SETADD, SETDEL, SET_AT, EXIT): ";
        cin >> cmd;
        for (auto& c : cmd) c = toupper(c);

        if (cmd == "EXIT") break;

        cout << "Введите элемент: ";
        cin >> elem;

        if (cmd == "SETADD") addElem(mySet, elem);
        else if (cmd == "SETDEL") removeElem(mySet, elem);
        else if (cmd == "SET_AT")
            cout << (checkElem(mySet, elem)
                     ? "Элемент найден\n"
                     : "Элемент отсутствует\n");
        else
            cout << "Неизвестная команда.\n";

        printSet(mySet);
    }

    freeSet(mySet);
    cout << "\nЗавершение программы.\n";
    return 0;
}
