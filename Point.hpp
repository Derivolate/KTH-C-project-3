#ifndef POINT_HPP
#define POINT_HPP
class Point {
    private:
        double x;
        double y;
    public:
        Point(double xx, double yy);
        Point(const Point&);
        Point& operator=(const Point&);
        const Point operator+(const Point&) const;
        const Point operator-() const;
        double X();
        double Y();
        void zero(); 
        
};
#include "Point.cpp"
#endif