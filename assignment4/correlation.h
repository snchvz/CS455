#ifndef CORRELATION_H
#define CORRELATION_H

//Andrew Sanchez
//Class Correlation. class takes in a singly linked list of
//data points and calculates the correlation. program also
//calculates significance with file tchart.txt


#include <iostream>
#include <fstream>
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
    bool dist_check(); //check if correlation is > .7 @
    T s_percentage();   //significance percent @
    T sig();    //sig value @
    void test();

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
    float table[10][9];

};

template<class T, class U>
Correlation<T,U>::Correlation(DDlist<T,U> & l)
{
    ls = l;
    size = ls.size();

    ifstream file("tchart.txt");

    int i = 0;
    int j = 0;
    for (i = 0; i < 10; i++){
        for (j = 0; j < 9; j++){
            file >> table[i][j];
        }
        j = 0;
    }

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
    T corr_value = corr_function();    //correlation value

    if (corr_value < 0)
        corr_value = corr_value * -1;

    if (corr_value < .7){
        cout << "correlation is less than .70" << endl;
        return -1;
    }

    T tval = 0;     //final t value for distribution
    T nsize = size;     // n value
    T denom = 0;    //denominator value

    nsize = nsize - 2;
    nsize = sqrt(nsize);
    tval = corr_value * nsize;  //numerator

    denom = 1 - corr_sq();
    denom = sqrt(denom);    //denominator

    tval = tval / denom;

    return tval;
}

template<class T, class U>
bool Correlation<T,U>::dist_check()
{
    if (tvalue() > .7)
        return true;
    return false;
}

template<class T, class U>
T Correlation<T,U>::sig()
{
    if (!dist_check()){
        cout << "no significance ";
        return -1;
    }
    int degree = size - 2;
    int i,j;
    float alpha, z, y, x;
    float tval = tvalue();

    if (degree < 11){
        i = degree;

        if (tval < table[i][1])
            return table[0][1];
        else if (tval > table[i][8])
            return table[0][8];

        for (j = 1; j < 9; j++){
            if (table[i][j] < tval and table[i][j+1] > tval){
                z = table[0][j+1] - table[0][j];
                y = table[i][j+1] - table[i][j];
                x = tval - table[i][j];
                alpha = x * z;
                alpha = alpha / y;
                alpha = alpha + table[0][j];
                return alpha;
            }
        }
    } else if (degree < 16){
        i = 11;

        if (tval < table[i][1])
            return table[0][1];
        else if (tval > table[i][8])
            return table[0][8];

        for (j = 1; j < 9; j++){
            if (table[i][j] < tval and table[i][j+1] > tval){
                z = table[0][j+1] - table[0][j];
                y = table[i][j+1] - table[i][j];
                x = tval - table[i][j];
                alpha = x * z;
                alpha = alpha / y;
                alpha = alpha + table[0][j];
                return alpha;
            }
        }

    } else if (degree < 21){
        i = 12;

        if (tval < table[i][1])
            return table[0][1];
        else if (tval > table[i][8])
            return table[0][8];

        for (j = 1; j < 9; j++){
            if (table[i][j] < tval and table[i][j+1] > tval){
                z = table[0][j+1] - table[0][j];
                y = table[i][j+1] - table[i][j];
                x = tval - table[i][j];
                alpha = x * z;
                alpha = alpha / y;
                alpha = alpha + table[0][j];
                return alpha;
            }
        }
    } else if (degree == 30){
        i = 13;

        if (tval < table[i][1])
            return table[0][1];
        else if (tval > table[i][8])
            return table[0][8];

        for (j = 1; j < 9; j++){
            if (table[i][j] < tval and table[i][j+1] > tval){
                z = table[0][j+1] - table[0][j];
                y = table[i][j+1] - table[i][j];
                x = tval - table[i][j];
                alpha = x * z;
                alpha = alpha / y;
                alpha = alpha + table[0][j];
                return alpha;
            }
        }
    } else {
        i = 14;

        if (tval < table[i][1])
            return table[0][1];
        else if (tval > table[i][8])
            return table[0][8];

        for (j = 1; j < 9; j++){
            if (table[i][j] < tval and table[i][j+1] > tval){
                z = table[0][j+1] - table[0][j];
                y = table[i][j+1] - table[i][j];
                x = tval - table[i][j];
                alpha = x * z;
                alpha = alpha / y;
                alpha = alpha + table[0][j];
                return alpha;
            }
        }
    }

    return 2;

}
template<class T, class U>
T Correlation<T,U>::s_percentage()
{
    if (!dist_check())
        return -1;
    T percentage = 1 - sig();
    percentage = percentage * 2;
    return percentage;
}

template<class T, class U>
void Correlation<T,U>::test()
{
    cout << table[7][3] << endl;
}

#endif
