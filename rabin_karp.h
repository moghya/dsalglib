#infndef DSALGLIB_RABINKARP_H
#define DSALGLIB_RABINKARP_H

#include "array.h"
namespace dsa{

	static const long long int mod = 1e9 + 7;
	long long int prime = 101;

	template<typename type>
// modified recursive power function
	long long pow(long long x, long long y){
		if(y == 0){
			return 1;
		}if(y == 1){
			return x%mod;
		}
		else if(y % 2 == 1){
			return ((x%mod) * pow((x%mod * x%mod)%mod, y/2))%mod; 
		}else{
			return pow(((x%mod) * (x%mod))%mod, y/2)%mod;
		}		
	}

	template<typename type>
// rolling hash
	long long int reCalculateHash(array<type> text,long long int oldIndex,long long int newIndex, long long int oldHash, long long int pattern_length){
		long long int newHash = (oldHash - text[oldIndex])%mod;
		newHash	/= prime;
		newHash = (newHash + text[newIndex] * pow(prime, pattern_length - 1))%mod;
		return newHash;
	}	

	template<typename type>
// creates a hash value
	long long int createHash(array<type> str, long long int end){
		long long int hashVal = 0;
		for(long long int i=0; i<end; i++){
			hashVal = (hashVal + (str[i] * pow(prime,	i))%mod)%mod; 
		}
		return hashVal;
	}

	template<typename type>
// checks if two strings of same hash value are equal or not
	bool checkString(array<type> pattern, array<type> text_snip, long long int pat_start, long long int pat_end, long long int text_start, long long int text_end){
		while(pat_start < pat_end && text_start < text_end){
			if(pattern[pat_start] != text_snip[text_start]){
				return false;
			}else{
				pat_start++;
				text_start++;
			}
		}	
		return true;
	}

	template<typename type>
// finds the valid/invalid shift for pattern in text
	int patternSearch(array<type> text, array<type> pattern){
		long long int m = pattern.size();
		long long int n = text.size();

		long long int patternHash = createHash(pattern, m);
		long long int textHash 	 = createHash(text, m);
		for(long long int i=0; i<n - m + 1; i++){
			if(patternHash == textHash && checkString(pattern, text, 0, m, i, i + m)){
				return i;
			}else if(i < n - m + 1){
				textHash = reCalculateHash(text, i, i + m, textHash, m);
			}
		}
		return -1;
	}
}
#endif	//DSALGLIB_RABINKARP_H
