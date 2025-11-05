#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

struct LFUCacheEntry {
    int key;
    int value;
    int frequency;
};

class LFUCache {
private:
    int capacity;
    unordered_map<int, list<LFUCacheEntry>::iterator> cacheMap;
    unordered_map<int, list<LFUCacheEntry>> frequencyMap;
    int minFrequency;

public:
    LFUCache(int cap) : capacity(cap), minFrequency(0) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        auto entry = cacheMap[key];
        int value = entry->value;
        int frequency = entry->frequency;

        frequencyMap[frequency].erase(entry);
        if (frequencyMap[frequency].empty()) {
            frequencyMap.erase(frequency);
            if (minFrequency == frequency) {
                minFrequency++;
            }
        }

        frequency++;
        frequencyMap[frequency].push_front({key, value, frequency});
        cacheMap[key] = frequencyMap[frequency].begin();

        return value;
    }

    void set(int key, int value) {
        if (capacity == 0) {
            return;
        }

        if (cacheMap.find(key) != cacheMap.end()) {
            auto entry = cacheMap[key];
            int frequency = entry->frequency;

            frequencyMap[frequency].erase(entry);
            if (frequencyMap[frequency].empty()) {
                frequencyMap.erase(frequency);
                if (minFrequency == frequency) {
                    minFrequency++;
                }
            }

            frequency++;
            frequencyMap[frequency].push_front({key, value, frequency});
            cacheMap[key] = frequencyMap[frequency].begin();
        } else {
            if (cacheMap.size() == capacity) {
                auto lfuEntry = frequencyMap[minFrequency].back();
                cacheMap.erase(lfuEntry.key);
                frequencyMap[minFrequency].pop_back();
                if (frequencyMap[minFrequency].empty()) {
                    frequencyMap.erase(minFrequency);
                }
            }

            minFrequency = 1;
            frequencyMap[minFrequency].push_front({key, value, minFrequency});
            cacheMap[key] = frequencyMap[minFrequency].begin();
        }
    }
};

int read_integer_safely() {
    int number;
    while (!(cin >> number)) {
        cout << "Ошибка: Введите корректное целое число: ";
        cin.clear();
        cin.ignore(1024, '\n');
    }
    cin.ignore(1024, '\n');
    return number;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int capacity;
    int numQueries;

    cout << "Введите емкость кэша (cap): ";
    capacity = read_integer_safely();
    if (capacity <= 0) {
        cout << "Ошибка: Емкость кэша должна быть положительным числом." << endl;
        return 1;
    }

    cout << "Введите количество запросов (Q): ";
    numQueries = read_integer_safely();
    if (numQueries < 0) {
        cout << "Ошибка: Количество запросов не может быть отрицательным." << endl;
        return 1;
    }

    LFUCache cache(capacity);

    cout << "Введите запросы (например: SET 1 2 или GET 1):" << endl;

    string command;
    int key;
    int value;

    for (int i = 0; i < numQueries; ++i) {
        cin >> command;

        if (command == "SET") {
            if (!(cin >> key >> value)) {
                cout << "Ошибка: Некорректный формат SET. Ожидается: SET ключ значение" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
                continue;
            }
            cache.set(key, value);
        } else if (command == "GET") {
            if (!(cin >> key)) {
                cout << "Ошибка: Некорректный формат GET. Ожидается: GET ключ" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
                continue;
            }
            cout << cache.get(key) << endl;
        } else {
            cout << "Ошибка: Неизвестная команда '" << command << "'. Допустимы SET и GET." << endl;
            cin.ignore(1024, '\n');
        }
    }

    return 0;
}