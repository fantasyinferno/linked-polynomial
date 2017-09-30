#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "polynode.h"
#include <string>

// Polymomial class. Head will contain the highest-degree node
class Polynomial {
    PolyNode* head;
    // recursion helper methods
    static PolyNode* addHelper(PolyNode*, PolyNode*);
    static PolyNode* subtractHelper(PolyNode*, PolyNode*);
    static PolyNode* multiplyHelper(PolyNode*, PolyNode*);
public:
    Polynomial();
    Polynomial(PolyNode*);
    Polynomial(const std::string &s);
    bool add(int, int);
    bool remove(int);
    PolyNode* get(int);
    int calc(int);
    // these operations require recursion to work efficiently
    Polynomial operator+(const Polynomial&);
    Polynomial operator-(const Polynomial&);
    Polynomial operator*(const Polynomial&);
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
};
std::ostream& operator<<(std::ostream&, const Polynomial&);
#endif