
/**
 * calculate pi
 */


#include <stdio.h>
#include <math.h>
// For the CUDA runtime routines (prefixed with "cuda_")
#include <cuda_runtime.h>


//#define BLOCKS  512
#define NUMTHREADS 1024
#define ITERATIONS 2e09


double cuda();

