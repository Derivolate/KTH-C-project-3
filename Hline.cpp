#include "Hline.hpp"
//A horizontal curve running from p = a to p = b, to the right (dir = true) or to left (dir = false) starting at Point begin running for length len
Hline::Hline(double a, double b, bool dir, double x, double y, double len) 
    : Curvebase(a, b, dir), bx(x), by(y), length(len), ey(y), ex(x+len){
}

double Hline::xp(double p) {
    if (!(pmin<=p and p<=pmax)){}
        //throw error
    return bx+(p-pmin)*(ex-bx)/(pmax-pmin);
}

double Hline::yp(double p) {
    if (!(pmin<=p and p<=pmax)){}
        //throw error
    return by;
}

double Hline::dxp(double p) { 
    if (!(pmin<=p and p<=pmax)){}
        //throw error
    return (ex-bx)/(pmax-pmin);
}

double Hline::dyp(double p) {
    return 0;
}