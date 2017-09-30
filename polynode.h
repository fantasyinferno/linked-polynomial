#ifndef POLYNODE_H
#define POLYNODE_H
// Self-explaining polynomial node
struct PolyNode {
    int data, degree;
    PolyNode* next;
    PolyNode(int, int, PolyNode*);
    PolyNode();
};


#endif