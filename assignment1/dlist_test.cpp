//andrew Sanchez
//uses user defined list.h to test insert, deleteNode, search, and read functions

#include <iostream>
#include "dlist.h"

using namespace std;

main()
{
   //create double linked list
   Dlist<float> ld;
   
   ld.insert(54.15);
   ld.insert(11.42);
   ld.insert(12.19);
   ld.insert(83.40);
   ld.insert(15.27);
   ld.insert(60.17);
   ld.insert(-63.81);
   ld.insert(54.15);
   ld.insert(-1.394);
   ld.insert(-22.60); 


   ld.read();

   cout << endl;

   ld.deleteNode(12.19);
   ld. deleteNode(27.33);

   cout << endl;

   ld.read();

}


