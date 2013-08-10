#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"
//нет ни одной реализации.
template <typename Vertex_t, typename Edge_t>
class ListRepresentation: public Representation<Vertex_t, Edge_t>
{
public:
	ListRepresentation (){}
	ListRepresentation (int numberOfVertex, bool _oriented){}
	ListRepresentation (int numberOfVertex, int numberOfEdge, bool _oriented){}
	ListRepresentation (ListRepresentation &one){}
	~ListRepresentation (){}

	int vertexCount (){}
	int edgeCount (){}
	bool isDirected (){}
	float getSaturationCoefficent (){}

	Vertex_t* insertVertex (){}
	bool deleteVertex (Vertex_t _vertex1){}
	Edge_t* insertEdge (Vertex_t _vertex1, Vertex_t _vertex2){}
	bool deleteEdge (Vertex_t _vertex1, Vertex_t _vertex2){}
};

#endif // LIST_REPRESENTATION_H
