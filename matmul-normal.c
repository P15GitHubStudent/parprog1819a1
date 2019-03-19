#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//gcc -O2 lab5.c -o lab5 -DN=400
//gcc -S lab5.c -o lab5 -DN=400

void get_walltime(double *wct);

int main(int argc, char *argv[]) {
	int i, j, k;

	//Βήμα 1
	// creation of 3 arrays with size N * N  we treat them as 2d array's 
	float *a, *b, *c;
	a = (float*)malloc(N*N*sizeof(float));
	if (a == NULL){
		return -1;
	}
	b = (float*)malloc(N*N*sizeof(float));
	if (b == NULL){
		free(a);
		return -1;
	}
	c = (float*)malloc(N*N*sizeof(float));
	if (c == NULL){
		free(a);
		free(b);
		return -1;
	}	

	// Initializing our data
	for(i=0; i<N*N; i++) {
		a[i] = 2.0;
		b[i] = 3.0;
		c[i] = 20.0;
	}
	
	//Βήμα 3
	double ts, te;
	
	// Arxi metriseon gia ton xrono
	get_walltime(&ts);
	
	// kanoyme transpose ton deytero pinaka gia eynohkh prospelash sthn kryfh mnhmh
	// episis upologizetai to dot product to opoio dinetai os timi ston pinaka c meso tou dereference tou pc
	float *pa, *pb, *pc, sum;
	pc = c;
	for(k=0; k<N; k++) {
		pb = b;
		for(j=0; j<N; j++) {
			pa = a + k*N;
			sum = 0;
			for(i=0; i<N; i++) {
				sum = sum + (*pa) * (*pb);
				pa++; pb++;
			}
			*pc = sum;
			pc++;
		}
	}
	//telos metriseon gia ton xrono
	get_walltime(&te);
	
	//float mflops = (N * N * N) / ((te - ts) * 1e6);
	printf("%lf\t%lf\n", te-ts, (unsigned long)N*N*N / ((te-ts) * 1e6));
	
	// Kodikas elenxou gia na sigoureutoume oti oi times tou pinaka c einai sostes kai episis gia na mhn ginoun optimatizations 
	for(i=0; i<N*N; i++) {
		if(c[i] != 6.0 * N){
			break;
		}
	}

	//apodesmeusi tis dynamikis desmeusis tis mnimis minimis
	free(a);
	free(b);
	free(c);

	return 0;
}

void get_walltime(double *wct) {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	*wct = (double)(tp.tv_sec + tp.tv_usec / 1000000.0);
}

