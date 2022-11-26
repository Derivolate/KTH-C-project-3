#ifndef POINT_HPP
#define POINT_HPP

class Point {
    public:
        Point(double xx, double yy);
        Point(const Point&);

        Point& operator=(const Point&);
        Point operator+(const Point&) const;
        Point operator-() const;

        double X();
        double Y();
        void zero(); 

    private:
        double x;
        double y;        
};

#endif