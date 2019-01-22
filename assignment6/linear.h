#ifndef LINEAR_H
#define LINEAR_H

//Andrew Sanchez
//Class Linear_R,


#include <iostream>
#include <cmath>
#include "dlist.h"

using namespace std;

template<class T, class U> class Linear_R;

template<class T, class U>
class Linear_R {

public:

    Linear_R(DDlist<T,U> & l);  //@
    ~Linear_R(){}   //@

    T xavg() const; //avg of x @
    U yavg() const; // avg of y @
    T xsqsum() const;   //sum of squared x @
    T beta1();  //@
    T beta0();  //@

private:
    DDlist<T,U> ls;
    unsigned int size;
};

template<class T, class U>
Linear_R<T,U>::Linear_R(DDlist<T,U> & l)
{
    ls = l;
    size = ls.size();
}

template<class T, class U>
T Linear_R<T,U>::xavg() const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    T sumx = 0;
    T xmean = 0;

    while (it != ls.end()){
        sumx += *it;
        ++it;
    }
    sumx += *it;
    xmean = sumx / size;
    return xmean;
}

template<class T, class U>
U Linear_R<T,U>::yavg() const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    U sumy = 0;
    U ymean = 0;

    while (it != ls.end()){
        sumy += ~it;
        ++it;
    }
    sumy += ~it;
    ymean = sumy / size;
    return ymean;
}

template<class T, class U>
T Linear_R<T,U>::xsqsum()const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    T sigmaxsq = 0;

    while (it != ls.end()){
        sigmaxsq = sigmaxsq + (*it * *it);
        ++it;
    }
    sigmaxsq = sigmaxsq + (*it * *it);
    sigmaxsq = sigmaxsq * size;
    return sigmaxsq;

}

template<class T, class U>
T Linear_R<T,U>::beta1()
{
    T num = 0;
    T numtemp1 = 0;
    T numtemp2 = size * xavg() * yavg();

    T denom = 0;
    T denomtemp1 = 0;
    T denomtemp2 = (size * xavg() * xavg());

    T finalret = 0;

    typename DDlist<T,U>::dditerator it = ls.begin();

     while (it != ls.end()){
        numtemp1 += (*it * ~it);
        ++it;
     }
     numtemp1 += (*it * ~it);
     num = numtemp1 - numtemp2;


    it = ls.begin();

    while (it != ls.end()){
        denomtemp1 += (*it * *it);
        ++it;
    }

    denomtemp1 += (*it * *it);
    denom = denomtemp1 - denomtemp2;

    finalret = num / denom;

    return finalret;
}

template<class T, class U>
T Linear_R<T,U>::beta0()
{
    T finalret = 0;

    finalret = yavg() - (beta1() * xavg());

    return finalret;
}


#endif
