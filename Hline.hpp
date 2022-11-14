#ifndef HLINE_HPP
#define HLINE_HPP
#include "Curvebase.hpp"
class Hline : Curvebase{
    public :
        Hline(double, double, bool, Point, double);
        ~Hline();
    protected :
        double pmin, pmax;
		Point begin, end;
		bool rev; // orientation of the curve
        double xp(double);
        double yp(double);
        double dxp(double);
        double dyp(double);
};
#include "Hline.cpp"
#endif