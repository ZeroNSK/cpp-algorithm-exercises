#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class BaseballGame {
private:
    stack<int> scores;

public:
    void addScore(int score) {
        scores.push(score);
    }

    void doubleScore() {
        if (!scores.empty()) {
            scores.push(scores.top() * 2);
        }
    }

    void sumLastTwoScores() {
        if (scores.size() >= 2) {
            int top1 = scores.top();
            scores.pop();
            int top2 = scores.top();
            scores.push(top1);
            scores.push(top1 + top2);
        }
    }

    void cancelLastScore() {
        if (!scores.empty()) {
            scores.pop();
        }
    }

    int getTotalScore() const {
        int total = 0;
        stack<int> temp = scores;
        while (!temp.empty()) {
            total += temp.top();
            temp.pop();
        }
        return total;
    }
};
