#include <iostream>
#include <string>
using namespace std;

struct DynArr {
    int* data;
    int size;
    int capac;
};

void initArr(DynArr& arr, int inCap = 4) {
    if (inCap <= 0) inCap = 4;
    arr.data = new int[inCap];
    arr.size = 0;
    arr.capac = inCap;
}

void freeArr(DynArr& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capac = 0;
}

void resizeArr(DynArr& arr) {
    int newCap = (arr.capac == 0) ? 4 : arr.capac * 2;
    int* newData = new int[newCap];
    for (int i = 0; i < arr.size; i++) {
        newData[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
    arr.capac = newCap;
}

void pushBack(DynArr& arr, int val) {
    if (arr.size >= arr.capac)
        resizeArr(arr);
    arr.data[arr.size++] = val;
}

void copyArr(DynArr& dest, const DynArr& src) {
    dest.data = new int[src.capac];
    dest.size = src.size;
    dest.capac = src.capac;
    for (int i = 0; i < src.size; i++) {
        dest.data[i] = src.data[i];
    }
}


struct TurtleInfo {
    int ahead;
    int behind;
};

void initTurtleArr(TurtleInfo*& arr, int count) {
    arr = new TurtleInfo[count];
}

void freeTurtleArr(TurtleInfo*& arr) {
    delete[] arr;
    arr = nullptr;
}

// Проверка, может ли конкретная черепаха говорить правду
bool checkTurtle(int idx, const TurtleInfo& t, int n) {
    int total = t.ahead + t.behind + 1; // включая саму черепаху
    return (total == n && t.ahead >= 0 && t.behind >= 0 && t.ahead < n && t.behind < n);
}

// Подсчёт максимального числа правдивых черепах
int countHonestTurtles(const TurtleInfo* arr, int n) {
    int honestCount = 0;
    for (int i = 0; i < n; i++) {
        if (checkTurtle(i, arr[i], n))
            honestCount++;
    }
    return honestCount;
}

int main() {
    cout << "Введите количество черепах: ";
    int n;
    cin >> n;

    if (n <= 0) {
        cout << "Ошибка: количество черепах должно быть положительным." << endl;
        return 1;
    }

    TurtleInfo* turtles;
    initTurtleArr(turtles, n);

    cout << "Введите для каждой черепахи два числа (впереди и позади):\n";
    for (int i = 0; i < n; i++) {
        cin >> turtles[i].ahead >> turtles[i].behind;
    }

    int result = countHonestTurtles(turtles, n);
    cout << "Максимальное количество черепах, которые могут говорить правду: " << result << endl;

    freeTurtleArr(turtles);
    return 0;
}
