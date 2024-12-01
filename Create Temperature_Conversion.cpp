#include <iostream>
using namespace std;

int main() {
    float celsius,fahrenheit;
    char x;

    cout << "Enter temperature: ";
    cin >> x;

    if (x == 'c') {
        cout << "Enter a number: ";
        cin >> celsius;
        fahrenheit = (celsius * 9.0) / 5 + 32;
        cout << fahrenheit << endl;


    } else if (x == 'f') {
        cout << "Enter a number: ";
        cin >> fahrenheit;
        celsius = (fahrenheit - 32) * (5 / 9);
        cout << celsius << endl;


    
    }
    return 0;
}
