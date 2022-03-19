#include "UndirectedGraph.h"
#include "VectorDereferencer.h"
#include "Node.h"
#include <random>
#include <string>
#include <map>
#include<iostream>

UndirectedGraph::UndirectedGraph(vector<Node *> n) //creates a graph using node vector
{
	nodes = n;
}

UndirectedGraph::UndirectedGraph(vector<Edge*> e) //creates a graph using edge pointer vector
{
	//cout << "\nvector size: " << e.size() << "\n";
	//cout << "edges size : " << GetEdges().size() << "\n";
	for (int i = 0; i < e.size(); i++)
	{
		Node start_node = Node((*e[i]).start);
		Node end_node = Node((*e[i]).end);
		//cout << "start node: " << start_node.name << " end node: " << end_node.name << "\n";
		if (!VectorContainsNode(nodes, start_node))
		{
			nodes.push_back(new Node((*e[i]).start));
			
		}
		GetNodePointer(start_node.name)->AddEdge(e[i]);

		if (!VectorContainsNode(nodes, end_node))
		{
			nodes.push_back(new Node((*e[i]).end));
			
		}
		GetNodePointer(end_node.name)->AddEdge(e[i]);
		//cout << "nodes list size: " << nodes.size() << "\n";
	}
	//cout << "edges size : " << GetEdges().size() << "\n";
}

UndirectedGraph::UndirectedGraph(vector<Edge> e_t) //creates a graph using edge vector
{
	//cout << "edges size : " << GetEdges().size() << "\n";

	vector<Edge*> e;
	for (int i = 0; i < e_t.size(); i++)
	{
		e.push_back(&e_t[i]);
	}
	cout << "\nvector size: " << e.size() << "\n";


	for (int i = 0; i < e.size(); i++)
	{
		Node start_node = Node((*e[i]).start);
		Node end_node = Node((*e[i]).end);
		//cout << "start node: " << start_node.name << " end node: " << end_node.name << "\n";
		if (!VectorContainsNode(nodes, start_node))
		{
			nodes.push_back(new Node((*e[i]).start));
		}
		GetNodePointer(start_node.name)->AddEdge(e[i]);

		if (!VectorContainsNode(nodes, end_node))
		{
			nodes.push_back(new Node((*e[i]).end));
		}
		GetNodePointer(end_node.name)->AddEdge(e[i]);
		cout << "IMPORTANT WEIGHT1: " << e[i]->weight << "\n";
		cout << "IMPORTANT WEIGHT2: " << GetNodePointer(end_node.name)->GetEdges()[0]->weight << "\n";

		//e[i]->Print();
		//cout << "nodes list size: " << nodes.size() << "\n";

	}
	cout << "edges size nice88 : " << GetEdges().size() << "\n";
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
			//cout << "edge count: " << (*matrix[y][x]).GetEdges().size() << "\n"; 
		}
	}

	//we save our edges both in the matrix and in a vector
	//vector is going to be usefull when calculating the minimum spanning tree
	nodes = nodes_t;
	nodes_matrix = matrix;
}

vector<Node*> UndirectedGraph::GetNodes()
{
	return nodes;
}

vector<Edge*> UndirectedGraph::GetEdges()
{
	vector<Edge*> all_edges;
	cout << "nodes size GetEdges(): " << nodes.size() << "\n";
	for (size_t i = 0; i < nodes.size(); i++)
	{
		vector<Edge*> edges = (*nodes[i]).GetEdges();
		//cout << "name: " << (*nodes[i]).name << "\n";
		//cout << "edge size: " << edges.size() << "\n";

		for (size_t j = 0; j < edges.size(); j++)
		{
			if (!(*edges[j]).IsIn(all_edges))
			{
				cout << "not in\n";
				all_edges.push_back(edges[j]);
				//cout << "weight: " << (*edges[j]).weight << "\n";
				//(*edges[j]).Print();
			}
		}
	}
	cout << "all edges 555: " << all_edges.size() << "\n";
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
				//cout << "nicedaiosjdaoisjdoiasjdoasijoidas\n";
				return true;
			}
			//checks wheter we want to go back where we were
			if (!VectorContainsNode(last_nodes_visited, start))
			{
				if (VectorContainsNode(nodes_visited, start))
				{
					//cout << "bdaisuhdbasik\n";
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
					//cout << "bdaisuhdbasik\n";
					return true;
				}
				else
				{
					current_nodes.push_back(end);

				}
			}

			edges_visited.push_back(e);
			//cout << "edge visited start: " << start.name << " end: " << end.name <<
				//" weight: " << e.weight << "\n";
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
			//cout << "visited node: " << n.name << "\n";
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

bool UndirectedGraph::VectorContainsNode(vector<Node*> v, Node n)
{
	bool contains = false;
	if (v.size() < 1)
	{
		return false;
	}
	for (int i = 0; i < v.size(); i++)
	{
		if ((*v[i]).name == n.name)
		{
			//cout << "vector size: " << v.size() << "\n";
			for (int j = 0; j < v.size(); j++)
			{
				//cout << "nodes in vector: " << v[j]->name << "\n";
			}
			//cout << n.name << " is in vector\n";
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

Node* UndirectedGraph::GetNodePointer(int n)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->name == n)
		{
			return nodes[i];
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

void UndirectedGraph::AddEdgeToNodes(Edge e)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if ((*nodes[i]).name == e.start || (*nodes[i]).name == e.end)
		{
			(*nodes[i]).edges.push_back(&e);
		}
	}
}

void UndirectedGraph::PrintMatrixGraph() //prints graph representable by a matrix
{
	cout << "\n";
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
		
		cout << "\n" << "\n";
		int space_needed_weights = 12;

		for (size_t i = 0; i < edges_t.size(); i++)
		{
			int weight_digits = to_string((*edges_t[i]).weight).length();
			cout << (*edges_t[i]).weight << string(space_needed_weights - weight_digits, ' ');
		}
		cout << "\n" << "\n";
	}
}

void UndirectedGraph::PrintEdges()
{
	cout << "edges count: " << GetEdges().size() << "\n";
	for (int i = 0; i < GetEdges().size(); i++)
	{
		GetEdges()[i]->Print();
		//cout << "start/end/weight" << GetEdges()[i]->start << GetEdges()[i]->end
			//<< GetEdges()[i]->weight << "\n";
	}
}

UndirectedGraph UndirectedGraph::GetMinimalSpanningTree2()
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
	cout << "EDGES\n";

	for (int i = 0; i < edges.size(); i++)
	{
		edges[i].Print();
	}

	cout << "\n";

	vector<UndirectedGraph> graphs;

	vector<Edge*> edge_collection;
	for (int i = 0; i < edges.size(); i++)
	{
		edge_collection.push_back(&edges[i]);
	}
	//cout << "collection size: " << edge_collection.size() << "\n";

	

	cout << "edges vector size44: " << edges.size() << "\n";

	cout << "----------------\n";
	cout << "mst creation\n";
	cout << "----------------\n";
	UndirectedGraph mst = UndirectedGraph(edges);
	cout << "----------------\n";
	cout << "mst creation done\n";
	cout << "----------------\n";

	//edge already is wrong...
	cout << "weight: " << (*mst.GetNodes()[0]).GetEdges()[0]->weight << "\n";

	cout << "node size: " << mst.GetNodes().size() << "\n";
	cout << "node1 edges size: " << mst.GetNodes()[0]->GetEdges().size() << "\n";
	cout << "pls work size: " << mst.GetEdges().size() << "\n";

	cout << "----------------\n";
	cout << "many edges print\n";
	cout << "----------------\n";


	for (int i = 0; i < mst.GetNodes().size(); i++)
	{
		cout << "weight pls work: " << mst.GetNodePointer(i + 1)->GetEdges()[0]->weight << "\n";
	}


	int node_size = mst.GetNodes().size();
	for (int i = 0; i < node_size; i++)
	{
		int edges_size = (*mst.GetNodes()[i]).GetEdges().size();
		cout << "/////name of node:" << (*mst.GetNodes()[i]).name << "\n";
		cout << "edges size: " << edges_size << "\n";
		for (int j = 0; j < edges_size; j++)
		{
			(*mst.GetNodes()[i]).GetEdges()[j]->Print();
			cout << "weight: " << (*mst.GetNodes()[i]).GetEdges()[j]->weight << "\n";
		}
	}

	return mst;
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
	

	vector<UndirectedGraph> graphs;

	for (int i = 0; i < edges.size(); i++)
	{
		//edges[i].Print();
		bool edge_dealth_with = false;

		for (int j = 0; j < graphs.size(); j++)
		{
			//cout << "graph cout: " << graphs[j].GetEdges().size() << "\n";
			if (IsEdgeOf(graphs[j], edges[i]))
			{
				cout << "finally\n";
				UndirectedGraph ug_t = graphs[j];
				ug_t.AddEdgeToNodes(edges[i]);
				if (!ug_t.HasCircle())
				{
					graphs[j].AddEdgeToNodes(edges[i]);
					//cout << "oooo\n";
					edges[i].Print();
				}
			}
		}

		if (edge_dealth_with == false)
		{
			vector<Edge*> edge_v;
			edge_v.push_back(&edges[i]);

			Node n1 = Node(edge_v, edges[i].start);
			Node n2 = Node(edge_v, edges[i].end);

			vector<Node*> n_t;
			n_t.push_back(&n1);
			n_t.push_back(&n2);

			UndirectedGraph ug_t = UndirectedGraph(n_t);
			graphs.push_back(ug_t);
			cout << "added single one " << ug_t.GetEdges().size() << "\n";
		}
	}

	return UndirectedGraph(mst_nodes);
}

bool UndirectedGraph::IsEdgeOf(UndirectedGraph g, Edge e)
{
	//cout << "nice\n";
	vector<Edge *> edges_t = g.GetEdges();

	for (int i = 0; i < edges_t.size(); i++)
	{
		e.Print();
		(*edges_t[i]).Print();
		if ((*edges_t[i]).start == e.start || (*edges_t[i]).start == e.end)
		{
			return true;
		}
		if ((*edges_t[i]).end == e.start || (*edges_t[i]).end == e.end)
		{
			return true;
		}
	}
	return false;
}

void UndirectedGraph::TestCases()
{
	cout << "\n" << "Test cases\n";
	cout << "------------------------------\n";


	//
	//https://imgur.com/a/glwuwGc
	//complex graph small circle
	//

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
		cout << "successful\n";
	}
	else
	{
		cout << "failed\n";
	}

	//
	//https://imgur.com/a/o3OU8F3
	//complex graph no circle
	//
	cout << "complex graph no circle: ";
	UndirectedGraph test_graph2 = UndirectedGraph(vector<Node*>{n1, n2, n4, n5, n6, n7});
	
	if (test_graph2.HasCircle())
	{
		cout << "failed\n";
	}
	else
	{
		cout << "successful\n";
	}

	//
	//https://imgur.com/a/Kd6SmtH
	//complex graph big circle
	//
	cout << "complex graph big circle: ";

	Edge* e8 = new Edge(3, 7, 9);
	n3 = new Node(vector<Edge*>{ e2, e8}, 3);
	n7 = new Node(vector<Edge*>{ e7, e8}, 7);
	UndirectedGraph test_graph3 = UndirectedGraph(vector<Node*>{n1, n2, n4, n5, n6, n7});

	if (test_graph3.HasCircle())
	{
		cout << "successful\n";
	}
	else
	{
		cout << "failed\n";
	}

	//
	//single graph and double graph is the same in code
	//
	cout << "single graph: ";

	n1 = new Node(3);

	UndirectedGraph test_graph4 = UndirectedGraph(vector<Node*>{n1});

	if (test_graph4.HasCircle())
	{
		cout << "failed\n";
	}
	else
	{
		cout << "successful\n";
	}

	//
	//https://imgur.com/5ufVSSj
	//tri point graph no circle
	//
	cout << "tri point graph no circle: ";

	e1 = new Edge(1, 3, 3);
	e2 = new Edge(2, 3, 8);

	n1 = new Node(vector<Edge*>{ e1 }, 1);
	n2 = new Node(vector<Edge*>{ e2 }, 2);
	n3 = new Node(vector<Edge*>{ e1, e2}, 3);

	UndirectedGraph test_graph5 = UndirectedGraph(vector<Node*>{n1, n2, n3});

	if (test_graph5.HasCircle())
	{
		cout << "failed\n";
	}
	else
	{
		cout << "successful\n";
	}

	//
	//https://imgur.com/a/gt8lPPR
	//tri point graph has circle
	//
	cout << "tri point graph has circle: ";

	e3 = new Edge(1, 2, 20);

	n1 = new Node(vector<Edge*>{ e1, e3 }, 1);
	n2 = new Node(vector<Edge*>{ e2, e3 }, 2);
	n3 = new Node(vector<Edge*>{ e1, e2}, 3);

	UndirectedGraph test_graph6 = UndirectedGraph(vector<Node*>{n1, n2, n3});

	if (test_graph6.HasCircle())
	{
		cout << "successful\n";
	}
	else
	{
		cout << "failed\n";
	}

	//
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
		cout << "successful\n";
	}
	else
	{
		cout << "failed\n";
	}

	//
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
		cout << "failed\n";
	else
		cout << "successful\n";


	//
	//https://imgur.com/a/glwuwGc
	//Test Edge Graph Creation
	//
	cout << "Test Edge Graph Creation: ";

	e1 = new Edge(1, 2, 3);
	e2 = new Edge(2, 3, 10);
	e3 = new Edge(3, 4, 5);
	e4 = new Edge(2, 4, 1);
	e5 = new Edge(4, 5, 4);
	e6 = new Edge(4, 6, 2);
	e7 = new Edge(6, 7, 4);

	n1 = new Node(vector<Edge*>{ e1 }, 1);
	n2 = new Node(vector<Edge*>{ e1, e2, e4 }, 2);
	n3 = new Node(vector<Edge*>{ e2, e3}, 3);
	n4 = new Node(vector<Edge*>{ e3, e4, e5, e6 }, 4);
	n5 = new Node(vector<Edge*>{ e5 }, 5);
	n6 = new Node(vector<Edge*>{ e6, e7 }, 6);
	n7 = new Node(vector<Edge*>{ e7, }, 7);

	UndirectedGraph test = UndirectedGraph(vector<Edge*>{e1, e2, e3, e4, e5, e6, e7});

	if (test.GetEdges().size() == 7)
	{
		cout << "successful\n";
	}
	else
	{
		cout << "failed\n\n";
		cout << "Edge count should be 7.\n";
		test.PrintEdges();
	}


	//
	//Rectangular matrix graph convert to vector graph
	//

	cout << "Rectangular matrix graph convert to vector graph: ";

	UndirectedGraph graph_rectangular = UndirectedGraph(2, 3);
	UndirectedGraph graph_vector = UndirectedGraph(graph_rectangular.GetEdges());

	bool graph_conversion_good = true;

	if (graph_vector.GetEdges().size() != graph_vector.GetEdges().size())
	{
		graph_conversion_good = false;
	}
	
	//graph_rectangular.PrintMatrixGraph();
	//graph_vector.PrintEdges();

	if (graph_conversion_good)
		cout << "successful (same amount of edges)\n";
	else
		cout << "failed\n";

}