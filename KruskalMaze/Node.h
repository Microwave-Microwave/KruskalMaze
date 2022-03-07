#pragma once
#include "Edge.h"
#include <vector>

using namespace std;

class Node
{
public:
	//variables
	int name;
	vector<Edge*> edges;

	//constructor
	Node(vector<Edge*> e, int n);
	Node(int n);

	//getters
	vector<Edge*> GetEdges();
	bool IsSet();
	bool Contains(Node n1, Node n2); //checks whether has an edge that connects n1 and n2
	Edge* GetEdge(Node n1, Node n2); //returns edge connected to n1 and n2

	//setters
	void AddEdge(Edge* e);
};