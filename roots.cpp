//This program is to find the roots of a single
//non-linear equation.  It will
// 1. Identify bracketed regions that enclose a root so as to generate
// initial guesses
// 2. Iterate using NR Method to find the roots to within a given tolerance
// 3. Find all roots in one execution

//****************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <time.h>
#include <stdio.h>
#define PI 3.14159265 //PI
#define E (2.7182818284590452353602874713526624977572470937L )
using namespace std;
//****************************

//FUNCTION DECLARATIONS//
double guess(double lower_bound, double upper_bound); 
double fx0_1(double x_0);
double fpx0_1(double x_0);
double fx0_2(double x_0);
double fpx0_2(double x_0);
//********************//

ofstream data_out("output2.txt"); //output data to text file

int main() {

  int i; //iterator for for loops

  double LBound = 0.; //the lower bound
  double UBound = 0.; //the upper bound
   
  int num_roots = 2; //number of roots for a function
  
  double bounds[num_roots][2]; //bounds for each root of a function
 
 /*
  //BOUNDS FOR PROBLEM 1
  bounds[0][0] = .5;
  bounds[0][1] = 1.5;
  bounds[1][0] = 3.0;
  bounds[1][1] = 4.0;
  bounds[2][0] = 5.0;
  bounds[2][1] = 6.0;
*/
  
  //BOUNDS FOR PROBLEM 2
  bounds[0][0] = -1.0;
  bounds[0][1] = 0.0;
  bounds[1][0] = 1.0;
  bounds[1][1] = 2.0;
  
 
 double rootsMat[num_roots]; //matrix to hold all the results

  double x_0 = 0.; //first iteration guess
  double x_1 = 0.; //next iteration guess
  double tau = .000001; //tolerance for guess

 // for each root, the bounds are taken and the root is found
  for(i = 0; i < num_roots; i++)
  {
    LBound = bounds[i][0]; //lower bound for ith root
    UBound = bounds[i][1]; //upper bound for ith root
   
    x_0 = guess(LBound, UBound); //initial guess for root

    //next iteration to calcualte root
    //x_1 = x_0 - (fx0_1(x_0)/fpx0_1(x_0));
    x_1 = x_0 - (fx0_2(x_0)/fpx0_2(x_0));
    
    //iteration loop to find next x_1 until within tolerance
    while(std::abs(x_1 - x_0) > tau) {
    
      x_0 = x_1; //update values for iteration
      //x_1 = x_0 - (fx0_1(x_0)/fpx0_1(x_0));
      x_1 = x_0 - (fx0_2(x_0)/fpx0_2(x_0));
    
    }

    //store roots in matrix for fun
    rootsMat[i] = x_1; //place root value in roots matrix
    data_out<<i<<'\t'<<rootsMat[i]<<endl; //print to output file
  }
}

//this function takes in the lower and upper bound on the roots of a 
//function and returns a guess, the average of the two bounds.
double guess(double lower_bound, double upper_bound){
  double avg;
  avg = (lower_bound + upper_bound) / 2.;

  return avg;
}

//returns f(x_0) for problem1
double fx0_1(double x_0) {
  return (sin(x_0) + log(x_0) - 1);
}

//return f'(x_0) for problem1
double fpx0_1(double x_0) {
  return (cos(x_0) + (1/x_0));
}

//returns f(x_0) for problem2
double fx0_2(double x_0) {
  return (pow(E, x_0)+x_0*x_0-3.*x_0-2);
}

//returns f'(x_0) for problem2
double fpx0_2(double x_0) {
  return((pow(E, x_0)+2.*x_0-3));
}
