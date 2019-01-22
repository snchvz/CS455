#ifndef CORRELATION_H
#define CORRELATION_H

//Andrew Sanchez
//Class Correlation. class takes in a singly linked list of
//data points and calculates the correlation. program also
//calculates significance with file tchart.txt and linear regression


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

    T xavg() const; //avg of x @
    U yavg() const; // avg of y @
    T beta1();  //@
    T beta0();  //@
    T std_dev();    //@
    T UPI(int perc, float xk);    //@
    T LPI(int perc, float xk);    //@


    T corr_function() const;   //@
    T corr_sq() const;    //@
    unsigned int size_() const; //@
    T tvalue() const;   //t value for distribution @
    bool dist_check(); //check if correlation is > .7 @
    T s_percentage();   //significance percent @
    T sig();    //sig value @

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
            if (table[i][j] == tval){
                return table[0][j];
            }
            else if (table[i][j] < tval and table[i][j+1] > tval){
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
            if (table[i][j] == tval){
                return table[0][j];
            }
            else if (table[i][j] < tval and table[i][j+1] > tval){
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
            if (table[i][j] == tval){
                return table[0][j];
            }
            else if (table[i][j] < tval and table[i][j+1] > tval){
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
            if (table[i][j] == tval){
                return table[0][j];
            }
            else if (table[i][j] < tval and table[i][j+1] > tval){
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
            if (table[i][j] == tval){
                return table[0][j];
            }
            else if (table[i][j] < tval and table[i][j+1] > tval){
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
T Correlation<T,U>::xavg() const
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
U Correlation<T,U>::yavg() const
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
T Correlation<T,U>::beta1()
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
T Correlation<T,U>::beta0()
{
    T finalret = 0;

    finalret = yavg() - (beta1() * xavg());

    return finalret;
}

template<class T, class U>
T Correlation<T,U>::std_dev()
{
    T size_ = size;
    T second = 0;
    T temp = 0;
    T finalret = 0;

    T first = 1 / (size_ - 2);

    typename DDlist<T,U>::dditerator it = ls.begin();

    while (it != ls.end()){
        temp = ~it - beta0() - (beta1() * *it);
        temp *= temp;
        second = second + temp;
        ++it;
    }
    temp = ~it - beta0() - (beta1() * *it);
    temp *= temp;
    second = second + temp;

    finalret = first * second;

    finalret = sqrt(finalret);
    return finalret;

}

template<class T, class U>
T Correlation<T,U>::UPI(int perc, float xk)
{
    T size_ = size;
    T yk = 0;
    T upi = 0;
    T range = 0;
    T temp = 0;
    T first = 1 + (1/size_);

    T frac = 0;
    T num = 0;
    T den = 0;
    int index = 0;
    int degree = size - 2;

    if (perc == 70){
        index = 3;
    } else if (perc == 90){
        index = 5;
    }
    else return 0;

    T tvalue = table[degree][index];
    range = tvalue * std_dev();

    num = xk - xavg();
    num *= num;

    typename DDlist<T,U>::dditerator it = ls.begin();

    while (it != ls.end()){
        temp = *it - xavg();
        temp *= temp;
        den = temp + den;
        ++it;
    }
    temp = *it - xavg();
    temp *= temp;
    den = temp + den;
    frac = num / den;

    first = first + frac;
    first = sqrt(first);

    range = range * first;

    yk = beta0() + beta1() * xk;
    upi = yk + range;

    return upi;

}

template<class T, class U>
T Correlation<T,U>::LPI(int perc, float xk)
{
    T size_ = size;
    T yk = 0;
    T lpi = 0;
    T range = 0;
    T temp = 0;
    T first = 1 + (1/size_);

    T frac = 0;
    T num = 0;
    T den = 0;
    int index = 0;
    int degree = size - 2;

    if (perc == 70){
        index = 3;
    } else if (perc == 90){
        index = 5;
    }
    else return 0;

    T tvalue = table[degree][index];
    range = tvalue * std_dev();

    num = xk - xavg();
    num *= num;

    typename DDlist<T,U>::dditerator it = ls.begin();

    while (it != ls.end()){
        temp = *it - xavg();
        temp *= temp;
        den = temp + den;
        ++it;
    }
    temp = *it - xavg();
    temp *= temp;
    den = temp + den;
    frac = num / den;

    first = first + frac;
    first = sqrt(first);

    range = range * first;

    yk = beta0() + beta1() * xk;
    lpi = yk - range;

    return lpi;
}



#endif
