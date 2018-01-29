#ifndef DSALGLIB_KMPSEARCH_H
#define DSALGLIB_KMPSEARCH_H

#include "array.h"

namespace dsa
{
    template<typename type>
	long long int jumpsearch( array<type> arr, type x)
	{
		// Finding block size to be jumped
		long long int n = arr.size(); 
		long long int step = sqrt(n);
	 
		// Finding the block where element is
		// present (if it is present)
		long long int prev = 0;
		while (arr[min(step, n)-1] < x)
		{
			prev = step;
			step += sqrt(n);
			if (prev >= n)
				return -1;
		}
	 
		// Doing a linear search for x in block
		// beginning with prev.
		while (arr[prev] < x)
		{
			prev++;
	 
			// If we reached next block or end of
			// array, element is not present.
			if (prev == min(step, n))
				return -1;
		}
		// If element is found
		if (arr[prev] == x)
			return prev;
	 
		return -1;
	}
    
}
#endif //DSALGLIB_KMPSEARCH_H