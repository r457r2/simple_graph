#ifndef REPRESENTATION_H
#define REPRESENTATION_H
#include "QList"

template <typename Vertex_t, typename Edge_t>
class Graph;

template <typename Vertex_t, typename Edge_t>
class Representation
{
protected:
	friend class Graph<Vertex_t, Edge_t>;
	QList<Vertex_t*> vertexes;
	bool directed;

	//Checks if vertex belongs to graph
	bool belongs(Vertex_t *pvertex)
	{
		int index = pvertex->getIndex();
		if(index <= vertexes.count() && vertexes[index] == pvertex)
			return true;
		return false;
	}

	int maxEdgesCount()
	{
		if(directed)
			return vertexes.size() * vertexes.size();
		else
		{
			int retval = 0;
			for(int i = 0; i <= vertexes.size(); i++)
				retval += i;
			return retval;
		}
	}

public:
	Representation (bool _directed) : directed(_directed) {}
	Representation (Representation &other) {}
	virtual ~Representation () {}

	int vertexCount ()
	{
		return this->vertexes.size();
	}

	virtual int edgeCount () = 0;

	bool isDirected ()
	{
		return this->directed;
	}

	float getDensity ()
	{
		return ((float) (2 * edgeCount())) / vertexCount();
	}

	virtual Vertex_t* insertVertex () = 0;
	virtual bool deleteVertex (Vertex_t* _pvertex1) = 0;
	virtual Edge_t* insertEdge (Vertex_t* _pvertex1, Vertex_t* _pvertex2) = 0;
	virtual bool deleteEdge (Vertex_t* _pvertex1, Vertex_t* _pvertex2) = 0;
	virtual Edge_t* getEdge (Vertex_t* _pvertex1, Vertex_t* _pvertex2) = 0;
};

#endif // REPRESENTATION_H
