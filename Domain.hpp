#ifndef DOMAIN_HPP
#define DOMAIN_HPP
#include "Curvebase.hpp"
#include "Point.hpp"
class Domain{
	public:
		Domain(const Curvebase&, const Curvebase&, const Curvebase&, const Curvebase&);
		Domain(const Domain&); //Copy constructor
		Domain& operator =(Domain&);
        Point Domain::operator()(int i, int j) const;
		void generate_grid(int, int);
		// ...
	private:
		Curvebase *sides[4];
		Point *corners[4];
        double *x_ = nullptr, *y_ = nullptr;
        int n_ = 0, m_ = 0;
		bool check_consistency(); //Check if the grid is topologically equivalent to a square
		// ...
};
#include "Domain.cpp"
#endif