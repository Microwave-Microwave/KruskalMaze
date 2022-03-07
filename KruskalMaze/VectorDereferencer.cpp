#include "VectorDereferencer.h"
#include <vector>
#include "Edge.h"

using namespace std;

VectorDereferencer::VectorDereferencer()
{

}

vector<Edge> VectorDereferencer::DereferenceVector(vector<Edge*> v)
{
	vector<Edge> vector;

	for (int i = 0; i < v.size(); i++)
	{
		Edge e = *v[i];
		vector.push_back(e);
	}
	
	return vector;
}