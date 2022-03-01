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
};