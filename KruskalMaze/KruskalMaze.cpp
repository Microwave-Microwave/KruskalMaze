#include <iostream>
#include <vector>
#include "KruskalMaze.h"
#include "UndirectedGraph.h"
#include "Edge.h"

using namespace std;

int main()
{
	// creates a rectangular undirected graph and prints it
	//UndirectedGraph graph_rectangle = UndirectedGraph(14, 9);
	//graph_rectangle.PrintMatrixGraph();

	//creates a square like undirected graph and prints it

	/*Edge e1(1, 2, 3);
	Edge e2(1, 2, 3);
	cout << (e1 == e2) << endl;*/

	UndirectedGraph graph_square = UndirectedGraph(5);
	graph_square.PrintMatrixGraph();
	
	vector<Edge*> edge_test = graph_square.GetEdges();
}