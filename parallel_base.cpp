#include <cstdio>
#include <chrono>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
 
/*
    #pragma omp parallel private(tid, nt)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();
*/
 
int vsum (int *v, int n)
{
    int i, r;
    
    r = 0;
    
    for (i=0; i<n; i++)
        r += v[i];
    
    return r;
}
 
int main (int argc, char **argv)
{
    int n, i, r;
    int *v;
    double elapsed;
    std::chrono::steady_clock::time_point tbegin, tend;
    
    n = atoi(argv[1]);
    
    printf("%i elements\n", n);
    
    v = static_cast<int*>( malloc(sizeof(int) * n) );
    
    for (i=0; i<n; i++)
        v[i] = 1;
    
    tbegin = std::chrono::steady_clock::now();
    r = vsum(v, n);
    tend = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> elapsed_ = std::chrono::duration_cast<std::chrono::duration<double>>(tend - tbegin);
	elapsed = elapsed_.count();
    printf("r = %i\n time: %f\n", r, elapsed);
    
    return 0;
}
