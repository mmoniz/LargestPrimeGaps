/* 
	as3.c 
	Main program for the A3 solution
	March 12, 2013
	Mike Moniz - 0950795
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>
#include <gmp.h>

#include "as3.h"

int main(int argc, char* argv[]) 
{

	int my_rank, p, i;

	mpz_t low, high, lower, gap, N, upper;
	
	mpz_init(gap);
	mpz_init(N);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Obtain the range. We do not check for eroneous input. */
	mpz_init_set_str(low, argv[1], 10);
	mpz_init_set_str(high, argv[2], 10);

	mpz_sub(N, high, low);

	/* Find how many rows per process. */
        mpz_t *range;
        range = (mpz_t*)Malloc(p, sizeof(mpz_t), MPI_COMM_WORLD, my_rank);


        calcRangePerProcess(N, p, low, range);

	/*Upper bound will be the lower bound of the next range or the maximum bound if
	it is on the highest element of the range
	*/
	if(my_rank < p - 1){
		mpz_init_set(upper, range[my_rank + 1]);
	} else {
		mpz_init_set(upper, high);
	}

	/*Starting prime is lower bound*/
	mpz_init_set(lower, range[my_rank]);

	double time = MPI_Wtime();
	unsigned long max_gap = maxGap(lower, upper, high, gap);
	time = MPI_Wtime() - time;

	unsigned long max;
	double timerecv;

	MPI_Reduce(&max_gap, &max, 1, MPI_UNSIGNED_LONG, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&time, &timerecv, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);	

	
	if(my_rank == 0) {
		printf("Max gap: %lu\n", max);
		printf("%d %s %.2e\n", p, argv[2], timerecv);
	}

	MPI_Finalize();
	return 0;
}

unsigned long maxGap(mpz_t lower, mpz_t upper, mpz_t high, mpz_t gap){
	mpz_t current_prime, local_gap;
	mpz_init(current_prime);
	mpz_init(local_gap);

	while( mpz_cmp(lower, upper) < 0 ){
		nextPrime(current_prime, lower);

		/*Calculate the local gap*/
		mpz_sub(local_gap, current_prime, lower);
		
		if(mpz_cmp(local_gap, gap) > 0){
			mpz_set(gap, local_gap);
		}

		/*update the lower bound*/
		mpz_set(lower, current_prime);
	}

	/*Check next prime to ensure we don't miss a gap*/
	nextPrime(current_prime, lower);
	if(mpz_cmp(current_prime, high) <= 0){
		if(mpz_cmp(local_gap, gap) > 0){
			mpz_set(gap, local_gap);
		}		
	}

	return mpz_get_ui(gap);
}
