#include <iostream>
#include <vector>
#include "functions.h"
using namespace std;

void turtles() {
    int n;
    cout << "Введите число черепах: ";
    cin >> n;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    int ans = 0;
    for (int i = 0; i < n; i++)
        if (a[i].first + a[i].second == n - 1) ans++;
    cout << "Макс. правдивых черепах: " << ans << endl;
}
