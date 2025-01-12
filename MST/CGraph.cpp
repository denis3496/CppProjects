/*
 * graph.cpp
 *
 *  Created on: 27 cze 2019
 *      Author: Denis
 */
#include "CGraph.h"

#include <cstdlib>	//srand
#include <cstdio>	//?

#include <fstream>


using namespace std;

CGraph::CGraph()
{
	size=13;
	density=0.34;
	makeGraph();
	PrintGraph();
}

CGraph::~CGraph(){

}

inline int CGraph::ComputeValue(){
	int Rmax=5, Rmin=1;
	return rand() % (Rmax - Rmin + 1) + Rmin;
}

inline double CGraph::ComputeProbability(){
	return (double)rand()/RAND_MAX;										//from 0 to 1
}

void CGraph::makeGraph(){
		int DiagPos=0;int j=0;
		costGraph= new int*[size];			//create 2d array of bools ON THE HEAP (dynamic)

		for(int i=0;i<size;++i){
			costGraph[i]=new int[size]; 	//new row with size x elements
			costGraph[i][i]=0;
			while(j<DiagPos){
					if(ComputeProbability()>density && i!=j){
						costGraph[j][i]=costGraph[i][j]=ComputeValue(); 	//!!! filling of the graph with values
					}
					else costGraph[j][i]=costGraph[i][j]=0;
					j++;
			}
			DiagPos++;	//every row gets one more column to check (symmetry of array/ optimization)
			j=0;		//SUPER IMPORTANT WHEN NOT USING FOR()
		}
}

void CGraph::PrintGraph(){
		ofstream testGraph;
		int i=0;
		testGraph.open("tGraph.txt");

		testGraph<<"  |";
			while(i<size){
				testGraph<<i<<"|";
				i++;
			}
			testGraph<<endl;
			for(i=0;i<size;++i){
				if(i<10)testGraph<<i<<" |";
				else testGraph<<i<<"|";
				for(int j=0;j<size;++j){
					if(j>10) testGraph<<" ";
					testGraph<<costGraph[i][j]<<" ";
				}
				testGraph<<endl;
			}

		testGraph.close();
}
