#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP
#include "ASI.hpp"
#include "Point.hpp"
class Curvebase{ //ABSTRACT CLASS, NEEDS TO BE INHERITED
	public:
        Curvebase(double, double);
		double x(double); //Function of s, the arc length parameter
		double y(double);
		virtual ~Curvebase(); // -> destructor always has to be virtual
		
		
	protected: //Exposed to derived classes but not to other classes
		double pmin, pmax;
		Point begin, end;
		bool rev; // orientation of the curve
		virtual double xp(double) = 0; // pure virtual function, has to be implemented but will not be implemented in base class
		virtual double yp(double) = 0; // check if a<p<b
		virtual double dxp(double) = 0;
		virtual double dyp(double) = 0;
		double integrate(double); // arc length integral, has to be defined in base class, can be overwritten i guess?
	
	private:
		double f(double); //Function to go in the integral of the standard definition of integrate
		double ASI(double (Curvebase::*)(double),double,double,double,double,double,double,double,double);
		double simp(double,double,double,double,double);
};

#include "Curvebase.cpp"
#endif