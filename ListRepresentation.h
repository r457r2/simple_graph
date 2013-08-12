#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"
//
template <typename Vertex_t, typename Edge_t>
class ListRepresentation: public Representation<Vertex_t, Edge_t>
{
private:
	QList<QList<Edge_t*> > repr;

public:
	ListRepresentation (){}
	ListRepresentation (int numberOfVertex, bool _oriented){}
	ListRepresentation (int numberOfVertex, int numberOfEdge, bool _oriented){}
	ListRepresentation (ListRepresentation &one){}
	~ListRepresentation (){}

	int vertexCount ()
	{return this->vectorOfVertex.size();}

	int edgeCount ()
	{
		int count = 0;
		for (int i = 0; i < this->vectorOfVertex.size(); i++)
		{
			count += repr[i].size();
		}
		return count;
	}

	bool isDirected (){return this->oriented;}

	float getSaturationCoefficent (){}

	Vertex_t* insertVertex ()
	{
		this->vectorOfVertex.append(new Vertex_t());
		this->vectorOfVertex.last()->setIndex(this->vectorOfVertex.size() - 1);
	}
	bool deleteVertex (Vertex_t* _vertex1)
	{
		int pos = this->vectorOfVertex.indexOf(_vertex1);

		if (pos == -1)
			return false;

		this->vectorOfVertex.removeOne(_vertex1);

		for (; pos < this->vectorOfVertex.size(); pos++)
		{
			this->vectorOfVertex[pos]->setIndex(pos);
		}
		return true;
	}

	Edge_t* insertEdge (Vertex_t* _vertex1, Vertex_t* _vertex2)
	{
		if (((this->vectorOfVertex.contains(_vertex1)) && (this->vectorOfVertex.contains(_vertex2))) == true)
			return NULL;

		for (int i = 0; i < repr[_vertex1->getIndex()].size(); i++)
		{
			if (repr[_vertex1->getIndex()][i]->isComingFrom(_vertex2) == true)
				return NULL;
		}

		repr[_vertex1->getIndex()].append(new Edge_t(_vertex1, _vertex2));
		return repr[_vertex1->getIndex()].last();
	}

	bool deleteEdge (Vertex_t* _vertex1, Vertex_t* _vertex2)
	{
		if (this->vectorOfVertex.contains(_vertex1) == true)
			return false;
		for (int i = 0; i < repr[_vertex1->getIndex()].size(); i++)
		{
			if (repr[_vertex1->getIndex()][i]->isComingFrom(_vertex2) == true)
			{
				repr[_vertex1->getIndex()].removeAt(i);
				return true;
			}
		}
		return NULL;
	}
};

#endif // LIST_REPRESENTATION_H
