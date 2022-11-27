#include "Curvebase.hpp"
#include <cmath>
#include <iostream>

Curvebase::Curvebase(double a, double b, bool dir) : pmin(a), pmax(b), rev(dir) {}

Curvebase::~Curvebase(){}

double Curvebase::integrate(double p) {
    double tol = 1e-10;
    // Calculate values to kickstart the algorithm
    double a = pmin, c = p;
    double b = a+c/2;
    double fa = integrand(a), fb = integrand(b), fc = integrand(c);
    double I = simp(fa,fb,fc,a,c);
    // Run the algorithm
    return ASI_routine(a,b,c,tol,fa,fb,fc,I);
}



double Curvebase::ASI_routine(double a, double b, double  c, double tol, double fa, double fb, double fc, double I1){
    //Calculate the midpoints
    double ab((a+b)/2), bc((b+c)/2);
    //Evaluate the midpoints
    double fab(integrand(ab)), fbc(integrand(bc));
    //Compute the midpoint integrals
    double Iab(simp(fa,fab,fb,a,b)), Ibc(simp(fb, fbc, fc, b,c));
    double I2 = Iab + Ibc;
    
    //Compare the new result, and return it if it is accurate enough
    double err(fabs(I1-I2));
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

//Inline function of the integrand
inline double Curvebase::integrand(double q){
    return sqrt(pow(dxp(q),2)+pow(dyp(q),2));
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
    double denom;
    while(fabs(dp) > tol){
        denom = sqrt(dxp(p)*dxp(p)+dyp(p)*dxp(p));
        
        //Handle if derivative is always zero -- horizonal/vertical boarder
        if (denom == 0) return s;

        dp = (integrate(p) - s*arclenth)/denom;
        p -= dp;
        if (p<pmin){
            p = pmin;
        }else if(p>pmax){
            p = pmax;
        }

        ++i;
    }
    return p;
}

double Curvebase::x(double s){
    double guess((pmin+pmax)/2);
    double p0;
    if (!rev) p0 = newton(1.0-s, guess);
    else p0 = newton(s,guess);
    return xp(p0);
}

double Curvebase::y(double s){
    double guess((pmin+pmax)/2);
    double p0;
    if (!rev) p0 = newton(1.0-s, guess);
    else p0 = newton(s,guess);
    return yp(p0);
}

// Check if the value of p is within bounds, and throw an error if that's not the case
void Curvebase::p_check(double p){
    if (!(pmin<=p and p<=pmax)){
        std::cerr<<"Value of p outside of allowed range"<<std::endl;
        exit(1);
    }
}