/*
 * main.cpp
 *
 *  Created on: 27 kwi 2019
 *      Author: Denis
 */

#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int N = 40;

inline void sum(int*p,vector <int> d){
	*p=0;
	for(int i=0;i<d.size();++i)
		*p=*p+d[i];
}


int main(){

	vector <int> data(40);
	int accum=0;

	for(int i=0;i<N;++i){
		data.push_back(i);
	}
	sum(&accum,data);
	cout<<"sum is "<<accum<<"\n"<<endl;
return 0;
}


