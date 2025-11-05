#include <iostream>
#include <string>
#include <unordered_set>
#include "functions.h"
using namespace std;

void substringUnique() {
    string s;
    cout << "Введите строку: ";
    cin >> s;
    unordered_set<char> set;
    int left = 0, ans = 0;
    for (int right = 0; right < s.size(); right++) {
        while (set.count(s[right])) set.erase(s[left++]);
        set.insert(s[right]);
        ans = max(ans, right - left + 1);
    }
    cout << "Макс. длина без повторов: " << ans << endl;
}
