#include <iostream>
#include "bst.h"

using namespace std;

struct myInt{
    int x;

    myInt(int y) : x(y){};
};

int main()
{
    cout << "Hello world" << endl;
    cout << "\n\n\n\n" << endl;

    myInt a(15);
    myInt b(7);
    myInt c(8);
    myInt d(20);

    bst<myInt, int, &myInt::x> newTree;

    newTree.add(a);
    newTree.add(b);
    newTree.add(c);



    newTree.print();
}