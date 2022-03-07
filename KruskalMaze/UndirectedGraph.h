#pragma once
#include <vector>
#include "Node.h"

using namespace std;

class UndirectedGraph
{
public:
	//variables
	vector<Node *> nodes;
	vector<vector<Node *>> nodes_matrix;

	//constructor
	UndirectedGraph(vector<Node *> n);
	UndirectedGraph(int a, int b); //rectangular graph
	UndirectedGraph(int a) : UndirectedGraph(a, a) {}; //square graph

	//getters
	vector<Node> GetNodes(); //returns node vector
	vector<Edge*> GetEdges();

	//setters
	void AddEdgesToNode(vector<Edge> e);

	//funtions

	void PrintMatrixGraph(); //prints matrix graph
	UndirectedGraph GetMinimalSpanningTree();
};