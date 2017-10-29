#ifndef DSALGLIB_KMPSEARCH_H
#define DSALGLIB_KMPSEARCH_H

#include "array.h"

namespace dsa
{
    template<typename type>
	long long int ternarySearch(array<type> input, type left_index, type right_index, type value)
	{
	    if (left_index > right_index)
		return -1;

	    long long int middle_index_1 = left_index + (right_index-left_index)/3;
	    long long int middle_index_2 = right_index - (right_index-left_index)/3;

	    if (input[middle_index_1] == value)
		return middle_index_1;

	    if (input[middle_index_2] == value)
		return middle_index_2;

	    if (value < input[middle_index_1])         // Search in first half
		return ternarySearch(input, left_index, middle_index_1 - 1, value);
	    else if (value > input[middle_index_2])    // Search in third half
		return ternarySearch(input, middle_index_2 + 1, right_index, value);
	    else                                // Search in second half
		return ternarySearch(input, middle_index_1 + 1, middle_index_2 - 1, value);
	}
}

#endif //DSALGLIB_BINARYSEARCH_H
