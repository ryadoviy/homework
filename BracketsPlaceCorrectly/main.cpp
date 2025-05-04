#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& input) {
    stack<char> s;
    for (char c : input) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) return false;

            char top = s.top();
            s.pop();

            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }    return s.empty();
}

int main() {
    string input;
    cout << "Enter an expression with brackets: ";
    getline(cin, input);

    if (isBalanced(input)) {
        cout << "Brackets are balanced." << endl;
    }
    else {
        cout << "Brackets are not balanced." << endl;
    }

    return 0;
}
