/*
 * Created by yadvendra20 on 3/12/2020
*/

#ifndef DSALGLIB_NUMTHEORY_FF_H
#define DSALGLIB_NUMTHEORY_FF_H

#include "../alginc.h"

namespace dsa {
	
	/*
	 * The binary exponentiation method computes 
	 * powers directed by the exponent bits, one 
	 * at a time. Bits of value 0 require a squaring; 
	 * bits of value 1 require a squaring and a multiplication.
	 * 
	 * More about binary exponentiantion: https://cp-algorithms.com/algebra/binary-exp.html
	*/
	
	long long binaryExponentiation(long long base, long long exponent) {
		if(base == 0LL)
			return 0LL;
		long long result = 1LL;
		while(exponent > 0) {
			if(exponent%2LL == 1LL)
				result *= base;
			base *= base;
			exponent /= 2LL;
		}
		return result;
	}
	
	/*
	 * Modular binary exponentiation
	*/
	long long modularBinaryExponentiation(long long base, long long exponent, long long mod) {
		if(base == 0LL)
			return 0LL;
		long long result = 1LL;
		while(exponent > 0) {
			if(exponent%2LL == 1LL)
				result = (result * base)%mod;
			base = (base * base)%mod;
			exponent /= 2LL;
		}
		return result;
	}
	
	/*
	 * GCD Computation
	*/
	
	long long gcd(long long first_num, long long second_num) {
		while(second_num > 0) {
			first_num %= second_num;
			swapit(first_num, second_num);
		}
		return first_num;
	}
}

#endif // DSALGLIB_NUMTHEORY_FF_H
