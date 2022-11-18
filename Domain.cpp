#include "Domain.hpp"
#include "Curvebase.hpp"
#include <cmath>

// Domain::Domain(const Curvebase& s1, const Curvebase& s2, const Curvebase& s3, const Curvebase& s4) {
// 	sides[0] = &s1;
// 	sides[1] = &s2;
// 	sides[2] = &s3;
// 	sides[3] = &s4;
// 	if (~check_consistency()) //If thegrid is not consistent, unassign them, why not throw error?
// 		sides[0] = sides[1] = sides[2] = sides[3] = nullptr;
// 	m_ = n_ = 0;
// 	x_ = y_ = nullptr;
// }


Domain::~Domain() {
	if (m_ > 0) {
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
	
void Domain::generate_grid(int m, int n, int c){
	if(m<1 or n<1) 
		// throw error
	if(m_>0 or n_>0) { //if previous grid exists, reset grid points
		delete [] x_;
		delete [] y_;
	}
	x_ = new double[(m+1)*(n+1)]; 
	y_ = new double[(m+1)*(n+1)];
	m_ = m, n_= n;
	double h1(1.0/n), h2(1.0/m); // (FORCE FLOATING POINT DIVISION)
	for(int i; i<=n; ++i){ //Vertical index, indicates the row
		for(int j; j<=m; ++j){ //Horizontal index, indicates the column
			if (c == 1) double xi(i*h1),nu(j*h2); // equidistant s
			else if (c==2) double xi(1+(tanh(3)*((i*h1)-1))/tanh(3)),nu(1+(tanh(3)*((j*h2)-1))/tanh(3)); // stretched s position Task 5
			x_[i+j*(n+1)]=phi1(xi)*sides[3]->x(nu)+phi2(xi)*sides[1]->x(nu)
						+ phi1(nu)*sides[0]->x(xi) + phi2(nu)*sides[2]->x(xi)
						- phi1(xi)*phi1(nu)*sides[0]->x(0)
						- phi1(xi)*phi2(nu)*sides[3]->x(1)
						- phi2(xi)*phi1(nu)*sides[2]->x(0)
						- phi2(xi)*phi2(nu)*sides[1]->x(1);
			y_[i+j*(n+1)]=phi1(xi)*sides[3]->y(nu)+phi2(xi)*sides[1]->y(nu)
						+ phi1(nu)*sides[0]->y(xi) + phi2(nu)*sides[2]->y(xi)
						- phi1(xi)*phi1(nu)*sides[0]->y(0)
						- phi1(xi)*phi2(nu)*sides[3]->y(1)
						- phi2(xi)*phi1(nu)*sides[2]->y(0)
						- phi2(xi)*phi2(nu)*sides[1]->y(1);
		}
	}
}