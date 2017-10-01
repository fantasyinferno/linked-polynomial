#include <iostream>
#include <regex>

using namespace std;
/*****************************/
/* TESTING PROGRAM FOR REGEX */
/*                           */
/*****************************/

int main() {
    // even moar tests
    regex r("P([1-9][0-9]*)\\s*([\\+\\-\\*]|cal)\\s*(?:P([1-9][0-9]*)|([\\-\\+]?[0-9]+))");
    string good[6] = { "P1 cal 3", "P1 + P2", "P1 * P2", "P1 - P2", "P1 + P3", "P1 * P8"},
            bad[6] = { "P1 - 3", "1 + P3", "P1 / P3", "P1 * P2 + P3", "P1", "P0 + P1"};
    for (int i = 0; i < 6; ++i) {
        cout << "Testing good " << i << ": " << good[i] << endl;
        if (regex_match(good[i], r)) {
            cout << "\tPassed!";
        } else {
            cout << "\tFailed!";
        }
        cout << endl;
    }
    for (int i = 0; i < 6; ++i) {
        cout << "Testing bad " << i << ": " << bad[i] << endl;
        if (!regex_match(bad[i], r)) {
            cout << "\tPassed!";
        } else {
            cout << "\tFailed!";
        }
        cout << endl;
    }
}