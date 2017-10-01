#include "polynomial.h"
#include "polynode.h"
#include <regex>
#include <stdexcept>
#include <cmath>
using namespace std;

Polynomial::Polynomial() {
    head = 0;
}
Polynomial::Polynomial(PolyNode *node) {
    head = node;
}
Polynomial::Polynomial(const string &s): Polynomial() {
    // regex for checking the string format and capturing the necessary parts of each term (value, x, degree)
    regex r("(?:\\s*([\\-\\+]?)\\s*([0-9]+)(?:\\*?(x)(?:\\^?([0-9]+)?))?)+?");
    if (!regex_match(s, r)) {
        throw std::invalid_argument("String must represent a polynomial");
    }
    auto begin = sregex_iterator(s.begin(), s.end(), r);
    auto end = sregex_iterator();
    smatch m;
    for (sregex_iterator i = begin; i != end; ++i) {
        m = *i;
        // 1 is the sign, 2 is the value, 3 is x, 4 is the degree
        int value = stoi(m.str(1) + m.str(2)), degree = 0;
        if (m.str(4).empty()) {
            if (m.str(3) == "x") {
                degree = 1;
            } else {
                degree = 0;
            }
        } else {
            degree = stoi(m.str(4));
        }
        add(value, degree);
    }
}
bool Polynomial::add(int value, int degree) {
    // check if a node with such degree already exists
    PolyNode *target = get(degree);
    if (target == 0) {
        // if it doesn't, create one
        PolyNode *toBeInserted = new PolyNode(value, degree, 0);
        // check if there is still memory
        if (toBeInserted == 0) {
            return 0;
        }
        // insert the node before head if its degree is highest
        
        if (head == 0 || head->degree < degree) {
            toBeInserted->next = head;
            head = toBeInserted;
        } else {
            // insert in the middle and at the end
            PolyNode *pPre = 0, *pLoc = head;
            while (pLoc != 0) {
                if (pLoc->degree < toBeInserted->degree) {
                    break;
                }
                pPre = pLoc;
                pLoc = pLoc->next;
            }
            pPre->next = toBeInserted;
            toBeInserted->next = pLoc;
        }
    } else {
        // if such a node exists, add to it's value
        target->data += value;
    }
    return 1;
}
bool Polynomial::remove(int degree) {
    /* Please help improve this function */
    PolyNode *pPre = 0, *pLoc = head;
    while (pLoc != 0) {
        if (pLoc->degree == degree) {
            // delete node at the middle and at the end
            if (pPre != 0) {
                pPre->next = pLoc->next;
                delete pLoc;
            } 
            // delete node at the beginning
            else {
                PolyNode* toBeDeleted = head;
                head = head->next;
                delete head;
            }
            return true;
        }
        pPre = pLoc;
        pLoc = pLoc->next;
    }
    return false;
}
PolyNode* Polynomial::get(int degree) {
    // this function gets a node :D
    PolyNode* walker = head;
    while (walker != 0) {
        if (walker->degree == degree) {
            return walker;
        }
        walker = walker->next;
    }
    return 0;
}

PolyNode* Polynomial::addHelper(PolyNode* a, PolyNode* b) {
    // if both node pointers are null, we are done. Return.
    if (a == 0 && b == 0) {
        return 0;
    }
    if (a == 0) {
        return new PolyNode(b->data, b->degree, 0);
    }
    if (b == 0) {
        return new PolyNode(a->data, a->degree, 0);
    }
    PolyNode* head;
   
    if (a->degree > b->degree) {
        // if a's degree is larger than b's, put it in first and increment a
        head = new PolyNode(a->data, a->degree, 0);
        head->next = addHelper(a->next, b);
    } else if (a->degree < b->degree) {
        // put b in first and increment b
        head = new PolyNode(b->data, b->degree, 0);
        head->next = addHelper(a, b->next);
    } else {
        // add if their degrees are equal
        head = new PolyNode(a->data + b->data, a->degree, 0);
        head->next = addHelper(a->next, b->next);
    }
    // return all the way up to the first
    return head;
}
PolyNode* Polynomial::subtractHelper(PolyNode* a, PolyNode* b) {
    // basically the same as above
    if (a == 0 && b == 0) {
        return 0;
    }
    if (a == 0) {
        return new PolyNode(-b->data, b->degree, 0);
    }
    if (b == 0) {
        return new PolyNode(a->data, a->degree, 0);
    }
    PolyNode* head;
    if (a->degree > b->degree) {
        head = new PolyNode(a->data, a->degree, 0);
        head->next = subtractHelper(a->next, b);
    } else if (a->degree < b->degree) {
        head = new PolyNode(-b->data, b->degree, 0);
        head->next = subtractHelper(a, b->next);
    } else {
        head = new PolyNode(a->data - b->data, a->degree, 0);
        head->next = subtractHelper(a->next, b->next);
    }
    return head;
}
PolyNode* Polynomial::multiplyHelper(PolyNode* a, PolyNode* b) {
    
}

Polynomial Polynomial::operator+(const Polynomial& o) {
    return Polynomial(addHelper(this->head, o.head));
}
Polynomial Polynomial::operator-(const Polynomial& o) {
    return Polynomial(subtractHelper(this->head, o.head));
}
Polynomial Polynomial::operator*(const Polynomial& o) {
    return Polynomial(multiplyHelper(this->head, o.head));
}

// evaluate the polynomial with a specific value of x
int Polynomial::calc(int x) {
    PolyNode* walker = head;
    int sum = 0;
    while (walker != 0) {
        sum += (int) walker->data * pow(x, walker->degree);
        walker = walker->next;
    }
    return sum;
}
/* Iterative solution. Don't know how to return the head of the polynomial.
Polynomial Polynomial::operator+(const Polynomial& o) {
    PolyNode *ret, *walker3, *walker1 = this->head, *walker2 = o.head;
    while (walker1! = 0 && walker2 != 0) {
        if (walker1->degree > walker2->degree) {
            walker3 = new PolyNode(walker1->data, walker1->degree, 0);
            walker1 = walker1->next;
        } else if (walker1->degree < walker2->degree) {
            walker3 = new PolyNode(walker2->data, walker2->degree, 0);
            walker2 = walker2->next;            
        } else {
            walker3 = new PolyNode(walker1->data + walker2->data, walker1->degree, 0);
            walker1 = walker1->next;
            walker2 = walker2->next;
        }
        walker3 = walker3->next;
    }
    while (walker1 != 0) {
        walker3 = new PolyNode(walker1->data, walker1->degree,0);
        walker3 = walker3->next;
    }
    while (walker2 != 0) {
        walker3 = new PolyNode(walker2->data, walker2->degree, 0);
        walker3 = walker3->next;
    }
    return Polynomial(ret);
} */

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    PolyNode* walker = p.head;
    while (walker != 0) {
        if (walker->data > 0 && walker != p.head) {
            os << "+";
        }
        os << walker->data;
        if (walker->degree != 0) {
            os << "*x^" << walker->degree;
        }
        walker = walker->next;
    }
    return os;
}