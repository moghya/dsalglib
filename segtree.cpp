#include<bits/stdc++.h>
using namespace std ;

/* This code implements segment tree */
/* The Segment Tree solves problems regarding queries asking maximum values in a given range */

const int N = 100000 ; // this is the public datamember of the class denoting the maximum size of the array .

int tree[4*N + 2] ; // Maximum size of the array can be N  , this is  the public data member for the class;

void update(int ind , int val ,  int start = 1 , int end = N , int node = 1)  // Member Function
{
	if(start == end)
	{
		tree[node] = val ; 
		return  ;
	}
	
	int mid = (start + end)/2 ; 
	
	if(ind <= mid)
	update(  ind , val , start , mid , 2*node) ; 
	else
	update(ind , val ,  mid + 1 , end, 2*node + 1 )  ; 
	
	
	if(tree[2*node] > tree[2*node + 1])
	tree[node] = tree[2*node] ; 
	else
	tree[node] = tree[2*node + 1] ;  
}

// When a query is asked  , the parameter l will denote the start value of the range , r will denote end value of the range .

int query(int l , int  r , int  start  = 1 ,int end = N , int node = 1)  //Member Function
{
	if(start > end || l>r || l>end || r < start)
	return 0 ; 
	
	if(start >=l && end <=r)
	return tree[node] ;
	
	int mid = (start + end)/2 ; 
	
	int p1 = query(  l , r , start , mid , 2*node) ; 
	int p2 = query( l , r , mid+1 , end , 2*node + 1) ; 
	
	if(p1 > p2)
	return p1 ; 
	else
	return p2 ; 
}

// The user just needs to pass the l , r values in the query function . The rest have been default specified . 
//The user needs to pass the ind , val values in the update function. the rest are default specified .

int main()
{
	return  0 ;
}
