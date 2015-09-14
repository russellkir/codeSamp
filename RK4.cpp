// RK4.cpp
//dfs
// This program implements a fourth-order Runge-Kutta algorithm to solve a single first-order ordinary differential equation 
//
//*****************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdio.h>
using namespace std;
//*****************

// declaration of functions/subroutines

double f1(double t, double x3);	// the right hand side of the ODE dx/dt = f1(t,x)
double f2(double t, double x4);
double f3(double t, double x1, double x2);
double f4(double t, double x1, double x2); 

// declaration of output stream

ofstream data_out("output2d.txt"); // output data

int main() {
	
	// variable declarations
    int i,j,k; // loop counters 
    
    double ttotal = 50.; // total time
    double delt = 0.1; // time step
    double t = 0.; // running time
    const int n = int(ttotal/delt); // number of points in discretization after initial value
    
    double k11, k21, k31, k41; // RK parameters
    double k12, k22, k32, k42; // RK parameters
    double k13, k23, k33, k43;
    double k14, k24, k34, k44;
    //double x10 = 1.; // initial condition
    double x1 = 0;
    double x2 = 1;
    double x3 = 0;
    double x4 = 0;
    
    data_out<<t<<'\t'<<x1<<endl; // initial condition
    
    for(i=1;i<=n;i++) {
	    
	    k11 = delt*f1(t,x3);
	    k12 = delt*f2(t,x4);
        k13 = delt*f3(t,x1,x2);
        k14 = delt*f4(t,x1,x2);

        k21 = delt*f1(t+.5*delt,x3+.5*k13);
        k22 = delt*f2(t+.5*delt,x4+.5*k14);
	    k23 = delt*f3(t+.5*delt,x1+.5*k11,x2+.5*k12);
        k24 = delt*f4(t+.5*delt,x1+.5*k11,x2+.5*k12);

        k31 = delt*f1(t+.5*delt,x3+.5*k23);
        k32 = delt*f2(t+.5*delt,x4+.5*k24);
        k33 = delt*f3(t+.5*delt,x1+.5*k21,x2+.5*k22);
        k34 = delt*f4(t+.5*delt,x1+.5*k21,x2+.5*k22);

        k41 = delt*f1(t+delt,x3+k33);
	    k42 = delt*f2(t+delt,x4+k34);
	    k43 = delt*f3(t+delt,x1+k31,x2+k32);
        k44 = delt*f4(t+delt,x1+k31,x2+k32);

        //x values
	    x1 = x1 + (k11 + 2.*k21 + 2.*k31 + k41)/6.;
	    x2 = x2 + (k12 + 2.*k22 + 2.*k32 + k42)/6.;
        x3 = x3 + (k13 + 2.*k23 + 2.*k33 + k43)/6.;
        x4 = x4 + (k14 + 2.*k24 + 2.*k34 + k44)/6.;
        t = t + delt;
	    
	    data_out<<t<<'\t'<<x1<<'\t'<<x2<</*'\t'<<x3<<'\t'<<x4<<*/endl;	    
    }
}	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double f1(double t, double x3) {
    double f1;
    f1 = x3;
    return f1;
}
double f2(double t, double x4) {
  double f2;
  f2 = x4;
  return f2;
}
double f3(double t, double x1, double x2){
  double f3;
  f3 = -3.*x1 + x2 + 2*exp(-0.5*t);
  return f3;
}
double f4(double t, double x1, double x2){
  double f4;
  f4 = x1/3 - 2.*x2;
  return f4;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
