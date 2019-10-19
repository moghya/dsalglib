#include<bits/stdc++.h>
#include<iomanip>
using namespace std;
int main()
{
    string str;
    cin>>str;
    //Length of the given string;
    int n = str.size();
    //vector pair of each suffix string and it's starting index;
    vector<pair<string, int> > vec_pair;
    //Generate each suffix string and it's corresponding starting index and make vector pair of both;
    for(int i=0;i<str.size();i++)
        vec_pair.push_back(make_pair(str.substr(i,n-i), i));
    //sort the suffix strings with respect to it's ASCII value;
    sort(vec_pair.begin(), vec_pair.end());
    //Print all suffix string and it's starting index;
    cout << setw(n+5) << left << "SUFFIX" << right << "INDEX" << endl;
    for(int i=0;i<vec_pair.size();i++)
        cout << setw(n+5) << left << vec_pair[i].first << right << vec_pair[i].second << endl;
    return 0;
}
