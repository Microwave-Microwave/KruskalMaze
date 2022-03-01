#pragma once
#include <vector>
#include "Node.h"

using namespace std;

class UndirectedGraph
{
public:
	//variables
	vector<Node> nodes;
	vector<vector<Node>> nodes_matrix;

	//constructor
	UndirectedGraph(int a, int b); //rectangular graph
	UndirectedGraph(int a) : UndirectedGraph(a, a) {}; //square graph

	//getters
	vector<Node> GetNodes(); //returns node vector

	//setters

	//funtions
	void PrintMatrixGraph(); //prints matrix graph
};