/*
 * COther.h
 *
 *  Created on: 29 cze 2019
 *      Author: Denis
 */

#ifndef COTHER_H_
#define COTHER_H_

#include "CGraph.h"

#include <vector>	//adjecency list
#include <list>

using namespace std;

class COther: public CGraph {	//name of the class has to be similar to the name of the file
public:
	COther();
	~COther();
	void printAdjList();
	void printMST();
	void enterBegin();
	void calcDistances();
private:
	list<int>* adj_list;
	int minAlg();
	bool* mstCheck;		//true-finished, false-not finished
	int* currVerDistance;			//index-vertex, value- vertices connected to index-vertex
	int* closestEdge;			//index-vertex, value- vertex closest to the index-vertex

};

#endif /* COTHER_H_ */
