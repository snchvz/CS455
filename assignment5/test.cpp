#include <iostream>

#include "dlist.h"
#include "linear.h"
using namespace std;

//test for linear regression program

int main()
{
    DDlist<float,float> ls;

    cout << "Test case 1: " << endl;

    ls.push_back(130, 186);
    ls.push_back(650, 699);
    ls.push_back(99, 132);
    ls.push_back(150, 272);
    ls.push_back(128, 291);
    ls.push_back(302, 331);
    ls.push_back(95, 199);
    ls.push_back(945, 1890);

    Linear_R<float, float> line(ls);

    cout << line.xavg() << endl;
  cout << line.yavg() << endl;

  cout << line.beta1() << endl;
 cout << line.beta0() << endl;
cout << endl;
DDlist<float,float> ls2;

    cout << "Test case 2: " << endl;

    ls2.push_back(163, 186);
    ls2.push_back(765, 699);
    ls2.push_back(141, 132);
    ls2.push_back(166, 272);
    ls2.push_back(137, 291);
    ls2.push_back(355, 331);
    ls2.push_back(136, 199);
    ls2.push_back(1206, 1890);

    Linear_R<float, float> line2(ls2);

    cout << line2.xavg() << endl;
  cout << line2.yavg() << endl;

  cout << line2.beta1() << endl;
cout << line2.beta0() << endl;
}
