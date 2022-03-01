#include <iostream>
#include <vector>
#include "KruskalMaze.h"
#include "UndirectedGraph.h"

using namespace std;

int main()
{
	//creates a rectangular undirected graph and prints it
	UndirectedGraph graph_rectangle = UndirectedGraph(4, 5);
	graph_rectangle.PrintMatrixGraph();

	//creates a square like undirected graph and prints it
	UndirectedGraph graph_square = UndirectedGraph(5);
	graph_square.PrintMatrixGraph();
}