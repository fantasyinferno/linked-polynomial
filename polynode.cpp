
#include "polynode.h"

PolyNode::PolyNode(int data, int degree, PolyNode* next) {
    this->data = data;
    this->degree = degree;
    this->next = next;
}
PolyNode::PolyNode() {
    this->data = 0;
    this->degree = 0;
}