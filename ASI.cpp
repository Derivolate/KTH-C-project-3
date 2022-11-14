#include <iostream>
#include <cmath>
#include "ASI.hpp"
using namespace std;

double ASI(double (*f)(double), double a, double b, double  c, double tol, double fa, double fb, double fc, double I1)
{
    //Calculate the midpoints
    double ab = (a+b)/2, bc = (b+c)/2;
    //Evaluate the midpoints
    double fab = f(ab), fbc = f(bc);
    //Compute the midpoint integrals
    double Iab = simp(fa,fab,fb,a,b), Ibc = simp(fb, fbc, fc, b,c);
    double I2 = Iab + Ibc;
    
    //Compare the new result, and return it if it is accurate enough
    double err = abs(I1-I2); //std::abs from cmath
    if( err < 15*tol)
    { 
        return I2;
    }
    else
    {
        //Recursive function call if the result is not accurate enough
        return ASI(f,a,ab,b,tol/2,fa,fab,fb,Iab) + ASI(f,b,bc,c,tol/2,fb,fbc,fc,Ibc);
    }
}

//Inline function for simpsons rule using pre-calculated function evaluations
inline double simp(double fa,double fb,double fc,double a,double c)
{
    return (fa+4*fb+fc)*(c-a)/6;
}