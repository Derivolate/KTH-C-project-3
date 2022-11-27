#include <cmath>
#include <iostream>
#include <cstdio>
#include "Domain.hpp"
#include "Curvebase.hpp"
#include <fstream>

Domain::Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4) {
	sides[0] = &s1;
	sides[1] = &s2;
	sides[2] = &s3;
	sides[3] = &s4;
	//TODO consistency check
	// if (~check_consistency()) 
	// 	std::cout << "Grid is inconsistent" << std::endl;
		// sides[0] = sides[1] = sides[2] = sides[3] = nullptr; //If thegrid is not consistent, unassign them, why not throw error?
	m_ = n_ = 0;
	x_ = y_ = nullptr;
}


Domain::~Domain() {
	if (m_ > 0 || n_ >0) {
		delete [] x_;
		delete [] y_;
	}
}

Point Domain::operator()(int i, int j) const {
	if (i < 0 || i >= m_ || j < 0 || j >= n_) {
		exit(-1);
	}
	int ind = i+j*m_;
	return Point(x_[ind],y_[ind]);
}

double Domain::phi1(double q){return 1-q;}
double Domain::phi2(double q){return q;}
	
void Domain::generate_grid(int m, int n, int c = 1){
	if(m<1 || n<1) 
		// throw error
	if(m_>0 || n_>0) { //if previous grid exists, reset grid points
		delete [] x_;
		delete [] y_;
	}
	x_ = new double[m*n]; 
	y_ = new double[m*n];
	double xi, nu;
	double xtemp,ytemp;
	m_ = m, n_= n;
	double h1(1.0/(n-1)), h2(1.0/(m-1)); // (FORCE FLOATING POINT DIVISION)
	for(int i(0); i<n; ++i){ //Vertical index, indicates the row
		for(int j(0); j<m; ++j){ //Horizontal index, indicates the column
			double xi(i*h1), nu(j*h2);
			// if (c == 1) {double xi(i*h1),nu(j*h2); // equidistant s
			// else if (c==2) double xi(1+(tanh(3)*((i*h1)-1))/tanh(3)),nu(1+(tanh(3)*((j*h2)-1))/tanh(3)); // stretched s position Task 5

			xtemp = phi1(xi)*sides[3]->x(nu)+phi2(xi)*sides[1]->x(nu)
						+ phi1(nu)*sides[0]->x(xi) + phi2(nu)*sides[2]->x(xi)
						- phi1(xi)*phi1(nu)*sides[0]->x(0)
						- phi1(xi)*phi2(nu)*sides[2]->x(0)
						- phi2(xi)*phi1(nu)*sides[0]->x(1)
						- phi2(xi)*phi2(nu)*sides[2]->x(1);
			ytemp = phi1(xi)*sides[3]->y(nu)+phi2(xi)*sides[1]->y(nu)
						+ phi1(nu)*sides[0]->y(xi) + phi2(nu)*sides[2]->y(xi)
						- phi1(xi)*phi1(nu)*sides[0]->y(0)
						- phi1(xi)*phi2(nu)*sides[2]->y(0)
						- phi2(xi)*phi1(nu)*sides[0]->y(1)
						- phi2(xi)*phi2(nu)*sides[2]->y(1);
						
			x_[i+j*n] = xtemp;
			y_[i+j*n] = ytemp;
		}
	}
}

void Domain::print_grid(){
	int ind;
	std::ofstream strm("outfile.txt");
	for(int ind = 0; ind<n_*m_; ++ind){
		strm << "(" << x_[ind] << ",  " << y_[ind] << ")" << std::endl;
		std::cout << "(" << x_[ind] << ",  " << y_[ind] << ")" << std::endl;
	}
	FILE *fx, *fy;
	fx =fopen(".\\outfileX.bin","wb");
	fy =fopen(".\\outfileY.bin","wb");
	fwrite(x_,sizeof(double),m_*n_,fx);
	fwrite(y_,sizeof(double),m_*n_,fy);
	fclose(fx);fclose(fy);
}


         
      