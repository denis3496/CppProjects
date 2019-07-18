/*
 * main.cpp
 *
 *  Created on: 30 kwi 2019
 *      Author: Denis
 *      SPRAWDZONE ZE NA PEWNO DZIALA
 *      W RAZIE CZEGO, ZAMKNAC PROJEKT, OTWORZYC, WYCZYSCIC, ZBUDOWAC
 */
#include <iostream>	//cin,cout

#include <ctime>
//#include <random>

#include <cstdlib>	//srand
#include <cstdio>	//?

#include <vector>	//adjecency list
#include <list>

#include <algorithm> //heap

#include <queue> 	//priority queue

#include <fstream>

using namespace std;

//Monte Carlo uzywamy do losowego wybierania wezlow na etapie
//szukania najkrotszej drogi i sprawdzania ich

class graph{
public:
	graph();
	~graph();
	int VerNum();// returns the number of vertices in the graph
	int EdgNum();// returns the number of edges in the graph
protected:					//SUPER IMPORTANT- ALLOWS TO SHARE IT BY INHERITANCE
	void ComputeEdges();
	double ComputeProbability();
	bool IsGraphConnected();
	void makeGraph();
	void UserInput();
	void PrintMatrix();
	int size;
	double density; 	//0.0-1.0 -->0-100%. Used by ComputeEdges()
	bool** GraphArr;	// base pointer do: array 2D- 1D bool* x 1D bool, size: size x size
};

class PriorityQueue:
		public graph	//using inheritance
{
public:
	PriorityQueue();
	~PriorityQueue();
protected:	////SUPER IMPORTANT- ALLOWS TO SHARE IT BY INHERITANCE
	void AdjacencyList();
	int ComputeValue();
	void SqueezeGraph();
	void PrintArray();
	void PrintGraph();
	void makeGraph();
	int** costArray;	//format: (node x,node y, value) --> size: 3 x size. squeezed array
	int** costGraph;
	int sizeArr;
};


class ShortestPath:
	public PriorityQueue
{
public:
	ShortestPath();
	~ShortestPath();
private:
	void ComputeDijkstraPath();
	void DijkstraSTL();
	void PrintPathSTL();
	void PrintPath();
	int minDistance();
	void UserInput();
	int* ShortestDistanceTo;
	vector<int> ShortestDistanceSTL;
	bool* Set;
	int start;

};

graph::graph(){
	UserInput();
	makeGraph();						//graph array without values
	ComputeEdges();
	while(IsGraphConnected()!=true) ComputeEdges();
	//PrintMatrix();
}

graph::~graph(){
	for(int i=0;i<size;++i){
		delete GraphArr[i];
	}
	delete GraphArr;
	cout<<"dealloc GraphArr"<<endl;
}

PriorityQueue::PriorityQueue():graph(){	//using inheritance between objects
	makeGraph();						//graph array with values
	SqueezeGraph();						//make cost array and COST GRAPH
	PrintArray();
	AdjacencyList();					//optional
	PrintGraph();
}

PriorityQueue::~PriorityQueue(){
	for(int i=0;i<size;++i){
		delete costGraph[i];
		delete costArray[i];
	}
	delete costGraph;
	delete costArray;
	cout<<"dealloc costGraph"<<endl;
}

ShortestPath::ShortestPath():PriorityQueue(){
	UserInput();
	//ComputeDijkstraPath();
	//PrintPath();
	DijkstraSTL();
	PrintPathSTL();
}

ShortestPath::~ShortestPath(){
	delete Set;
	delete ShortestDistanceTo;
	cout<<"dealloc set"<<endl;
}

//Map of program:
//1. Make an graph object
//	+give size
//	+reserve place on the heap (2d array)
//	+make "random" edges (undirected, no loops)
//  +print matrix
//	+check connections
//	+squeeze graph to array of only existing edges
//	+add random values
//  +make array with nodes and values + make graph matrix containing values
//	+print this array and matrix
//	+Dijkstra + further simplifications

void graph::PrintMatrix(){
	int i=0;
	cout<<"  |";
	while(i<size){
		cout<<i<<"|";
		i++;
	}
	cout<<endl;
	for(i=0;i<size;++i){
		if(i<10)cout<<i<<" |";
		else cout<<i<<"|";
		for(int j=0;j<size;++j){
			if(j>10)cout<<" ";
			cout<<(int)GraphArr[i][j]<<" ";
		}
		cout<<endl;
	}
}

void graph::UserInput(){
	cout<<"Size:"<<endl;
	//cin>>size;
	size=13;
	cout<<"Density:"<<endl;
	//cin>>density; 						//like 0.19
	density=0.29;
}

void graph::makeGraph(){
		GraphArr= new bool*[size];		//create 2d array of bools ON THE HEAP (dynamic)
		for(int i=0;i<size;++i){
			GraphArr[i]=new bool[size]; //new row with size x elements
		}
}

inline double graph::ComputeProbability(){
	return (double)rand()/RAND_MAX;										//from 0 to 1
}

void graph::ComputeEdges(){
	for(int i=0;i<size;++i){
		for(int j=0;j<size;++j){
			if(i==j) GraphArr[i][j]=false;										//no connections "edges" na the diagonal (diagonal=loops)
			else{
				GraphArr[i][j]=GraphArr[j][i]=(ComputeProbability()<density);	//symmetrical operation- it means that e.g. if between node 3 and 1 exists edge
			}
		}																		//than between 3 and 1 has to be as well (logical)
	}																			//density- threshold: above- edge exists, below- no edge. The number is random																	//making "density" number higher makes more numbers accepted
}			//SUPER IMPORTANT NOTE: DIAGONAL SYMMETRY= UNDIRECTIONAL EDGES
			//UNDIRECTIONAL= THE COST OF TRAVEL IS THE SAME IN BOTH DIRECTIONS AND IT IS ALWAYS POSSIBLE TO GO BOTH DIRECTIONS

bool graph::IsGraphConnected(){

	int old_size=0,closedSet_size=0;
	bool* close= new bool[size];
	bool* open= new bool[size];

	for(int i=0;i<size;++i)
		open[i]=close[i]=false; 		//init- all is false
	open[0]=true; 						//init- point 0 placed in open set but it could be any other

	//adding to closed set..
	while(closedSet_size<size){
		for(int i=0;i<size;++i){					//take next element
			old_size=closedSet_size;				//init
			if((open[i]==true)&&(close[i]==false)){	//true added for clarity.
													//if element is in open and not in closed
				closedSet_size++; close[i]=true;	//add it to closed set
			}
			//after adding to closed set, leave elements in the open set as they are
			//(they are still connected to the other elements that are in the closed set)
			//and add newly appeared graph nodes that are now connected to the added point
			for(int j=0;j<size;++j)					//algorithm goes one by one from i,0 to i,j
				open[j]= open[j]||GraphArr[i][j]; 	//if open[j] was true- it stays
		}											//SUPER IMPORTANT- matrix has [verses x columns]
			//IF COLUMN numbers (all possible NODES) in the verse have value TRUE,
			//it means that THESE NODES are connected this particular checked NODE (verse number)!

	if(closedSet_size==size) return true;			//jesli graf jest w pelni polaczony
	if (old_size == closedSet_size) return false;	//jesli nic nie jest polaczone
	}	//SUPER IMPORTANT: return states are in the while loop
	delete close;
	delete open;
	return false;
}

inline int PriorityQueue::ComputeValue(){
	int Rmax=5, Rmin=1;
	return rand() % (Rmax - Rmin + 1) + Rmin;
}

void PriorityQueue::makeGraph(){
		costGraph= new int*[size];			//create 2d array of bools ON THE HEAP (dynamic)
		for(int i=0;i<size;++i){
			costGraph[i]=new int[size]; 	//new row with size x elements
		}
}

void PriorityQueue::PrintGraph(){
	int i=0;
	cout<<"  |";
	while(i<size){
		cout<<i<<"|";
		i++;
	}
	cout<<endl;
	for(i=0;i<size;++i){
		if(i<10)cout<<i<<" |";
		else cout<<i<<"|";
		for(int j=0;j<size;++j){
			if(j>10)cout<<" ";
			cout<<costGraph[i][j]<<" ";
		}
		cout<<endl;
	}
}

void PriorityQueue::SqueezeGraph(){
	int DiagPos=0;
	int j=0;
	int newArrIndex=0;
	costArray= new int*[size*size];					//has to store up to whole matrix
	for(int i=0;i<size;++i){
		costGraph[i][i]=0;
		//we are checking only to the diagonal because of symmetry
			while(j<DiagPos){
					if(GraphArr[i][j]==true){
						costArray[newArrIndex]=new int[3];							//see: format
						costArray[newArrIndex][0]=i; costArray[newArrIndex][1]=j; costArray[newArrIndex][2]=ComputeValue();
						costGraph[j][i]=costGraph[i][j]=costArray[newArrIndex][2]; 	//!!! filling of the graph with values
						newArrIndex++;
					}
					else costGraph[j][i]=costGraph[i][j]=0;
					j++;
			}
			DiagPos++;	//every row gets one more column to check (symmetry of array/ optimization)
			j=0;		//SUPER IMPORTANT WHEN NOT USING FOR()
	}
	//cout<<"num of edges:"<<newArrIndex<<endl;
	sizeArr=newArrIndex;
}

void PriorityQueue::PrintArray(){
	for(int i=0;i<sizeArr;++i)
		cout<<i<<".("<<costArray[i][0]<<","<<costArray[i][1]<<","<<costArray[i][2]<<")"<<endl;
}		//i+1 is local

void PriorityQueue::AdjacencyList(){
	int i;
	vector< list< pair <int, int> > > adjacencyList(sizeArr);	//the only usage of vector in program

	for(i=0;i<sizeArr;++i){									//adjecencyList[vertex].addConnectedVertex(pairof(vertex,value))
		adjacencyList[costArray[i][0]].push_back(make_pair(costArray[i][1],costArray[i][2]));
	}
	 printf("\nThe Adjacency List-\n");
	 // Printing Adjacency List...
	 for (i = 0; i <adjacencyList.size(); ++i) {
				cout<<i;
				//adjacencyList[i]-contains a single row of connections
				list< pair<int, int> >::iterator listRowBegin = adjacencyList[i].begin();	//begin-sets the node i as a first node in connection
				//SUPER IMPORTANT: IF WE WANT TO LOOK INSIDE A VECTOR LIST WE HAVE TO INITIALISE A LIST
				while (listRowBegin != adjacencyList[i].end()) {							//end of connected nodes
					cout<<"->"<<(*listRowBegin).first<<"("<<(*listRowBegin).second<<")";	// node- first, value-second
					++listRowBegin;
				}
				cout<<endl;
	    }
}

int ShortestPath::minDistance(){
	int minDist=99999; int minDistIndex;
	bool open=false;

	for(int i=0;i<size;++i){
		if(Set[i]==open && ShortestDistanceTo[i]<minDist)
			minDist=ShortestDistanceTo[i], minDistIndex=i;
	}
	return minDistIndex;
}

void ShortestPath::UserInput(){
	cout<<"Start:"<<endl;
	cin>>start;
//	start=3;
}

void ShortestPath::PrintPath(){
	cout<<"Path start:"<<start<<endl;
	for(int i=0;i<size;++i)
		cout<<"To:"<<i<<" Distance:"<<ShortestDistanceTo[i]<<endl;
}


void ShortestPath::ComputeDijkstraPath(){
		ShortestDistanceTo = new int[size];
		//both sets included in the below set by true/false values
		bool open=false; bool closed=true;
		Set= new bool[size];
		cout<<"Dijkstra algorithm v1 begins.."<<endl;
		//initialization below..
		for(int i=0;i<size;++i)
		{										//if the node has any connections
				 ShortestDistanceTo[i]=99999;	//"infinity"- we need to minimize this value for every point
				 Set[i]=false;					//everything starts in open set
				//should contain all non-repeating nodes between which connection exists WITH OUT STARTING POINT
		}

		ShortestDistanceTo[start]=0; 	//distance from start to start

		for(int i=0;i<size-1;i++){
			int v_1=minDistance(); 		//source
			Set[v_1]=closed;

			for(int v_2=0;v_2<size;++v_2){
						if(Set[v_2]==open && costGraph[v_1][v_2] && ShortestDistanceTo[v_1]!=99999 &&
									ShortestDistanceTo[v_1]+costGraph[v_1][v_2]<ShortestDistanceTo[v_2])
								ShortestDistanceTo[v_2]=ShortestDistanceTo[v_1]+costGraph[v_1][v_2];
						}
			}
}

inline void ShortestPath::PrintPathSTL(){
	cout<<"Path start:"<<start<<endl;
			for(int i=0;i<size;++i)
				cout<<"To:"<<i<<" Distance:"<<ShortestDistanceSTL[i]<<endl;
}

void ShortestPath::DijkstraSTL(){								//it uses exactly the same procedures as by defining adjacency list
	ShortestDistanceSTL= vector<int>(sizeArr,9999);			//sizeArr !!!! size of costArr
	// iPair ==>  Integer Pair
	typedef pair<int, int> Pair;
	priority_queue<Pair, vector<Pair>,greater<Pair>> priorityQueue;	//see: typedef Pair
																	//"greater" is crucial
	priorityQueue.push(make_pair(0,start)); 	//create pair of integers where first is a distance and second is destination
	ShortestDistanceSTL[start]=0;				//the same in both functions

	while(!priorityQueue.empty()){
		int v_1=priorityQueue.top().second;			//element of queue type where top is the first element on the heap of type pair of integer: second element in pair: destination
		priorityQueue.pop();						//erase top element from heap
		list<pair<int,int>> *ListArr;				//create a pointer to a list of pairs of ints
		ListArr = new list<Pair>[size];				//allocate memory for this list

		for(int j=0;j<sizeArr;++j){																//sizeArr!! size of costArr
			ListArr[costArray[j][0]].push_back(make_pair(costArray[j][1],costArray[j][2]));
			ListArr[costArray[j][1]].push_back(make_pair(costArray[j][0],costArray[j][2]));		//this line is not in adjacency list generation procedure
		}
		cout<<"adding to the list"<<endl;
		list<pair<int,int>>::iterator i; 										//iterator is a given object in class list
		for(i=ListArr[v_1].begin();i!=ListArr[v_1].end();++i){					//here begins real Dijkstra
				int v_2 = (*i).first;											//take next destination from the heap
				int distance=(*i).second;										//take its value
				if(ShortestDistanceSTL[v_2]>ShortestDistanceSTL[v_1]+distance)	//if the previously saved distance to the next destination is bigger than the actual one than override
				{
					ShortestDistanceSTL[v_2]=ShortestDistanceSTL[v_1]+distance;
					priorityQueue.push(make_pair(ShortestDistanceSTL[v_2],v_2));
				}
		}
		delete ListArr;
	}

}

int main(){
	srand(time(0)); 					//seed rand()- generator start point
	ShortestPath a;
	return 0;
}
