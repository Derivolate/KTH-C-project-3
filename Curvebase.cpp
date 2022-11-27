#include "Curvebase.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <functional>

using namespace std::placeholders;

Curvebase::Curvebase(double a, double b, bool dir) : pmin(a), pmax(b), rev(dir) {
    //TODO whattefuck should go in the nonderived curvebase constructor?
}

Curvebase::~Curvebase(){
    //TODO standard destructor
}

double Curvebase::integrate(double p) {
    double tol = 1e-10; //TODO come up with better tollerance
    double a = pmin, c = p;
    double b = a+c/2;
    double fa = integrand(a), fb = integrand(b), fc = integrand(c);
    double I = simp(fa,fb,fc,a,c);
    return ASI_routine(a,b,c,tol,fa,fb,fc,I);
}

double Curvebase::integrand(double q){
    return sqrt(pow(dxp(q),2)+pow(dyp(q),2));
}

double Curvebase::ASI_routine(double a, double b, double  c, double tol, double fa, double fb, double fc, double I1){
    //Calculate the midpoints
    double ab = (a+b)/2, bc = (b+c)/2;
    //Evaluate the midpoints
    double fab = integrand(ab), fbc = integrand(bc);
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
        return ASI_routine(a,ab,b,tol/2,fa,fab,fb,Iab) + ASI_routine(b,bc,c,tol/2,fb,fbc,fc,Ibc);
    }
}

//Inline function for simpsons rule using pre-calculated function evaluations
inline double Curvebase::simp(double fa,double fb,double fc,double a,double c)
{
    return (fa+4*fb+fc)*(c-a)/6;
}

double Curvebase::newton(double s, double guess, double tol = 1e-12){
    double p(guess);
    double dp(1.0);
    int i(0);
    int timeout(1e5);
    double arclenth(integrate(pmax));

    while(fabs(dp) > tol){
        double dnmntr = sqrt(dxp(p)*dxp(p)+dyp(p)*dxp(p));
        // std::cout << "p_" << i << " = " << p << " -- Integrant = " << std::sqrt(dxp(p)*dxp(p)+dyp(p)*dxp(p)) << std::endl;
        if (dnmntr == 0){//Handle if derivative is always zero -- horizonal/vertical boarder
            // std::cout << "Newton - Curve is a constant therefore no solving is needed" << std::endl;
            return s;
        } 
        dp = (integrate(p) - s*arclenth)/dnmntr;
        p -= dp;
        ++i;
    }
    // std::cout << "Newton - Finished in " << i << " iterations" << std::endl;
    return p;
}

double Curvebase::x(double s){
    double guess((pmin+pmax)/2);
    double p0;
    if (!rev) p0 = newton(1.0-s, guess);
    else {
        // std::cout << "Calling x newton with s = " << s << std::endl;
        p0 = newton(s,guess);
    }
    return xp(p0);
}

double Curvebase::y(double s){
    double guess((pmin+pmax)/2);
    double p0;
    if (!rev) p0 = newton(1.0-s, guess);
    else {
        // std::cout << "Calling y newton with s = " << s << std::endl;
        p0 = newton(s,guess);
    }
    return yp(p0);
}

