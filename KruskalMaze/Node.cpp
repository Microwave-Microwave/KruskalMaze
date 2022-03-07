#include "Node.h"
#include "VectorDereferencer.h"
#include <vector>
#include <iostream>

using namespace std;

Node::Node(vector<Edge*> e, int n)
{
	edges = e;
	name = n;
}

Node::Node(int n)
{
	name = n;
}

vector<Edge*> Node::GetEdges()
{
	return edges;
}

bool Node::IsSet()
{
	if (edges.size() == 0)
		return false;
	else
		return true;
}

bool Node::Contains(Node n1, Node n2)
{
	bool contains = false;
	
	VectorDereferencer vd = VectorDereferencer();
	vector<Edge> cof_edges = vd.DereferenceVector(edges);

	for (int i = 0; i < edges.size(); i++)
	{
		if (cof_edges[i].end == n2.name && cof_edges[i].start == n1.name)
		{
			contains = true;
		}
		if (cof_edges[i].end == n1.name && cof_edges[i].start == n2.name)
		{
			contains = true;
		}
	}

	return contains;
}

Edge* Node::GetEdge(Node n1, Node n2)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if ((*edges[i]).start == n1.name && (*edges[i]).end == n2.name)
		{
			return edges[i];
		}
		if ((*edges[i]).start == n2.name && (*edges[i]).end == n1.name)
		{
			return edges[i];
		}
	}
	cout << endl << "GetEdge() Edge not found" << endl;
	return edges[0];
}

void Node::AddEdge(Edge* e)
{
	edges.push_back(e);
}