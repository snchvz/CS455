#ifndef CORRELATION_H
#define CORRELATION_H

//Andrew Sanchez
//Class Correlation. class takes in a singly linked list of double data points and
//calculates the correlation.


#include <iostream>
#include <cmath>
#include "dlist.h"

using namespace std;

template<class T, class U> class Correlation;

template<class T, class U>
class Correlation {
public:
    typedef DDlist_iterator<T,U> dditerator;

    Correlation(DDlist<T,U> & l);   //@
    ~Correlation(){}                 //@

    T corr_function() const;   //@
    T corr_sq() const;    //@
    unsigned int size_() const; //@
    T tvalue() const;   //t value for distribution @


protected:
    T xsum() const;    // sum of x@
    U ysum() const;    // sum of y@

    T xysum() const; // sum of x times y@

    T sumxsq() const;   //the sum of x, then squared @
    U sumysq() const;   //the sum of y, then squared @

    T xsqsum() const;   //the sum of squared x times size @
    U ysqsum() const;   //the sum of squared y times size @

private:
    DDlist<T,U> ls;
    unsigned int size;
};

template<class T, class U>
Correlation<T,U>::Correlation(DDlist<T,U> & l)
{
    ls = l;
    size = ls.size();
}

template<class T, class U>
unsigned int Correlation<T,U>::size_()const
{
    return size;
}

template<class T, class U>
T Correlation<T,U>::xsum()const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    T sumx = 0;

    while (it != ls.end()){
        sumx += *it;
        ++it;
    }
    sumx += *it;
    return sumx;
}

template<class T, class U>
U Correlation<T,U>::ysum()const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    U sumy = 0;

    while (it != ls.end()){
        sumy += ~it;
        ++it;
    }
    sumy += ~it;
    return sumy;
}

template<class T, class U>
T Correlation<T,U>::xysum()const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    T sumxy = 0;

    while (it != ls.end()){
        sumxy = sumxy + (*it * ~it);
        ++it;
    }
    sumxy = sumxy + (*it * ~it);
    sumxy = sumxy * size;
    return sumxy;
}

template<class T, class U>
T Correlation<T,U>::sumxsq()const
{
    T sumxsquared = xsum() * xsum();
    return sumxsquared;
}

template<class T, class U>
U Correlation<T,U>::sumysq()const
{
    U sumysquared = ysum() * ysum();
    return sumysquared;
}

template<class T, class U>
T Correlation<T,U>::xsqsum()const
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
U Correlation<T,U>::ysqsum()const
{
    typename DDlist<T,U>::dditerator it = ls.begin();
    U sigmaysq = 0;

    while (it != ls.end()){
        sigmaysq = sigmaysq + (~it * ~it);
        ++it;
    }
    sigmaysq = sigmaysq + (~it * ~it);
    sigmaysq = sigmaysq * size;
    return sigmaysq;
}

template<class T, class U>
T Correlation<T,U>::corr_function()const
{
    T corr_output = 0;  //final output
    T corr_num = 0;     // numerator
    T corr_den1 = 0;     //denominator first half
    T corr_den2 = 0;    //denominator second half
    T corr_denf = 0;    //final denominator

    corr_num = xsum() * ysum();
    corr_num = xysum() - corr_num;

    corr_den1 = xsqsum() - sumxsq();

    corr_den2 = ysqsum() - sumysq();

    corr_denf = corr_den1 * corr_den2;
    corr_denf = sqrt(corr_denf);

    corr_output = corr_num / corr_denf;
    return corr_output;
}

template<class T, class U>
T Correlation<T,U>::corr_sq()const
{
    T corr_squared = corr_function() * corr_function();
    return corr_squared;
}

template<class T, class U>
T Correlation<T,U>::tvalue()const
{
    T tval = 0;     //final t value for distribution
    T nsize = size;     // n value
    T corr_value = corr_function();    //correlation value
    T denom = 0;    //denominator value

    if (corr_value < 0)
        corr_value = corr_value * -1;

    nsize = nsize - 2;
    nsize = sqrt(nsize);
    tval = corr_value * nsize;  //numerator

    denom = 1 - corr_sq();
    denom = sqrt(denom);    //denominator

    tval = tval / denom;

    return tval;
}














#endif
