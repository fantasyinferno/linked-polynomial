# linked-polynomial
Polynomial program for CO2003

## Intro
This repository contains the code files for representing a polynomial using Linked List and a program to test the described functionalities.
## Compiling & Running
Just compile the files using g++:
```sh
g++ main.cpp polynomial.cpp polynode.cpp -o polynomial.exe
./polynomial
```
## Usage
The program has two main sections: entering polynomials and operating on them.
### Polynomials:
Example:
```sh
1\*x^2 - 2x^2 + 1
2x3 + 4x2 -6
5\*x^4 - 2\*x^2 - 1
```
The terms of the polynomial must be of the following forms:
```sh
axb
a\*xb
a\*x^b
ax^b
```
Notice that ```x1, x*2, x^3,...```  are not supported.
### Operators:
Example:
```sh
P1 + P2
P1 cal -7
P1 -     P3
```
P1 denotes the first entered polynomial. Notice that indexing starts at 1.
Multiplication is not supported yet.