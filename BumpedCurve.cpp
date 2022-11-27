#include "BumpedCurve.hpp"
#include <cmath>
//a,b,rev,x0,y0,x1,x2,s1,s2,h
BumpedCurve::BumpedCurve(double a, double b, bool rev, double x0, double y0, double len, double x1_, double x2_, double s1_, double s2_, double h_)
    :Curvebase(a, b, rev),bx(x0),by(y0),ex(x0+len),ey(y0),x1(x1_),x2(x2_),s1(s1_),s2(s2_),h(h_),xc(((s1_/s2_)*x1_+x2_)/(1+(s1_/s2_))){}

double  BumpedCurve::xp(double p)
{
    if (!(pmin<=p and p<=pmax)){}
        //throw error
    return bx+(p-pmin)*(ex-bx)/(pmax-pmin);
}

double  BumpedCurve::yp(double p)
{
    double yval;
    double xval = xp(p);
    if (xval<xc)
    {
        yval = -s1*(xval-x1);
    }
    else 
    {
        yval =  s2*(xval-x2);
    }
    return h/(1+exp(yval));
}

double  BumpedCurve::dxp(double p)
{
    if (!(pmin<=p and p<=pmax)){}
        //throw error
    return (ex-bx)/(pmax-pmin);
}

double  BumpedCurve::dyp(double p)
{
    double sval, expval;
    double xval = xp(p);
    if (xval<xc)
    {
        expval = exp(-s1*(xval-x1));
        sval = -s1;
    }
    else
    {
        expval = exp(s2*(xval-x2));
        sval = s2;
    }
    return -(h*expval*sval)/pow(1+expval,2);
}