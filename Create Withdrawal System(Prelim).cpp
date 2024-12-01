#include <iostream>
using namespace std;
int main() {
    
    int balance;
    cout << "Enter your current balance: ";
    cin >> balance;
    
    int withdrawal;
    cout << "Enter the account they wish to withdraw: ";
    cin >> withdrawal;
    
    while (true) {
        if (withdrawal > balance) {
        cout << "Insufficient funds. Please enter valid amount: ";
        cin >> withdrawal;
        }
    
        else if (withdrawal %100!=0) {
            cout<<"Please enter amount that is multiple of 100: ";
            cin >> withdrawal;
        
        } 
        else {
            balance == withdrawal;
            cout << "Withdrawal successful. The balance has been deducted: " << balance << endl;
            break;
        }
    }
    cout << "Final Balance: " << balance << endl;


    return 0;
}
