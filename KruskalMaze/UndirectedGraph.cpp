#include "UndirectedGraph.h"
#include "VectorDereferencer.h"
#include "Node.h"
#include <random>
#include <string>
#include <map>
#include<iostream>

UndirectedGraph::UndirectedGraph(vector<Node *> n) //creates a graph using vector
{
	nodes = n;
}
UndirectedGraph::UndirectedGraph(int a, int b) //creates a rectangular graph
{
	//https://i.imgur.com/meAvvp9.png

	int name = 1;
	vector<vector<Node *>> matrix;
	vector<Node *> nodes_t;
	
	//create only nodes in a vector and matrix
	for (int y = 0; y < b; y++)
	{
		vector<Node *> x_nodes;
		
		for (int x = 0; x < a; x++)
		{
			Node *n = new Node(name);
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
				Node n1 = *matrix[y][x];
				Node n2 = *matrix[y][x - 1];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					(*matrix[y][x]).AddEdge(new Edge(n1.name, n2.name, rnd_weight));
				}
			}

			//create left edge
			if (x < a - 1)
			{
				Node n1 = *matrix[y][x];
				Node n2 = *matrix[y][x + 1];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					(*matrix[y][x]).AddEdge(new Edge(n1.name, n2.name, rnd_weight));
				}
			}
			
			//create edge below
			if (y > 0)
			{
				Node n1 = *matrix[y][x];
				Node n2 = *matrix[y - 1][x];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					(*matrix[y][x]).AddEdge(new Edge(n1.name, n2.name, rnd_weight));
				}
			}

			//create edge above
			if (y < b - 1)
			{
				Node n1 = *matrix[y][x];
				Node n2 = *matrix[y + 1][x];

				if (!n1.Contains(n1, n2))
				{
					int rnd_weight = distr(gen);
					edges_t.push_back(Edge(n1.name, n2.name, rnd_weight));
					(*matrix[y][x]).AddEdge(new Edge(n1.name, n2.name, rnd_weight));
				}
			}
			//cout << "edge count: " << (*matrix[y][x]).GetEdges().size() << endl; 
		}
	}

	//we save our edges both in the matrix and in a vector
	//vector is going to be usefull when calculating the minimum spanning tree
	nodes = nodes_t;
	nodes_matrix = matrix;
}

vector<Edge*> UndirectedGraph::GetEdges()
{

	vector<Edge *> all_edges;
	//cout << "nodes size: " << nodes.size() << endl;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		vector<Edge *> edges = (*nodes[i]).GetEdges();
		//cout << "name: " << (*nodes[i]).name << endl;
		//cout << "edge size: " << edges.size() << endl;

		for (size_t j = 0; j < edges.size(); j++)
		{
			if (!(*edges[j]).IsIn(all_edges))
			{
				all_edges.push_back(edges[j]);
				//cout << "weight: " << (*edges[j]).weight << endl;
			}
		}
	}

	return all_edges;
}

bool UndirectedGraph::HasCircle()
{
	if (nodes.size() < 3)
	{
		return false;
	}

	VectorDereferencer vd = VectorDereferencer();

	vector<Edge> edges = vd.DereferenceVector(GetEdges());
	vector<Edge> edges_visited;

	vector<Edge> current_edges;
	current_edges.push_back(edges[0]);

	vector<Node> nodes_visited;
	vector<Node> current_nodes;

	vector<Node> last_nodes_visited;

	for (int i = 0; i < edges.size(); i++)
	{
		for (int j = 0; j < current_edges.size(); j++)
		{
			
			Edge e = current_edges[j];
			Node start = GetNode(e.start);
			Node end = GetNode(e.end);

			if (VectorContainsEdge(edges_visited, e))
			{
				//cout << "nicedaiosjdaoisjdoiasjdoasijoidas" << endl;
				return true;
			}
			//checks wheter we want to go back where we were
			if (!VectorContainsNode(last_nodes_visited, start))
			{
				if (VectorContainsNode(nodes_visited, start))
				{
					//cout << "bdaisuhdbasik" << endl;
					return true;
				}
				else
				{
					current_nodes.push_back(start);

				}
			}
			if (!VectorContainsNode(last_nodes_visited, end))
			{
				if (VectorContainsNode(nodes_visited, end))
				{
					//cout << "bdaisuhdbasik" << endl;
					return true;
				}
				else
				{
					current_nodes.push_back(end);

				}
			}

			edges_visited.push_back(e);
			//cout << "edge visited start: " << start.name << " end: " << end.name <<
				//" weight: " << e.weight << endl;
		}
		current_edges.clear();
		if (NodeVectorHasCuplicates(current_nodes))
		{
			return true;
		}
		for (int j = 0; j < current_nodes.size(); j++)
		{
			Node n = current_nodes[j];
			nodes_visited.push_back(n);

			for (int k = 0; k < n.GetEdges().size(); k++)
			{
				Edge e = vd.DereferenceVector(n.GetEdges())[k];

				if (!e.IsIn(edges_visited))
				{
					current_edges.push_back(e);
				}
			}
			//cout << "visited node: " << n.name << endl;
		}
		last_nodes_visited = current_nodes;
		current_nodes.clear();
	}
	return false;
}

bool UndirectedGraph::VectorContainsNode(vector<Node> v, Node n)
{
	bool contains = false;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].name == n.name)
		{
			return true;
		}
	}
	return contains;
}

bool UndirectedGraph::VectorContainsEdge(vector<Edge> v, Edge e)
{
	bool contains = false;

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].start == e.start && v[i].end == e.end)
		{
			return true;
		}
		if (v[i].start == e.end && v[i].end == e.start)
		{
			return true;
		}
	}
	return contains;
}

Node UndirectedGraph::GetNode(int n)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->name == n)
		{
			return *nodes[i];
		}
	}
}

bool UndirectedGraph::NodeVectorHasCuplicates(vector<Node> v)
{
	
	vector<Node> vector;

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < vector.size(); j++)
		{
			if (vector[j].name == v[i].name)
			{
				return true;
			}
		}
		vector.push_back(v[i]);
	}
	
	return false;
}

void UndirectedGraph::AddEdgesToNode(vector<Edge> e)
{
	/*
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (e[0])
		{

		}
	}
	*/
}

void UndirectedGraph::PrintMatrixGraph() //prints graph representable by a matrix
{
	for (size_t y = 0; y < nodes_matrix.size(); y++)
	{
		vector<Edge *> edges_t;

		for (size_t x = 0; x < nodes_matrix[0].size(); x++)
		{
			int name = (*nodes_matrix[y][x]).name;
			size_t space_needed = 10;
			cout << "[" << name << "]";
			
			
			if (x < nodes_matrix[0].size() - 1)
			{
				Node n1 = (*nodes_matrix[y][x]);
				Node n2 = (*nodes_matrix[y][x + 1]);
				int weight = (*n1.GetEdge(n1, n2)).weight;

				space_needed -= to_string(weight).length();
				space_needed -= to_string(n1.name).length();

				cout << string(ceil((float)space_needed / 2), ' ');
				cout << weight ;
				cout << string(floor((float)space_needed / 2), ' ');

				
			}
			
		}
		if (y < nodes_matrix.size() - 1)
		{
			for (size_t x = 0; x < nodes_matrix[0].size(); x++)
			{
				Node n1 = *nodes_matrix[y][x];
				Node n2 = *nodes_matrix[y + 1][x];
				edges_t.push_back(n1.GetEdge(n1, n2));
			}
		}
		
		cout << endl << endl;
		int space_needed_weights = 12;

		for (size_t i = 0; i < edges_t.size(); i++)
		{
			int weight_digits = to_string((*edges_t[i]).weight).length();
			cout << (*edges_t[i]).weight << string(space_needed_weights - weight_digits, ' ');
		}
		cout << endl << endl;
	}
}

UndirectedGraph UndirectedGraph::GetMinimalSpanningTree()
{
	vector<Node*> mst_nodes;

	VectorDereferencer vd = VectorDereferencer();
	vector<Edge> edges = vd.DereferenceVector(GetEdges());


	sort(edges.begin(),
		edges.end(),
		[](const Edge& lhs, const Edge& rhs)
		{
			return lhs.weight < rhs.weight;
		});

	for (int i = 0; i < edges.size(); i++)
	{
		cout << "start/end/weight: " << edges[i].start << "/"
			<< edges[i].end << "/" << edges[i].weight << endl;
	}

	return UndirectedGraph(mst_nodes);
}

void UndirectedGraph::TestCases()
{
	cout << "Test cases" << endl;

	//https://imgur.com/a/glwuwGc
	//complex graph small circle

	cout << "complex graph small circle: ";
	Edge* e1 = new Edge(1, 2, 3);
	Edge* e2 = new Edge(2, 3, 10);
	Edge* e3 = new Edge(3, 4, 5);
	Edge* e4 = new Edge(2, 4, 1);
	Edge* e5 = new Edge(4, 5, 4);
	Edge* e6 = new Edge(4, 6, 2);
	Edge* e7 = new Edge(6, 7, 4);

	Node* n1 = new Node(vector<Edge*>{ e1 }, 1);
	Node* n2 = new Node(vector<Edge*>{ e1, e2, e4 }, 2);
	Node* n3 = new Node(vector<Edge*>{ e2, e3}, 3);
	Node* n4 = new Node(vector<Edge*>{ e3, e4, e5, e6 }, 4);
	Node* n5 = new Node(vector<Edge*>{ e5 }, 5);
	Node* n6 = new Node(vector<Edge*>{ e6, e7 }, 6);
	Node* n7 = new Node(vector<Edge*>{ e7,}, 7);

	UndirectedGraph test_graph1 = UndirectedGraph(vector<Node*>{n1, n2, n3, n4, n5, n6, n7});

	if (test_graph1.HasCircle())
	{
		cout << "successful" << endl;
	}
	else
	{
		cout << "failed" << endl;
	}


	//https://imgur.com/a/o3OU8F3
	//complex graph no circle
	cout << "complex graph no circle: ";
	UndirectedGraph test_graph2 = UndirectedGraph(vector<Node*>{n1, n2, n4, n5, n6, n7});
	
	if (test_graph2.HasCircle())
	{
		cout << "failed" << endl;
	}
	else
	{
		cout << "successful" << endl;
	}


	//https://imgur.com/a/Kd6SmtH
	//complex graph big circle
	cout << "complex graph big circle: ";

	Edge* e8 = new Edge(3, 7, 9);
	n3 = new Node(vector<Edge*>{ e2, e8}, 3);
	n7 = new Node(vector<Edge*>{ e7, e8}, 7);
	UndirectedGraph test_graph3 = UndirectedGraph(vector<Node*>{n1, n2, n4, n5, n6, n7});

	if (test_graph3.HasCircle())
	{
		cout << "successful" << endl;
	}
	else
	{
		cout << "failed" << endl;
	}


	//single graph and double graph is the same in code
	cout << "single graph: ";

	n1 = new Node(3);

	UndirectedGraph test_graph4 = UndirectedGraph(vector<Node*>{n1});

	if (test_graph4.HasCircle())
	{
		cout << "failed" << endl;
	}
	else
	{
		cout << "successful" << endl;
	}


	//https://imgur.com/5ufVSSj
	//tri point graph no circle
	cout << "tri point graph no circle: ";

	e1 = new Edge(1, 3, 3);
	e2 = new Edge(2, 3, 8);

	n1 = new Node(vector<Edge*>{ e1 }, 1);
	n2 = new Node(vector<Edge*>{ e2 }, 2);
	n3 = new Node(vector<Edge*>{ e1, e2}, 3);

	UndirectedGraph test_graph5 = UndirectedGraph(vector<Node*>{n1, n2, n3});

	if (test_graph5.HasCircle())
	{
		cout << "failed" << endl;
	}
	else
	{
		cout << "successful" << endl;
	}

	//https://imgur.com/a/gt8lPPR
	//tri point graph has circle
	cout << "tri point graph has circle: ";

	e3 = new Edge(1, 2, 20);

	n1 = new Node(vector<Edge*>{ e1, e3 }, 1);
	n2 = new Node(vector<Edge*>{ e2, e3 }, 2);
	n3 = new Node(vector<Edge*>{ e1, e2}, 3);

	UndirectedGraph test_graph6 = UndirectedGraph(vector<Node*>{n1, n2, n3});

	if (test_graph6.HasCircle())
	{
		cout << "successful" << endl;
	}
	else
	{
		cout << "failed" << endl;
	}

	//https://imgur.com/a/0R5DcS5
	//rectangular graph has circle
	//
	cout << "rectangular graph has circle: ";

	e1 = new Edge(1, 2, 10);
	e2 = new Edge(2, 3, 2);
	e3 = new Edge(3, 4, 3);
	e4 = new Edge(4, 1, 4);

	n1 = new Node(vector<Edge*>{ e1, e4 }, 1);
	n2 = new Node(vector<Edge*>{ e1, e2 }, 2);
	n3 = new Node(vector<Edge*>{ e2, e3 }, 3);
	n4 = new Node(vector<Edge*>{ e3, e4 }, 4);

	UndirectedGraph test_graph7 = UndirectedGraph(vector<Node*>{n1, n2, n3, n4});

	if (test_graph7.HasCircle())
	{
		cout << "successful" << endl;
	}
	else
	{
		cout << "failed" << endl;
	}

	//https://imgur.com/a/7iwfTdm
	//rectangular graph no circle
	//
	cout << "rectangular graph no circle: ";

	n1 = new Node(vector<Edge*>{ e1}, 1);
	n2 = new Node(vector<Edge*>{ e1, e2 }, 2);
	n3 = new Node(vector<Edge*>{ e2, e3 }, 3);
	n4 = new Node(vector<Edge*>{ e3}, 4);

	UndirectedGraph test_graph8 = UndirectedGraph(vector<Node*>{n1, n2, n3, n4});

	if (test_graph8.HasCircle())
	{
		cout << "failed" << endl;
	}
	else
	{
		cout << "successful" << endl;
	}
}