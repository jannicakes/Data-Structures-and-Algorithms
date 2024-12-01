#include <iostream>
using namespace std;

int main() {
    int exam1, exam2, exam3, average;

    cout << "Enter the score for Exam 1:";
    cin >> exam1;

    cout << "Enter the score for Exam 2:";
    cin >> exam2;

    cout << "Enter the score for Exam 3:";
    cin >> exam3;
    
    average = (exam1 + exam2 + exam3) /3;

    cout << "Average score: " << average << endl;
    
    
    if (average >= 70) {
        cout << "Result: Passed" << endl;

    } else {
        cout << "Result: Failed" << endl;
    }

    return 0;
}