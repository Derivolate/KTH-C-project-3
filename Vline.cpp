#include "Vline.hpp"
//A horizontal curve running from p = a to p = b, to the right (dir = true) or to left (dir = false) starting at Point begin running for length len
Vline::Vline(double a, double b, bool dir, double x, double y, double len) : pmin(a), pmax(b), bx(x), by(y), length(len), rev(dir), ex(x), ey(y+len){}

Vline::~Vline(){
//TODO what needs to happen here?
}
double Vline::xp(double p){
    if (~(pmin<=p and p<=pmax)){}
        //throw error
    return bx;
}
double Vline::yp(double p){
    if (~(pmin<=p and p<=pmax)){}
        //throw error
    return by+(p-pmin)*(ey-by)/(pmax-pmin);
}

double Vline::dxp(double p){
    return 0;
}

double Vline::dyp(double p){
    if (~(pmin<=p and p<=pmax)){}
        //throw error
    return (ey-by)/(pmax-pmin);
}