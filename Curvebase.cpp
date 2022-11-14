#include "Curvebase.hpp"
#include <cmath>
Curvebase::Curvebase(double a = 0.0, double b = 1.0) : pmin(a), pmax(b){
    //TODO whattefuck should go in the nonderived curvebase constructor?
}

Curvebase::~Curvebase(){
    //TODO standard destructor
}

double Curvebase::integrate(double p){
    //TODO integrate with ASI from a to p
    double a(pmin), b(pmin+p/2), c(p);
    double fa(f(a)), fb(f(b)), fc(f(c));
    double I(simp(fa,fb,fc,a,c));
    double tol = 1e-10; //TODO come up with better tollerance
    return ASI(&f,a,b,c,tol,fa,fb,fc,I); //TODO why does this not work?
}
double Curvebase::f(double q){
    return std::sqrt(std::pow(dxp(q),2)+std::pow(dyp(q),2));
}