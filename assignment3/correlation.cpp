#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    List<float> ls;
    List<float> ls2;

    ls.insert(5);
    ls.insert(12.1);
    ls.insert(55);
    ls.insert(2.5);
    ls.insert(7.77);

    ls2.insert(6);
    ls2.insert(19.01);
    ls2.insert(3.55);
    ls2.insert(14);
    ls2.insert(101);

    ls.read();
    cout << endl;
    ls2.read();

    cout << endl;

    List_iterator::iterator it = ls
}
