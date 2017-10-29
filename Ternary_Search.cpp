//SATYAMEVA JAYATE 		

			// Used to find max value in unimodal function

#include <bits/stdc++.h>
using namespace std;
int arr[100];
int ternary(int l,int r,int key)
{
	int mid1=(r+2*l)/3; // Using Section formula
	int mid2=(2*r+l)/3;
	if(l<=r)
	{
		if(arr[mid1]==key)
			return mid1;
		if(arr[mid2]==key)
			return mid2;
		else
		{
			if(arr[mid1]>key)
		   	   return ternary(l,mid1-1,key);
			else if(arr[mid2] <key)
				return ternary(mid2+1,r,key);
			else 
				return ternary(mid1+1,mid2-1,key);
		}
	}
	return -1;
}
int main()
{
	int i,n,key,ans;
	cin >> n; // Element in the array
	for(i=0;i<n;i++)
	{
		cin >> arr[i];
	}
	sort(arr,arr+n);// Hence the array is sorted
	cout <<"Enter the element to be searched\n";
	cin >> key;
	ans = ternary(0,n,key);
	cout <<ans<<"\n";
	return 0;
}

