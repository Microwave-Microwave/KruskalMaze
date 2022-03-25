#pragma once
#include <vector>
#include "Node.h"

using namespace std;

class UndirectedGraph
{
public:
	//variables
	vector<Node *> nodes;
	vector<vector<Node *>> nodes_matrix;

	//constructor
	UndirectedGraph(vector<Node *> n);
	UndirectedGraph(vector<Edge*> e);
	UndirectedGraph(vector<Edge> e);
	UndirectedGraph(int a, int b); //rectangular graph
	UndirectedGraph(int a) : UndirectedGraph(a, a) {}; //square graph

	//getters
	vector<Node*> GetNodes(); //returns node vector
	vector<Edge*> GetEdges();
	bool HasCircle();
	bool VectorContainsNode(vector<Node> v, Node n);
	bool VectorContainsNode(vector<Node*> v, Node n);
	bool VectorContainsEdge(vector<Edge> v, Edge e);
	Node GetNode(int n);
	Node* GetNodePointer(int n);
	bool NodeVectorHasCuplicates(vector<Node> v);

	//setters
	void AddEdgesToNode(vector<Edge> e);
	void AddEdgeToNodes(Edge e);

	//funtions

	void PrintMatrixGraph(); //prints matrix graph
	void PrintEdges();
	UndirectedGraph GetMinimalSpanningTreeCaveman();
	UndirectedGraph GetMinimalSpanningTreeCaveman2();
	UndirectedGraph GetMinimalSpanningTreeCaveman3();
	UndirectedGraph GetMinimalSpanningTree();
	UndirectedGraph GetMinimalSpanningTree2();

	bool IsEdgeOf(UndirectedGraph g, Edge e);
	bool IsConnected(Edge* e1, Edge* e2);

	//TestCases
	void TestCases();
};