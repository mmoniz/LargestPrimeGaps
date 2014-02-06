/* common.c 

   Contains functions Malloc and calcNumsPerProcess. 
   Malloc allocates memory through malloc and aborts MPI, if malloc
   fails
   calcNumsPerProcess calculates how many "numbers" to be 
   allocated to a process.

*/
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#include "mpi.h"


void * Malloc(int num_elements, int el_size, MPI_Comm comm, int rank)
{
  void *b = malloc(num_elements*el_size);
  if (b==NULL)
    {
      fprintf(stderr, "*** PROCESS %d: MALLOC COULD NOT ALLOCATE %d ELEMENTS OF SIZE %d BYTES\n", 
	      rank, num_elements, el_size);
      MPI_Abort( comm, 1);      
    }
  return b;
}

void nextPrime(mpz_t current_prime, mpz_t previous){
	int is_prime = 0;
	int reps = 25;

	while(is_prime == 0){
		mpz_nextprime(current_prime, previous);
		is_prime = mpz_probab_prime_p(current_prime, reps);
	}
}


void calcRangePerProcess(mpz_t N, int p, mpz_t low, mpz_t *nums_per_node)
{
  int i;
  mpz_t modulo;
  mpz_init(modulo);

  mpz_init_set(nums_per_node[0], low);

  for (i = 1; i < p; i++) {
    mpz_init(nums_per_node[i]);

    /*nums_per_node[i] += nums_per_node[i] + N/p*/
    mpz_add(nums_per_node[i], nums_per_node[i], nums_per_node[i-1]);
    mpz_cdiv_q_ui(modulo,N,p);
    mpz_add(nums_per_node[i], nums_per_node[i], modulo);

    /*modulo = N%p*/
    mpz_mod_ui(modulo, N, p);

    if(mpz_cmp_ui(modulo, i) < 0){
      mpz_add_ui(nums_per_node[i], nums_per_node[i], 1);
    }    
  }
}



  
