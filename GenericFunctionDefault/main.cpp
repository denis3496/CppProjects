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

template <class T> T sum(const T tab[],int quan,T sum=0){
	for(int i=0;i<quan;++i)
		sum+=tab[i];
	return sum;
}


int main(){
	cout<<"template for sum()"<<endl;
	int a[]={1,2,3};
	double b[]={2.1,2.2,2.3};
	cout<<sum(a,3,6)<<endl;
	cout<<sum(b,3,6.5)<<endl;
	return 0;
}


