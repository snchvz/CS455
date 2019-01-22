#include <iostream>

#include "dlist.h"
#include "correlation.h"
using namespace std;

int main()
{
    DDlist<float,float> ls;

    cout << "Given data: " << endl;
    ls.push_back(400,26.6);
    ls.push_back(450,30.2);
    ls.push_back(1700,36.6);
    ls.push_back(1600,48.8);
    ls.push_back(1958,58.5);
    ls.push_back(2030,55.6);
    ls.push_back(125,32.3);

    ls.read();

    Correlation<float,float> clist(ls);

    cout << "correlation: " << clist.corr_function() << endl;

    cout << "correlation squared: " << clist.corr_sq() << endl;

    cout << "t value : " << clist.tvalue() << endl;

    cout << "p = " << clist.sig() << endl;

    cout << "percentage: " << clist.s_percentage()<< endl;

    cout << endl;
    cout << endl;

    DDlist<float,float> ls2;

    cout << "Custom data: " << endl;

    ls2.push_back(234.1, 34);
    ls2.push_back(355.66, 59);
    ls2.push_back(115.9, 27);
    ls2.push_back(243.2, 48.3);
    ls2.push_back(192.3, 33.6);
    ls2.push_back(132.5, 35);
    ls2.push_back(634, 55);


    ls2.read();

    Correlation<float, float> clist2(ls2);

    cout << "correlation: " << clist2.corr_function() << endl;
    cout << "correlation squared: " << clist2.corr_sq() << endl;
    cout << "t value: " << clist2.tvalue() << endl;
    cout << "p = " << clist2.sig() << endl;
    cout << "percentage : " << clist2.s_percentage() << endl;

    clist2.test();

}

