#include <iostream>
#include <regex>

using namespace std;
/*****************************/
/* TESTING PROGRAM FOR REGEX */
/*                           */
/*****************************/


int main() {
    // regular expression used to check if a string represents a polynomial
    regex r("(?:\\s*([\\-\\+]?)\\s*([0-9]+)(?:\\*?(x)(?:\\^?([0-9]+)?))?)+?");

    // valid testcases
    string good[9] = { "5x5+4x4+3x3+2x2+1x1+0",
                    "5000*x^9 + 4*x^2 + 3*x^3 + 2*x^2 + 1*x^1 + 0",
                    "-5*x^10 - 4*x^4 + 3*x^3 - 2*x^2 + 1*x^1 + 0",
                    "5x7   +   4*x^4+3*x3",
                    "5x^5 + 4x1000000000",
                    "1x + 0",
                    "66x+66+66+66+6",
                    "0",
                    ""
    };
    // bad test cases
    string bad[9] = { "5d5 + 4x4 + 3x3 + 2x2 + 1x1 + 0",
                        "6*x*6*6 + 10",
                        "7*x^x + 8",
                        "9*x + 12*x3 + -144*x",
                        "66x+66+66+66+66x38-2x*x10",
                        "38 / 2 + 61",
                        "x^2+x^3 / 108",
                        "x64+x^3 / 15",
                        "x0 + x98 + x98 - 2 / 9"
                        };
    // regex_match should return true
    for (int i = 0; i < 8; ++i) {
        cout << "Testing good " << i << ": " << good[i] << endl;
        if (regex_match(good[i], r)) {
            cout << "\tPassed!";
        } else {
            cout << "\tFailed!";
        }
        cout << endl;
    }
    // regex_match should return false
    cout << "--------------------------" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << "Testing bad " << i << ": " << bad[i] << endl;
        if (!regex_match(bad[i], r)) {
            cout << "\tPassed!";
        } else {
            cout << "\tFailed!";
        }
        cout << endl;
    }
    // get ax^b, a*x^b, axb or a
    for (int i = 0; i < 8; ++i) {
        auto wordsBegin = sregex_iterator(good[i].begin(), good[i].end(), r);
        auto wordsEnd = sregex_iterator();

        for (sregex_iterator j = wordsBegin; j != wordsEnd; ++j) {
            smatch match = *j;
            string sign = match.str(1), value = match.str(2), x = match.str(3), degree = match.str(4);
            cout << sign << value << x << degree << " ";
        }
        cout << endl;
    }


}