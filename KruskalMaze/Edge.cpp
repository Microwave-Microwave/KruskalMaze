#include "Edge.h"
#include "VectorDereferencer.h"
#include <vector>
#include <iostream>

using namespace std;

Edge::Edge(int s, int e, int w)
{
	start = s;
	end = e;
	weight = w;
}

bool Edge::IsIn(vector<Edge *> edges)
{
	VectorDereferencer vd = VectorDereferencer();
	vector<Edge> cof_edges = vd.DereferenceVector(edges);

	bool is_in = false;

	for (size_t i = 0; i < edges.size(); i++)
	{

		if (cof_edges[i].start == start && cof_edges[i].end == end)
		{ 
			is_in = true;
		}
		if (cof_edges[i].end == start && cof_edges[i].start == end)
		{
			is_in = true;

		}
	}

	return is_in;
}

bool Edge::IsIn(vector<Edge> edges)
{
	vector<Edge> cof_edges = edges;

	bool is_in = false;

	for (size_t i = 0; i < edges.size(); i++)
	{

		if (cof_edges[i].start == start && cof_edges[i].end == end)
		{
			is_in = true;
		}
		if (cof_edges[i].end == start && cof_edges[i].start == end)
		{
			is_in = true;

		}
	}

	return is_in;
}