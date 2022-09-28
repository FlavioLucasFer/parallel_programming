#include <cstdio>
#include <iostream>
#include <cmath>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
 
/*
    #pragma omp parallel private(tid, nt)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();
*/

struct parallel_int_t {
	int data = 0;
	char trash[60];
};

int vsum (int *v, int n)
{
    int i, r, p, p_rest, nt, tid;
    r = 0;
    
    #pragma omp parallel master
		nt = omp_get_num_threads();
	
	p = floor(n / nt);
	p_rest = n - (p * nt);
	
	parallel_int_t ms[nt];
	
	#pragma omp parallel private(tid)
	{
		int start, internal_p;
		internal_p = p;
		
		tid = omp_get_thread_num();
		start = tid * p;
		
		if (tid == (nt - 1))
			internal_p += p_rest;
		
		for (int i = 0; i < internal_p; i++)
			ms[tid].data += v[start + i];
	}
	
	for (int i = 0; i < nt; i++)
		r += ms[i].data;
    
    return r;
}
 
int main (int argc, char **argv)
{
    int n, i, r;
    int *v;
    
    n = atoi(argv[1]);
    
    printf("%i elements\n", n);
    
    v = static_cast<int*>( malloc(sizeof(int) * n) );
    
    for (i=0; i<n; i++)
        v[i] = 1;
    
    r = vsum(v, n);
    
    printf("r = %i\n", r);
    
    return 0;
}
