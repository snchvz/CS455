#include <iostream>

#include "dlist.h"
#include "correlation.h"
using namespace std;

int main()
{
    DDlist<float,float> ls;

    cout << "Given data: " << endl;
    ls.push_back(200,30.0);
    ls.push_back(800,118.7);
    ls.push_back(260,13);
    ls.push_back(450,40.8);
    ls.push_back(1500,144.6);
    ls.push_back(450,26.6);
    ls.push_back(1850,95.5);
    ls.push_back(900,77.60);
    ls.push_back(1650,140.6);
    ls.push_back(1400,140.8);
   
    ls.read();

    Correlation<float,float> clist(ls);

    cout << "correlation: " << clist.corr_function() << endl;

    cout << "correlation squared: " << clist.corr_sq() << endl;

    cout << endl;

    DDlist<float,float> ls2;

    cout << "Custom data: " << endl;

    ls2.push_back(334.1, 44);
    ls2.push_back(355.66, 39);
    ls2.push_back(115.9, 30);
    ls2.push_back(743.2, 58.3);
    ls2.push_back(192.3, 33.6);


    ls2.read();

    Correlation<float, float> clist2(ls2);
    
    cout << "correlation: " << clist2.corr_function() << endl;
    cout << "correlation squared: " << clist2.corr_sq() << endl;
}

