#include "Curvebase.hpp"
#include <cmath>
#include <functional>
#include <iostream>
using namespace std;
Curvebase::Curvebase(double a = 0.0, double b = 1.0) : pmin(a), pmax(b){
    //TODO whattefuck should go in the nonderived curvebase constructor?
}

Curvebase::~Curvebase(){
    //TODO standard destructor
}

double Curvebase::integrate(double p){
    double tol = 1e-10; //TODO come up with better tollerance
    
    double a = pmin, c = p;
    double b = a+c/2;
    double fa = integrand(a), fb = integrand(b), fc = integrand(c);
    double I = simp(fa,fb,fc,a,c);
    return ASI_routine(integrand,a,b,c,tol,fa,fb,fc,I);
}
double Curvebase::integrand(double q){
    return sqrt(pow(dxp(q),2)+pow(dyp(q),2));
}

double Curvebase::ASI_routine(ASI_fkt f, double a, double b, double  c, double tol, double fa, double fb, double fc, double I1){
    //Calculate the midpoints
    double ab = (a+b)/2, bc = (b+c)/2;
    //Evaluate the midpoints
    double fab = f(ab), fbc = f(bc);
    //Compute the midpoint integrals
    double Iab = simp(fa,fab,fb,a,b), Ibc = simp(fb, fbc, fc, b,c);
    double I2 = Iab + Ibc;
    
    //Compare the new result, and return it if it is accurate enough
    double err = std::abs(I1-I2); //std::abs from cmath
    if( err < 15*tol)
    { 
        return I2;
    }
    else
    {
        //Recursive function call if the result is not accurate enough
        return ASI_routine(f,a,ab,b,tol/2,fa,fab,fb,Iab) + ASI_routine(f,b,bc,c,tol/2,fb,fbc,fc,Ibc);
    }
}

//Inline function for simpsons rule using pre-calculated function evaluations
inline double Curvebase::simp(double fa,double fb,double fc,double a,double c)
{
    return (fa+4*fb+fc)*(c-a)/6;
}

double Curvebase::newton(ASI_fkt f, ASI_fkt df, double guess, double tol = 1e-12){
    double x0(guess);
    double dx(guess);
    int i(0);
    int timeout(1e5);
    while(fabs(dx) > tol){
        if  (i >= timeout){
            cout << "Runtime Error: Newton Method might not converge" << endl;
            return 0;
        }
        dx = f(x0)/df(x0);
        x0 -= dx;
        ++i;
    }
    return x0;
}