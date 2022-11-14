#include <math.h>
#include "Point.hpp"

Point::Point(double xx = 0.0, double yy = 0.0) :x(xx), y(yy) { }
Point::Point(const Point& Q): x(Q.x), y(Q.y) { }

Point& Point::operator=(const Point& P) {
    if (this != &P) {
        x = P.x; // equivalent: (*this).x = P.x;
        y = P.y;
    }
    return *this; // dereferencing!
}

const Point Point::operator+(const Point& Q) const{
    return Point(x+Q.x,y+Q.y);
}
const Point Point::operator-() const {
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