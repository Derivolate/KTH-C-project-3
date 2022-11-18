#include "Domain.hpp"
#include "Curvebase.hpp"

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
	
void Domain::generate_grid(int m, int n){
	if(m<1 or n<1) 
		// throw error
	if(m_>0 or n_>0) { //if previous grid exists, reset grid points
		delete [] x_;
		delete [] y_;
	}
	x_ = new double[(m+1)*(n+1)]; 
	y_ = new double[(m+1)*(n+1)];
	m_ = m, n_= n;
	double hx(1.0/n), hy(1.0/m); // (FORCE FLOATING POINT DIVISION)
	for(int i; i<=n; ++i){ //Vertical index, indicates the row
		for(int j; j<=m; ++j){ //Horizontal index, indicates the column
			x_[i+j*(n+1)]=phi1(i*hx)*side[3]->x(j*hy)+phi2(i*hx)*side[1]->x(j*hy);// implement 5.26
			y_[i+j*(n+1)]=phi1(i*hy)*side[3]->x(j*hx)+phi2(i*hx)*side[1]->x(j*hy);
		}
	}
}