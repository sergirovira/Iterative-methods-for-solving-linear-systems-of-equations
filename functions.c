#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n = 1e6;

void printVector(double *v){
	int i;
	printf("(");
	
	for(i = 0;i<5;i++){
		printf("%e,",v[i]);
	}
	printf("...");
	for(i = n-5;i<n;i++){
		printf(",%e",v[i]);
	}
	printf(")\n");
}

void printVectorN(double *v,int n){
	int i;
	printf("(");
	
	for(i = 0;i<n-1;i++){
		printf("%e,",v[i]);
	}
	printf("%e",v[n-1]);
	printf(")\n");
}

double normInfVector(double *v){
	double max = fabs(v[0]);
	double term;
	int i;
	for(i=1;i<n;i++){
		term = fabs(v[i]);
		if(term>max){
			max = term;
		}
	}
	return max;
}

double product(double *a, double *b){
    int i;
    double sum = 0;
    for(i=0;i<n;i++){
	     sum += a[i]*b[i];      
    }
    return sum;
}

double * subtractVectors(int l,double *a,double *b){
	double *v = (double *)malloc(l*sizeof(double));
	int i;
	for(i=0;i<l;i++){
		v[i] = a[i]-b[i];
	}
	return v;

}

void copyVector(double *a,double *b){
	int i;
	for(i=0;i<n;i++){
		a[i] = b[i];
	}
}
