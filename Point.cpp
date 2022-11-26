#include "Point.hpp"
#include <math.h>

Point::Point(double xx, double yy) : x(xx), y(yy) { }
Point::Point(Point const & Q): x(Q.x), y(Q.y) { }

Point & Point::operator=(Point const & P) {
    if (this != &P) { // nicht unbedingt notwendig -- wenn gleich überschreibt man halt -- billiger als der branch -- git aber Fälle, wo man aufpassen muss
        x = P.x; // equivalent: (*this).x = P.x;
        y = P.y;
    }
    return *this; // dereferencing!
}

Point Point::operator+(const Point& Q) const{
    return Point(x+Q.x,y+Q.y);
}
Point Point::operator-() const {
    return Point(-x,-y);
}

double Point::X() {
    return x;
}
double Point::Y() {
    return y;
}
void Point::zero() {
    x = y = 0.0;
}