//andrew Sanchez
//uses user defined list.h to test insert, deleteNode, search, and read functions

#include <iostream>
#include "list.h"

using namespace std;

main()
{
    //create list
    List<float> ls;

    ls.search(5);

    //insert values
    ls.insert(54.15);
    ls.insert(11.42);
    ls.insert(12.19);
    ls.insert(83.4);
    ls.insert(15.27);
    ls.insert(60.17);
    ls.insert(-63.81);
    ls.insert(54.15);
    ls.insert(-1.394);
    ls.insert(-22.6);

    cout << endl;

    ls.read();
   
    cout << endl;

    ls.search(-63.81);
    ls.search(10);
    ls.search(0);
    ls.search(100);
    ls.search(54.15);
    ls.search(83.40);
    
    cout << endl;

    ls.deleteNode(12.19);
    ls.deleteNode(27.33);

    cout << endl;

    ls.read();
}

