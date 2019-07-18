/*
 * graph.h
 *
 *  Created on: 27 cze 2019
 *      Author: Denis
 */

#ifndef CGRAPH_H_
#define CGRAPH_H_

class CGraph
{ 							// singly linked list
	public:
		CGraph();
		~CGraph();
		void PrintGraph();
		int** costGraph;	//graph

	protected:
		inline int ComputeValue();
		inline double ComputeProbability();
		void makeGraph();
		void init();

		int size;
		double density;
};




#endif /* CGRAPH_H_ */
