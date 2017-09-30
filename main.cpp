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
        regex r("P([1-9][0-9]*)\\s*([+\\-*]|cal)\\s*(?:P|[\\-\\+]?)([0-9]+)");
        smatch m;
        if (!regex_search(s, m, r)) {
            cout << "ewwww" << endl;
            return -1;
        }
        string op = m[2];
        int i = stoi(m[1]), j = stoi(m[3]);
        if (op.compare("add")) {
            cout << p[i - 1] + p[j - 1];
        } else if (op.compare("sub")) {
            cout << p[i - 1] - p[j - 1];
        } else if (op.compare("mul")) {
            cout << p[i - 1] * p[j - 1];
        } else if (op.compare("cal")) {
            cout << p[i - 1].calc(j);
        }
        cout << "Do you want to continue this operation? (y/n)";
        cin >> c; 
    } while (c == 'y');
}