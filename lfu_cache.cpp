#include <iostream>
#include <unordered_map>
#include "functions.h"
using namespace std;

struct LFU {
    int cap;
    unordered_map<int,pair<int,int>> m;  // счетчик ключ : значение/частота встречаемости
    LFU(int c): cap(c) {}
    void set(int k, int v) { 
        if (m.size() == cap) { 
            int minf = 1e9, del = -1;
            for (auto &p : m)
                if (p.second.second < minf) // если у нас при попытке записи в новый элемент и с забитой таблицей, старый - реже всех используется
                    minf = p.second.second, del = p.first; // то мы его стираем и записываем на его место в памяти новый.
            m.erase(del); 
        }
        m[k] = {v, 1};
    }
    int get(int k) {
        if (!m.count(k)) return -1;
        m[k].second++;
        return m[k].first;
    }
};

void lfuCache() {
    int cap;
    cout << "Введите емкость кэша: ";
    cin >> cap;
    LFU l(cap);
    string cmd; int x,y;
    cout << "Команды: SET x y / GET x / end\n";
    while (cin >> cmd && cmd != "end") {
        if (cmd == "SET") { cin >> x >> y; l.set(x,y); }
        else if (cmd == "GET") { cin >> x; cout << l.get(x) << endl; }
    }
}
