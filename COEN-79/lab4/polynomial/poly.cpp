#include <iostream>
#include <cmath>
#include <limits.h>
#include "poly.h"

//coded mainly by Nick L. with assistance from Tanner K. 

using namespace std;
using namespace coen79_lab4;
namespace coen79_lab4{
polynomial::polynomial(double c, unsigned int exponent){//default vals 0.0 and 0
  current_degree = exponent;
  for(int i=0; i<=MAXIMUM_DEGREE; i++){//set all coefficients to 0.0.
    coef[i] = 0.0;
  }
  coef[current_degree] = c;//change current degree's coeff to c.
  //is redundant with default constructor, but doesn't cause problems.
}

void polynomial::assign_coef(double coefficient, unsigned int exponent){
  assert(exponent <= MAXIMUM_DEGREE);
  coef[exponent] = coefficient;//set that exponent's coefficient to var coefficient
  update_current_degree();
}

void polynomial::add_to_coef(double amount, unsigned int exponent){
  assert(exponent <= MAXIMUM_DEGREE);
  coef[exponent] += amount;//add amount to cofficient.
  update_current_degree();
}

void polynomial::clear(){
  for(int i=0; i<=MAXIMUM_DEGREE; i++){
    coef[i] = 0.0;
  }
  current_degree = (unsigned int)0;
}

polynomial polynomial::antiderivative() const{
  assert(current_degree < MAXIMUM_DEGREE);
  polynomial temp;
  for(int i = 0; i <= current_degree; i++){
    temp.assign_coef(coef[i]/(i+1),i+1); // the 0th space in temp is skipped because c=0
  }
  temp.update_current_degree();
  return temp;
}

double polynomial::coefficient(unsigned int exponent) const{
  if(!(int(exponent) <= MAXIMUM_DEGREE))return 0;
  return coef[exponent];
}

double polynomial::definite_integral(double x0, double x1) const{
  polynomial temp = antiderivative();
  return temp.eval(x1) - temp.eval(x0);
}

void polynomial::update_current_degree(){//helper function for other functions. Checks current degree of the polynomial and updates the variable current_degree to reflect this value.
  for(int i=0; i<=MAXIMUM_DEGREE; i++){
    if(coef[i]!=0.0)current_degree = (unsigned int)i;
  }
}

unsigned int polynomial::degree() const{
  return current_degree;
}

polynomial polynomial::derivative() const{
  assert(current_degree <= MAXIMUM_DEGREE);
  polynomial temp;
  for(int i = 1; i <= current_degree; i++){
    temp.assign_coef(coef[i]*i,i-1);
  }
  temp.update_current_degree();
  return temp;
}

double polynomial::eval(double x) const{
  double sum = 0;
  for(int i = 0; i <= current_degree; i++){
    sum += coef[i]*pow(x,i);
  }
  return sum;
}

bool polynomial::is_zero() const{//only return true if every coeff is zero.
  for(int i = 0; i <= MAXIMUM_DEGREE; i++){
    if(coef[i] != 0) return false;
  }
  return true;
}

int polynomial::next_term(unsigned int e) const{
  for(int i = e+1; i <= current_degree; i++){
    if(coef[i] != 0) return i;
  }
  return 0;
}

int polynomial::previous_term(unsigned int e) const{
  for(int i = e-1; i >= 0; i--){
    if(coef[i] != 0) return i;
  }
  return UINT_MAX;
}

/* polynomial p1(1,2);
   p1(7);
   7^2.
   Allows you to pass a parameter to a polynomial variable directly, which 
   returns that polynomial where x = var.
*/

double polynomial::operator()(double x) const{
  return eval(x);
}

polynomial operator -(const polynomial& p1, const polynomial& p2){
  polynomial temp;
  int maxDeg;
  if(p1.degree()>p2.degree())
    maxDeg = p1.degree();
  else
    maxDeg = p2.degree();
  for(int i = 0; i <= maxDeg; i++){
    temp.assign_coef(p1.coefficient(i)-p2.coefficient(i),i);
  }
  temp.update_current_degree();
  return temp;
}

polynomial operator +(const polynomial& p1, const polynomial& p2){
  int maxDeg;
  if(p1.degree()>p2.degree())
    maxDeg = p1.degree();
  else
    maxDeg = p1.degree();
  polynomial temp;
  for(int i = 0; i <= maxDeg; i++){
    temp.assign_coef(p1.coefficient(i)+p2.coefficient(i),i);
  }
  temp.update_current_degree();
  return temp;
}

//precondition: p1 * p2 does not exceed MAXIMUM_DEGREE. Or you're gonna have a bad time.
polynomial operator *(const polynomial& p1, const polynomial& p2){
  int maxDeg;
  if(p1.degree()>p2.degree())
    maxDeg = p1.degree();
  else
    maxDeg = p1.degree();
  polynomial temp;
  for(int i = 0; i <= maxDeg; i++){
    for(int j = 0; j <= maxDeg; j++){
      temp.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
      //every term of p1 gets multiplied by every term of j, and the result is summed to its spot in temp.
    }
  }
  temp.update_current_degree();
  return temp;
}

ostream& operator << (ostream& out, const polynomial& p){
  
  int deg = int(p.degree());
  if(p.coefficient(deg) < 0) out << "-";//give the first value a - if it's negative
  if(deg!=0 &&  abs(p.coefficient(deg)) != 1) out << p.coefficient(deg);// don't show the first coeff if it's 1
  if(deg == 1) out << "x";//don't show the first coeff's ^ if it's 1
  if(deg > 1) out << "x^" << deg;//show the first coeff's ^ if it's >1
  if(deg == 0) out << p.coefficient(deg);
  deg --;
  while(deg > 1){
    if (p.coefficient(deg)==0){
      deg--;
      continue; //skip the following steps if there isn't a coefficient at this space.
    }
    if (p.coefficient(deg) > 0) out << " + ";
    else out << " - ";
    
    if (abs(p.coefficient(deg)) != 1) out << abs(p.coefficient(deg));// don't show 1.
    out << "x^" << deg;//condition for this is handled by while loop.
    deg--;
  }
  if(deg == 1){
    if(p.coefficient(deg)!=0){
      if(p.coefficient(deg) > 0) out << " + ";
      else out << " - ";
    
      if(abs(p.coefficient(deg)) != 1)out << abs(p.coefficient(deg));
      out << "x";
    }
    deg--;
  }
  if(deg == 0 && p.coefficient(deg) != 0){
    if(p.coefficient(deg) > 0) out << " + " << p.coefficient(deg);
    else out << " - " << abs(p.coefficient(deg));
  }
  out << endl;
  return out;
}
}
