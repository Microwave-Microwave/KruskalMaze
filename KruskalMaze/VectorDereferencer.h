#pragma once
#include <vector>
#include "Edge.h"

using namespace std;

class VectorDereferencer
{
public:
	VectorDereferencer();
	vector<Edge> DereferenceVector(vector<Edge*> v);
};