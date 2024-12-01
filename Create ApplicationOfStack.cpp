#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Function to define precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to perform arithmetic operations
int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // Assuming integer division for simplicity
    }
    return 0;
}

// Function to evaluate an infix expression
int evaluateInfix(const string &expression) {
    stack<int> values;    // Stack to store integer values
    stack<char> operators; // Stack to store operators
    
    for (int i = 0; i < expression.length(); i++) {
        // Skip whitespaces
        if (expression[i] == ' ')
            continue;

        // If the current character is a number, push it to the values stack
        if (isdigit(expression[i])) {
            int val = 0;
            
            // There may be more than one digit in the number
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            
            values.push(val);
            i--; // To balance the loop increment
        }
        // If the current character is an opening bracket, push it to operators stack
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }
        // If the current character is a closing bracket, solve the bracket
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                int val2 = values.top();
                values.pop();
                
                int val1 = values.top();
                values.pop();
                
                char op = operators.top();
                operators.pop();
                
                values.push(applyOperator(val1, val2, op));
            }
            // Pop the opening bracket
            operators.pop();
        }
        // If the current character is an operator
        else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                int val2 = values.top();
                values.pop();
                
                int val1 = values.top();
                values.pop();
                
                char op = operators.top();
                operators.pop();
                
                values.push(applyOperator(val1, val2, op));
            }
            
            // Push the current operator to operators stack
            operators.push(expression[i]);
        }
    }
    
    // Entire expression has been parsed, apply remaining operators
    while (!operators.empty()) {
        int val2 = values.top();
        values.pop();
        
        int val1 = values.top();
        values.pop();
        
        char op = operators.top();
        operators.pop();
        
        values.push(applyOperator(val1, val2, op));
    }
    
    // The top of values contains the result
    return values.top();
}

int main() {
    string expression;
    
    // Get infix expression from the user
    cout << "Enter an infix expression: ";
    getline(cin, expression);
    
    // Evaluate the infix expression
    int result = evaluateInfix(expression);
    
    cout << "The result of the expression " << expression << " is: " << result << endl;
    
    return 0;
}
