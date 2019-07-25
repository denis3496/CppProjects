/*
 * main.cpp
 *
 *  Created on: 25.07.2019
 *      Author: Foerster
 */
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

int main(void)
{
	ifstream data_file("data.txt");
	istream_iterator<int> start(data_file),end;
	vector<int> data(start,end);


	cout<<data.size()<<endl;
	cout<<*start;
	auto sum=0; double avg;

	for(auto i=start;i!=end;i++){
		sum+=*i;//doesnt work as expected

	}

	avg=1.0 * sum/data.size();
	cout<<avg<<endl;

	return 0;
}

