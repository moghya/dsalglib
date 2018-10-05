#include<bits/stdc++.h>
using namespace std;


int prime = 101;

long reCalculateHash(string text, int oldIndex,int newIndex, long oldHash, int pattern_length){
	long newHash = oldHash - text[oldIndex];
	newHash	/= prime;
	newHash = newHash + text[newIndex] * pow(prime, pattern_length - 1);
	return newHash;
}	

long createHash(string str, int end){
	long hashVal = 0;
	for(int i=0; i<end; i++){
		hashVal += str[i] * pow(prime,	i);
	}
	return hashVal;
}

bool checkString(string pattern, string text_snip, int pat_start, int pat_end, int text_start, int text_end){
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

int patternSearch(string text, string pattern){
	int m = pattern.size();
	int n = text.size();

	long patternHash = createHash(pattern, m);
	long textHash 	 = createHash(text, m);
	for(int i=0; i<n - m + 1; i++){
		if(patternHash == textHash && checkString(pattern, text, 0, m, i, i + m)){
			return i;
		}else if(i < n - m + 1){
			textHash = reCalculateHash(text, i, i + m, textHash, m);
		}
	}
	return -1;
}

int main(){

	string text;
	string pattern;
	cout << "Enter the text: ";
	cin >> text;
	cout << "Enter the pattern to search in the text: ";
	cin >> pattern;
	
	int index = patternSearch(text, pattern);
	if(index != -1){
		cout << "Shift to " << index + 1 << " places to get the pattern in text" << endl;
	}else{
		cout << "Pattern not found" << endl;
	}

	return 0;
}
