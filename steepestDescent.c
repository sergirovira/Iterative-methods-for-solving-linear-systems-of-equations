/*
Author: Sergi Rovira Cisterna
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcions.c" 

/*
Change this method for another
linear system
*/

void A(double * x,double *t){
    int i;
    t[0] = 4*x[0] - x[1];
    for(i=1;i<n-1;i++){
      t[i] = 4*x[i] - x[i-1] - x[i+1];
    }
    t[n-1] = 4*x[n-1] - x[n-2];
}


void getP(double *x,double *p){
    int i;
    A(x,p);
    p[0] -= 3;
    for(i=1;i<n-1;i++){
       p[i] -= 2;
    }
    p[n-1] -= 3;
}

/*
Steepest Descent Method
-----------------------
input: 
  - x: solution vector
  - p: pointer to value p
  - x_ant: helper vector 
  - t: helper vector
output:
  - itr: number of iterations before convergence

*/
int steepestDescent(double *x,double *x_ant,double *p,double *t){
  int i,itr;
  double alpha;
  double ptp; //dot product of p

  for(i=0;i<n;i++){
    x[i] = 0.9;
  }
  itr = 0;

  do
  {
    getP(x,p); //p = Ax - b
    A(p,t); //t = Ap
    ptp = product(p,p);

    alpha = (ptp/product(p,t));
    copyVector(x_ant,x);
    itr++;
    for(i=0;i<n;i++){
         x[i] = x_ant[i] - alpha*p[i];
    }
  } while(sqrt(ptp) > 1e-12);
  return itr;
}


int main(){

  double * x = (double *)malloc(n*sizeof(double));
  double * x_ant = (double *)malloc(n*sizeof(double));
  double * p = (double *)malloc(n*sizeof(double));
  double * t = (double *)malloc(n*sizeof(double));
  
  int itr = steepestDescent(x,x_ant,p,t);
  
  printf("Steepest Descent \n itr: %d\n x=",itr);
  printVector(x);

  free(x);
  free(x_ant);
  free(p);
  free(t);
  
  
  return 0;
}