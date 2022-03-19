#pragma once
#include <vector>

using namespace std;

class Edge
{
public:
	//variables
	int start;
	int end;
	int weight;

	//constructor
	Edge(int start, int end, int weight);

	//Functions
	bool IsIn(vector<Edge*> edges);
	bool IsIn(vector<Edge> edges);
	void Print();

	//Getters
	//vector<Node> GetNodes();
};