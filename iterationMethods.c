/*
Author: Sergi Rovira Cisterna
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcions.c"

/*
Jacobi Method
--------------------------------------------------
inputs: 
	x: solution vector
	x2: secondary vector to help with the iteration and memory management
	b: equation's system independent terms
output: 
	itr: number of iterations before convergence
*/

int jacobi(double *x,double *x2,double *b){
	int itr,i;

	for(i=0;i<n;i++){
		b[i] = (i+1)/(double)n;
		x[i] = 1;
	}
	itr = 0;

	do
	{
		copyVector(x2,x);
		itr++;
		//Change these lines for another linear system
		x[0] = (b[0] + 2*x2[1] - x2[n-1])/4.0;
		for(i = 1; i<n-1; i++){
			x[i] = (b[i] - 1*x2[i-1] + 2*x2[i+1])/4.0;
		}
		x[n-1] = (b[n-1] + 2*x2[0] - 1*x2[n-2])/4.0;

	} while((3*normInfVector(subtractVectors(n,x,x2)))>1e-12);
	return itr;
}

/*
Gauss-Seidel Method
-------------------
inputs: 
	x: solution vector
	x2: secondary vector to help with the iteration and memory management
	b: equation's system independent terms
output: 
	itr: number of iterations before convergence
*/

int gaussSeidel(double *x,double *x2,double *b){
	int itr,i;


	for(i=0;i<n;i++){
		b[i] = (i+1)/(double)n;
		x[i] = 1;
	}
	itr = 0;

	do
	{
		copyVector(x2,x);
		itr++;
		//Change these lines for another linear system
		x[0] = (b[0] + 2*x[1] - x[n-1])/4.0;
		for(i = 1; i<n-1; i++){
			x[i] = (b[i] - 1*x[i-1] + 2*x[i+1])/4.0;
		}
		x[n-1] = (b[n-1] + 2*x[0] - 1*x[n-2])/4.0;
	} while((3*normInfVector(subtractVectors(n,x,x2)))>1e-12);
	return itr;
}

/*
SOR Method
----------
inputs: 
	x: solution vector
	x2: secondary vector to help with the iteration and memory management
	b: equation's system independent terms
	w: successive over-relaxation offset
output: 
	itr: number of iterations before convergence
*/

int SOR(double *x,double *x2,double *b,float w){
	int itr,i;

    for(i=0;i<n;i++){
    	b[i] = (i+1)/(double)n;
		x[i] = 1;
    }
    itr = 0;
    
    do
    {
    	copyVector(x2,x);
    	itr++;
    	//Change these lines for another linear system
	    x[0] = x[0] + w*(b[0] + 2*x[1] - x[n-1] -4*x[0])/4.0;
	    for(i = 1; i<n-1; i++){
		    x[i] = x[i] + w*(b[i] - 1*x[i-1] + 2*x[i+1] -4*x[i])/4.0;
	    }
	    x[n-1] = x[n-1] + w*(b[n-1] + 2*x[0] - 1*x[n-2] -4*x[n-1])/4.0;
    } while((3*normInfVector(subtractVectors(n,x,x2)))>1e-12);

    return itr;
}


int main(){
	double *x = (double *)malloc(n*sizeof(double));
	double *x2 = (double *)malloc(n*sizeof(double));
	double *b = (double *)malloc(n*sizeof(double));
	int itr,i;
	float w = 0.1; 

	itr = jacobi(x,x2,b);

	printf("Jacobi: \n itr: %d \n x=",itr);
	printVector(x);

	itr = gaussSeidel(x,x2,b);

	printf("Gauss-Seidel: \n itr: %d \n x=",itr);
	printVector(x);

	printf("SOR:\n");
	for(i=0;i<20;i++){
		itr = SOR(x,x2,b,w);
		printf("w: %f, itr: %d \n x=",w,itr);
		w+= 0.05;
	}
	printVector(x);

	free(x);
	free(x2);
	free(b);

	return 0;
}