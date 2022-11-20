#ifndef DOMAIN_HPP
#define DOMAIN_HPP
#include "Curvebase.hpp"
#include "Point.hpp"
class Domain{
	public:
		Domain( Curvebase&, Curvebase&, Curvebase&, Curvebase&);
		Domain(const Domain&); //Copy constructor
		Domain& operator =(Domain&); //Assignment operator
        Point operator()(int i, int j) const;
		~Domain();
		void generate_grid(int, int, int); // pass mxn grid and interpolation option. 1-linear, 2-whateverthatoptionalthingis
		void print_grid();
	private:
		Curvebase *sides[4];
		Point *corners[4];
        double *x_ = nullptr, *y_ = nullptr;
        int n_ = 0, m_ = 0;
		bool check_consistency(); //Check if the grid is topologically equivalent to a square
		double phi1(double); //transition function for grid generation phix(0) = 1, phix(1) = 0
		double phi2(double); //transition function for grid generation phiy(1) = 1, phix(0) = 0
};
#include "Domain.cpp"
#endif