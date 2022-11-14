#include "Hline.hpp"
//A horizontal curve running from p = a to p = b, to the right (dir = true) or to left (dir = false) starting at Point begin running for length len
Hline::Hline(double a, double b, bool dir, Point begin, double len) : pmin(a), pmax(b), begin(begin), rev(dir){
    end = Point(begin.X(), begin.Y()+len);
}
Hline::~Hline(){

}
double Hline::xp(double p){
    if (~(pmin<=p and p<=pmax)){}
        //throw error
    return begin.X()+(p-pmin)*(end.X()-begin.X())/(pmax-pmin);
}
double Hline::yp(double p){
    if (~(pmin<=p and p<=pmax)){}
        //throw error
    return begin.Y();
}
double Hline::dxp(double p){
    if (~(pmin<=p and p<=pmax)){}
        //throw error
    return (end.X()-begin.X())/(pmax-pmin);
}
double Hline::dyp(double p){
    return 0;
}