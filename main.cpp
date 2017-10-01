#include <iostream>
#include <vector>
#include <string>
#include "polynomial.h"
#include <regex>
using namespace std;

int main() {
    // p contains the polynomials to be inserted
    vector<Polynomial> p;
    char c = 'y';
    
    // loop to enter polynomials
    do {
        cout << "Enter a polynomial: ";
        string s;
        getline(cin, s);
        Polynomial pol(s);
        p.push_back(pol);
        cout << "Your polynomial is " << pol << endl;
        cout << "Do you want to continue this operation? (y/n)";
        cin >> c;
        getline(cin, s);
    } while (c == 'y');
    
    // loop to enter and process operations
    c = 'y';
    do {
        cout << "Enter an operator: ";
        string s;
        getline(cin, s);
        // i, j contain the indices of the polynomials specified by the operands
        // x will contain the value to be evaluated in the case of "cal"
        // operator is stored in op
        regex r("P([1-9][0-9]*)\\s*(\\+|\\-|\\*|cal)\\s*(?:P([1-9][0-9]*)|([\\-\\+]?[0-9]+))");
        smatch m;
        if (!regex_search(s, m, r)) {
            cout << "ewwww" << endl;
            return -1;
        }
        string op = m[2], secondParam = (m[3] == "") ? m[4] : m[3];
        int i = stoi(m[1]), j = stoi(secondParam);
        if (op == "+") {
            cout << "add me" << endl;
            cout << p[i - 1] + p[j - 1];
        } else if (op == "-") {
            cout << "subtract me" << endl;
            cout << p[i - 1] - p[j - 1];
        } else if (op == "*") {
            cout << p[i - 1] * p[j - 1];
        } else if (op == "cal") {
            cout << p[i - 1].calc(j);
        }
        cout << endl << "Do you want to continue this operation? (y/n)";
        cin >> c; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (c == 'y');
}