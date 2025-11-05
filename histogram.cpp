#include <iostream>
#include <string>
using namespace std;

struct MyArr {
    char* data;
    int size;
    int capacity;
};

void initArray(MyArr& arr) {
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void freeArr(MyArr& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void ensureCapacity(MyArr& arr, int newSize) {
    if (newSize <= arr.capacity) return;
    int newCap = arr.capacity == 0 ? 1 : arr.capacity;
    while (newCap < newSize) newCap *= 2;
    char* newData = new char[newCap];
    for (int i = 0; i < arr.size; ++i)
        newData[i] = arr.data[i];
    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCap;
}

void addEnd(MyArr& arr, char c) {
    ensureCapacity(arr, arr.size + 1);
    arr.data[arr.size++] = c;
}

void arrSort(MyArr& arr) {
    for (int i = 0; i < arr.size - 1; ++i)
        for (int j = 0; j < arr.size - 1 - i; ++j)
            if (arr.data[j] > arr.data[j + 1]) {
                char tmp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = tmp;
            }
}

void countFreq(const MyArr& input, int freq[256]) {
    for (int i = 0; i < 256; ++i)
        freq[i] = 0;

    for (int i = 0; i < input.size; ++i) {
        unsigned char c = input.data[i];
        if (c != ' ' && c != '\n' && c != '\r')
            freq[c]++;
    }
}

int findMax(const int freq[256]) {
    int maxVal = 0;
    for (int i = 0; i < 256; ++i)
        if (freq[i] > maxVal)
            maxVal = freq[i];
    return maxVal;
}

void printHistogram(const MyArr& input) {
    int freq[256];
    countFreq(input, freq);

    MyArr unique;
    initArray(unique);

    for (int i = 0; i < input.size; ++i) {
        unsigned char c = input.data[i];
        if (c == ' ' || c == '\n' || c == '\r') continue;

        bool exists = false;
        for (int j = 0; j < unique.size; ++j)
            if (unique.data[j] == c)
                exists = true;

        if (!exists)
            addEnd(unique, c);
    }

    arrSort(unique);
    int maxH = findMax(freq);

    for (int h = maxH; h > 0; --h) {
        for (int i = 0; i < unique.size; ++i) {
            unsigned char c = unique.data[i];
            if (freq[c] >= h)
                cout << "#";
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < unique.size; ++i)
        cout << unique.data[i];
    cout << endl;

    freeArr(unique);
}

int main() {
    cout << "Введите строку (латиница, цифры, знаки):" << endl;
    string inputLine;
    getline(cin, inputLine);

    MyArr arr;
    initArray(arr);
    for (char c : inputLine)
        addEnd(arr, c);

    cout << "\nГистограмма частот символов:\n";
    printHistogram(arr);

    freeArr(arr);
    return 0;
}
