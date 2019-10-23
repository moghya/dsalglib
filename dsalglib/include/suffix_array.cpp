#include <iostream> 
#include <cstring> 
#include <algorithm> 
using namespace std; 
  
// Structure to store information of a suffix 
struct suffix 
{ 
    int index; 
    char *suff; 
}; 
  
// A comparison function used by sort() to compare two suffixes 
int cmp(struct suffix a, struct suffix b) 
{ 
    return strcmp(a.suff, b.suff) < 0? 1 : 0; 
} 
  
int *buildSuffixArray(char *txt, int n) 
{ 
    // A structure to store suffixes and their indexes 
    struct suffix suffixes[n]; 
  
    for (int i = 0; i < n; i++) 
    { 
        suffixes[i].index = i; 
        suffixes[i].suff = (txt+i); 
    } 
  
    // Sort the suffixes using the comparison function 
    // defined above. 
    sort(suffixes, suffixes+n, cmp); 
  
    int *suffixArr = new int[n]; 
    for (int i = 0; i < n; i++) 
        suffixArr[i] = suffixes[i].index; 
  
    // Return the suffix array 
    return  suffixArr; 
} 
  
// A utility function to print an array of given size 
void printArr(int arr[], int n) 
{ 
    for(int i = 0; i < n; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 
  
int main() 
{ 
    char txt[] = "joker"; 
    int n = strlen(txt); 
    int *suffixArr = buildSuffixArray(txt,  n); 
    cout << "Following is suffix array for " << txt << endl; 
    printArr(suffixArr, n); 
    return 0; 
} 