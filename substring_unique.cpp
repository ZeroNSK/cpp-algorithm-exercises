#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

class DoubleHashingTable {
private:
    struct Entry {
        string key;
        int value;
        bool occupied;
        bool deleted;
    };
    
    vector<Entry> table;
    int size;

    int hash1(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % size;
        }
        return hash;
    }

    int hash2(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 37 + c) % (size - 1);
        }
        return hash + 1;
    }

public:
    DoubleHashingTable(int size) : table(size), size(size) {
        for (int i = 0; i < size; i++) {
            table[i].occupied = false;
            table[i].deleted = false;
        }
    }

    void insert(const string& key, int value) {
        int index = hash1(key);
        int step = hash2(key);
        int originalIndex = index;
        int probes = 0;

        cout << "ДВОЙН.ХЕШ ВСТАВКА: " << key << "->" << value << " начало в " << index << endl;

        do {
            probes++;
            cout << "Проба " << probes << ": ячейка " << index;

            if (!table[index].occupied || table[index].deleted) {
                table[index] = {key, value, true, false};
                cout << " - свободна" << endl;
                cout << "Размещено в ячейке " << index << endl;
                return;
            }

            if (table[index].key == key) {
                table[index].value = value;
                cout << " - обновлено" << endl;
                return;
            }

            cout << " - занята" << endl;
            index = (index + step) % size;
        } while (index != originalIndex);

        cout << "Таблица переполнена!" << endl;
    }

    bool remove(const string& key) {
        int index = hash1(key);
        int step = hash2(key);
        int originalIndex = index;
        int probes = 0;

        cout << "ДВОЙН.ХЕШ УДАЛЕНИЕ: " << key << " начало в " << index << endl;

        do {
            probes++;
            cout << "Проба " << probes << ": ячейка " << index;

            if (table[index].occupied && !table[index].deleted && table[index].key == key) {
                cout << " - найден" << endl;
                cout << "Удален: " << key << "->" << table[index].value << endl;
                table[index].deleted = true;
                table[index].occupied = false;
                return true;
            }

            if (!table[index].occupied && !table[index].deleted) {
                cout << " - свободна" << endl;
                break;
            }

            cout << " - занята" << endl;
            index = (index + step) % size;
        } while (index != originalIndex);

        cout << "Ключ не найден" << endl;
        return false;
    }

    bool search(const string& key) {
        int index = hash1(key);
        int step = hash2(key);
        int originalIndex = index;
        int probes = 0;

        cout << "ДВОЙН.ХЕШ ПОИСК: " << key << " начало в " << index << endl;

        do {
            probes++;
            cout << "Проба " << probes << ": ячейка " << index;

            if (table[index].occupied && !table[index].deleted && table[index].key == key) {
                cout << " - найден" << endl;
                cout << "Значение: " << table[index].value << endl;
                return true;
            }

            if (!table[index].occupied && !table[index].deleted) {
                cout << " - свободна" << endl;
                break;
            }

            cout << " - занята" << endl;
            index = (index + step) % size;
        } while (index != originalIndex);

        cout << "Не найден" << endl;
        return false;
    }

    void display() {
        cout << "ДВОЙН.ХЕШ: ";
        bool hasData = false;
        for (int i = 0; i < size; i++) {
            if (table[i].occupied && !table[i].deleted) {
                cout << "[" << i << "]" << table[i].key << "->" << table[i].value << " ";
                hasData = true;
            }
        }
        if (!hasData) cout << "пусто";
        cout << endl;
    }
};

class CuckooHashTable {
private:
    struct Entry {
        string key;
        int value;
        bool occupied;
    };
    
    vector<Entry> table1;
    vector<Entry> table2;
    int size;

    int hash1(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % size;
        }
        return hash;
    }

    int hash2(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 37 + c) % size;
        }
        return hash;
    }

public:
    CuckooHashTable(int size) : table1(size), table2(size), size(size) {
        for (int i = 0; i < size; i++) {
            table1[i].occupied = false;
            table2[i].occupied = false;
        }
    }

    void insert(const string& key, int value) {
        int pos1 = hash1(key);
        cout << "КУКУШКА ВСТАВКА: " << key << "->" << value << " в ячейку " << pos1 << endl;
        
        if (table1[pos1].occupied && table1[pos1].key == key) {
            table1[pos1].value = value;
            cout << "Обновлено в таблице 1" << endl;
            return;
        }
        
        int pos2 = hash2(key);
        if (table2[pos2].occupied && table2[pos2].key == key) {
            table2[pos2].value = value;
            cout << "Обновлено в таблице 2" << endl;
            return;
        }
        
        if (!table1[pos1].occupied) {
            table1[pos1] = {key, value, true};
            cout << "Ячейка " << pos1 << " - свободна" << endl;
            cout << "Размещено в ячейке " << pos1 << endl;
            return;
        }

        cout << "Ячейка " << pos1 << " - занята (значение: " << table1[pos1].key << "->" << table1[pos1].value << ")" << endl;
        cout << "Создан новый узел" << endl;
        
        Entry displaced = table1[pos1];
        table1[pos1] = {key, value, true};

        for (int i = 0; i < size; ++i) {
            int pos = hash2(displaced.key);
            cout << "Проба " << (i + 1) << ": ячейка " << pos;
            
            if (!table2[pos].occupied) {
                table2[pos] = displaced;
                cout << " - свободна" << endl;
                cout << "Размещено в ячейке " << pos << endl;
                return;
            }

            cout << " - занята" << endl;
            swap(displaced, table2[pos]);
            pos = hash1(displaced.key);
            
            if (!table1[pos].occupied) {
                table1[pos] = displaced;
                return;
            }
            swap(displaced, table1[pos]);
        }

        cout << "Переполнение таблицы!" << endl;
    }

    bool remove(const string& key) {
        int pos1 = hash1(key);
        cout << "КУКУШКА УДАЛЕНИЕ: " << key << " из ячейки " << pos1 << endl;
        
        if (table1[pos1].occupied && table1[pos1].key == key) {
            cout << "Проба 1: ячейка " << pos1 << " - найден" << endl;
            cout << "Удален: " << key << "->" << table1[pos1].value << endl;
            table1[pos1].occupied = false;
            return true;
        }

        int pos2 = hash2(key);
        if (table2[pos2].occupied && table2[pos2].key == key) {
            cout << "Проба 2: ячейка " << pos2 << " - найден" << endl;
            cout << "Удален: " << key << "->" << table2[pos2].value << endl;
            table2[pos2].occupied = false;
            return true;
        }

        cout << "Ключ не найден" << endl;
        return false;
    }

    bool search(const string& key) {
        int pos1 = hash1(key);
        cout << "КУКУШКА ПОИСК: " << key << " в ячейке " << pos1 << endl;
        
        if (table1[pos1].occupied && table1[pos1].key == key) {
            cout << "Найден за 1 шагов: " << pos1 << endl;
            cout << "Значение: " << table1[pos1].value << endl;
            return true;
        }

        int pos2 = hash2(key);
        if (table2[pos2].occupied && table2[pos2].key == key) {
            cout << "Найден за 2 шагов: " << pos2 << endl;
            cout << "Значение: " << table2[pos2].value << endl;
            return true;
        }

        cout << "Не найден" << endl;
        return false;
    }

    void display() {
        cout << "КУКУШКА: ";
        bool hasData = false;
        for (int i = 0; i < size; i++) {
            if (table1[i].occupied) {
                cout << "[" << i << "]" << table1[i].key << "->" << table1[i].value;
                if (table2[i].occupied) {
                    cout << "->" << table2[i].key << "->" << table2[i].value;
                }
                cout << " ";
                hasData = true;
            } else if (table2[i].occupied) {
                cout << "[" << i << "]" << table2[i].key << "->" << table2[i].value << " ";
                hasData = true;
            }
        }
        if (!hasData) cout << "пусто";
        cout << endl;
    }
};

int longestUniqueSubstring(const string& s) {
    vector<int> lastIndex(256, -1);
    int maxLength = 0;
    int start = 0;

    for (int i = 0; i < s.length(); ++i) {
        if (lastIndex[s[i]] >= start) {
            start = lastIndex[s[i]] + 1;
        }
        lastIndex[s[i]] = i;
        maxLength = max(maxLength, i - start + 1);
    }

    return maxLength;
}

void substringMode() {
    cout << "РЕЖИМ: Самая длинная подстрока без повторяющихся символов" << endl;
    
    while (true) {
        cout << endl;
        cout << "Команды: INPUT строка, BACK" << endl;
        cout << "Введите команду: ";

        string command;
        getline(cin, command);

        if (command == "BACK") break;

        if (command.find("INPUT ") == 0) {
            string input = command.substr(6);
            if (input.empty()) {
                cout << "Ошибка формата! Используйте: INPUT строка" << endl;
                continue;
            }

            int length = longestUniqueSubstring(input);
            cout << "Длина самой длинной подстроки без повторяющихся символов: " << length << endl;
        } else {
            cout << "Ошибка формата! Используйте: INPUT строка или BACK" << endl;
        }
    }
}

void manualHashTableOperations() {
    cout << "УПРАВЛЕНИЕ ХЕШ-ТАБЛИЦАМИ (размер: 10)" << endl;

    DoubleHashingTable doubleHashTable(10);
    CuckooHashTable cuckooTable(10);

    while (true) {
        cout << endl;
        cout << "Команды: INSERT ключ значение, DELETE ключ, SEARCH ключ, BACK" << endl;
        cout << "Введите команду: ";

        string operation;
        getline(cin, operation);

        if (operation == "BACK") break;

        if (operation.find("INSERT ") == 0) {
            size_t spacePos = operation.find(' ', 7);
            if (spacePos == string::npos) {
                cout << "Ошибка формата! Используйте: INSERT ключ значение" << endl;
                continue;
            }
            
            string key = operation.substr(7, spacePos - 7);
            string valueStr = operation.substr(spacePos + 1);
            
            if (key.empty() || valueStr.empty()) {
                cout << "Ошибка формата! Используйте: INSERT ключ значение" << endl;
                continue;
            }
            
            try {
                int value = stoi(valueStr);
                cout << endl;
                cuckooTable.insert(key, value);
                cuckooTable.display();
                cout << endl;
                doubleHashTable.insert(key, value);
                doubleHashTable.display();
            } catch (const exception& e) {
                cout << "Ошибка: неверное число" << endl;
            }
        } else if (operation.find("DELETE ") == 0) {
            string key = operation.substr(7);
            if (key.empty()) {
                cout << "Ошибка формата! Используйте: DELETE ключ" << endl;
                continue;
            }
            
            cout << endl;
            cuckooTable.remove(key);
            cuckooTable.display();
            cout << endl;
            doubleHashTable.remove(key);
            doubleHashTable.display();
        } else if (operation.find("SEARCH ") == 0) {
            string key = operation.substr(7);
            if (key.empty()) {
                cout << "Ошибка формата! Используйте: SEARCH ключ" << endl;
                continue;
            }
            
            cout << endl;
            cuckooTable.search(key);
            cout << endl;
            doubleHashTable.search(key);
        } else {
            cout << "Неизвестная команда!" << endl;
        }
    }
}

// Удалена функция main, чтобы избежать конфликта точек входа.
