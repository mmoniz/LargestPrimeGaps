void * Malloc(int num_elements, int el_size, MPI_Comm comm, int rank);
void calcRangePerProcess(mpz_t N, int p, mpz_t low, mpz_t *nums_per_process);
void nextPrime(mpz_t current_prime, mpz_t previous);
unsigned long maxGap(mpz_t lower, mpz_t upper, mpz_t high, mpz_t gap);
