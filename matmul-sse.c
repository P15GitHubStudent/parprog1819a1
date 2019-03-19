#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>

//gcc -O2 lab5_with_sse.c -o lab5_with_sse -DN=10
//gcc -S lab5_with_sse.c -o lab5_with_sse -DN=10

void get_walltime(double *wct);

int main(int argc, char *argv[]) {
	int i, j, k;

	//Βήμα 1
	float *a, *b, *c;
	//128 bit leksh
    __m128 *va, *vb, *vc, *vd, sum;

	sum = _mm_set_ps(0.0, 0.0, 0.0, 0.0);
    
    int checkA = posix_memalign((void**)&a, 16, N*N*sizeof(float));
    if(checkA!=0) {
        return 1;
    }
    int checkB = posix_memalign((void**)&b, 16, N*N*sizeof(float));
    if(checkB!=0) {
        free(a);
        return 1;
    }
    int checkC = posix_memalign((void**)&c, 16, N*N*sizeof(float));
    if(checkC!=0) {
        free(a);
        free(b);
        return 1;
    }

	for(i=0; i<N*N; i++) {
		a[i] = 2.0;
		b[i] = 3.0;
		c[i] = 20.0;
	}

	
	//Βήμα 3
	double ts, te;
	get_walltime(&ts);
	float *pc = c;	

	vc = (__m128*)c;
	for(k=0; k<N; k++) {
		vb = (__m128*)b;
		for(j=0; j<N; j++){
			va = (__m128*)(a + k*N);
			sum = _mm_set_ps(0.0, 0.0, 0.0, 0.0);
			for(i=0; i< N; i+=4){
				sum += _mm_mul_ps((*va), (*vb));
				//printf("%f \n", sum[0]);
				va++; vb++;
			}
			*pc = sum[0] + sum[1] + sum[2] + sum[3];
			//printf("sum=%f", *pc);
			pc++;	
			//vc++;
		}
	}
	
	get_walltime(&te);
	
	printf("%lf\t%lf\n", te-ts, (unsigned long)N*N*N / ((te-ts) * 1e6));
	for(i=0; i<N*N; i++) {
		if(c[i] != 6.0 * N) {
			break;
		}
	}

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
