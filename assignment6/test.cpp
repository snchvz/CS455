#include <iostream>

#include "dlist.h"
#include "correlationfin.h"
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
    ls.push_back(368, 788);
    ls.push_back(961, 1601);

    Correlation<float, float> corr(ls);

    cout << "beta0: " << corr.beta0() << endl;
    cout << "beta1: " << corr.beta1() << endl;


    cout << "UPI 70 percent: " << corr.UPI(70, 386) << endl;
    cout << "LPI 70 percent: " << corr.LPI(70, 386) << endl;

    cout << "UPI 90 percent: " << corr.UPI(90, 386)<< endl;
    cout << "LPI 90 percent: " << corr.LPI(90, 386) << endl;

}
