/*
 * main.cpp
 *
 *  Created on: 26.07.2019
 *      Author: Foerster
 */
/*
 * main.c
 *
 *  Created on: 25.07.2019
 *      Author: Foerster
 */

#include <iostream>
#include <algorithm>		//quick sort algorithm
#include <vector>
#include <fstream>
#include <iterator>
#include <functional> //for wrapper


using namespace std;

int main(void){
	ifstream data_file("word.txt");

	istream_iterator<string> start(data_file), end;
	vector<string> words(start, end);

	sort(words.begin(),words.end());

	// for each string in the vector
	  for (unsigned n=0;n<words.size();n++)	//we analyze every string. we should use auto to make use of STL and vector
	    {									//BUT when auto is used, error occurs
	    // convert the string to lowercase
	    transform(
	    	words[n].begin(),				//we get the value out of the container
			words[n].end(),
			words[n].begin(),				//saving point
			 [](auto a) {return tolower(a);}//tolower doesnt work on the whole string.
	      );					//wrapper <Argument type,Result type> (pointer to a function to create a wrapper for whole string)-&function
	    }
	ofstream data_out("sorted.txt"); 	// opens up the file too

	for(auto str:words)					//str means every string in vector
		data_out<<str<<" ";				//

	data_out.close();
	data_file.close();
	return 0;
}







