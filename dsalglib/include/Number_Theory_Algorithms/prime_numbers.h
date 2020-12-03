/*
 * Created by yadvendra20 on 3/12/2020
*/

#ifndef DSALGLIB_NUMTHEORY_PRIMES_H
#define DSALGLIB_NUMTHEORY_PRIMES_H

#include "../array.h"

namespace dsa {
	
	// returns true if the number is prime otherwise returns false
	
	/*
	 * The complexity of the isNumPrime function is O(square_root(number))
	*/
	
	bool isNumPrime(int number) {
		if(number <= 1)
			return false;
		for(int i = 2; i * i <= number; i++) {
			if(number % i == 0)
				return false;
		}
		return true;
	}
	
	// Sieve of eratosthenes
	
	/*
	 * The sieve function returns a boolean array is_prime of 'number' size
	 * where is_prime[num] = true (if num is a prime number) otherwise false
	 * 
	 * More about sieve of eratosthenes: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
	*/
	
	array<bool> sieve(long long int number) {
		
		array<bool> is_prime(number + 1, true);
		is_prime[0] = false;
		is_prime[1] = false;
		
		for(int i = 2; i * i <= number; i++) {
			if(is_prime[i]) {
				for(int j = i * i; j <= number; j += i)
					is_prime[j] = false;
			}
		}
		return is_prime;
	}
}

#endif // DSALGLIB_NUMTHEORY_PRIMES_H
