#include "UndirectedGraph.h"
#include "Node.h"
#include <random>
#include <string>
#include<iostream>

UndirectedGraph::UndirectedGraph(int a, int b) //creates a rectangular graph
{
	//https://i.imgur.com/meAvvp9.png

	int name = 1;
	vector<vector<Node>> matrix;
	vector<Node> nodes_t;
	
	//create only nodes in a vector and matrix
	for (int y = 0; y < b; y++)
	{
		vector<Node> x_nodes;
		
		for (int x = 0; x < a; x++)
		{
			Node n = Node(name);
			x_nodes.push_back(n);
			nodes_t.push_back(n);
			name++;
		}
		matrix.push_back(x_nodes);
	}

	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(1, a * b); // define the range

	//assign edges to the nodes using the matrix to navigate
	for (int y = 0; y < b; y++)
	{
		for (int x = 0; x < a; x++)
		{
			vector<Edge> edges_t;

			//create right edge
			if (x > 0)
			{
				Node n1 = matrix[y][x];
				Node n2 = matrix[y][x - 1];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					matrix[y][x].AddEdge(Edge(n1.name, n2.name, rnd_weight));
				}
			}

			//create left edge
			if (x < a - 1)
			{
				Node n1 = matrix[y][x];
				Node n2 = matrix[y][x + 1];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					matrix[y][x].AddEdge(Edge(n1.name, n2.name, rnd_weight));
				}
			}
			

			//create edge below
			if (y > 0)
			{
				Node n1 = matrix[y][x];
				Node n2 = matrix[y - 1][x];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					matrix[y][x].AddEdge(Edge(n1.name, n2.name, rnd_weight));
				}
			}

			//create edge above
			if (y < b - 1)
			{
				Node n1 = matrix[y][x];
				Node n2 = matrix[y + 1][x];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					matrix[y][x].AddEdge(Edge(n1.name, n2.name, rnd_weight));
				}
			}

		}
	}

	//we save our edges both in the matrix and in a vector
	//vector is going to be usefull when calculating the minimum spanning tree
	nodes = nodes_t;
	nodes_matrix = matrix;
}

void UndirectedGraph::PrintMatrixGraph() //prints graph representable by a matrix
{
	for (int y = 0; y < nodes_matrix.size(); y++)
	{
		vector<Edge> edges_t;

		for (int x = 0; x < nodes_matrix[0].size(); x++)
		{
			int name = nodes_matrix[y][x].name;
			int space_needed = 10;
			cout << "[" << name << "]";
			
			
			if (x < nodes_matrix[0].size() - 1)
			{
				Node n1 = nodes_matrix[y][x];
				Node n2 = nodes_matrix[y][x + 1];
				int weight = n1.GetEdge(n1, n2).weight;

				space_needed -= to_string(weight).length();
				space_needed -= to_string(n1.name).length();

				cout << string(ceil((float)space_needed / 2), ' ');
				cout << weight ;
				cout << string(floor((float)space_needed / 2), ' ');

				
			}
			
		}
		if (y < nodes_matrix.size() - 1)
		{
			for (int x = 0; x < nodes_matrix[0].size(); x++)
			{
				Node n1 = nodes_matrix[y][x];
				Node n2 = nodes_matrix[y + 1][x];
				edges_t.push_back(n1.GetEdge(n1, n2));
			}
		}
		
		cout << endl << endl;
		int space_needed_weights = 12;

		for (int i = 0; i < edges_t.size(); i++)
		{
			int weight_digits = to_string(edges_t[i].weight).length();
			cout << edges_t[i].weight << string(space_needed_weights - weight_digits, ' ');
		}
		cout << endl << endl;
	}
}