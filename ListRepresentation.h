#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"
//нет ни одной реализации.
template <typename Vertex_t, typename Edge_t>
class ListRepresentation: public Representation
{
	public:
		ListRepresentation (){}
		ListRepresentation (int numberOfVertex, bool _oriented){}
        ListRepresentation (int numberOfVertex, int numberOfEdge, bool _oriented){}
		ListRepresentation (ListRepresentation &one){}
		~ListRepresentation (){}

		int numberOfVertex (){}
		int numberOfEdge (){}
		bool isDirected (){}
		float getSaturationCoefficent (){}//коэффицент насыщенности
		bool insertVertex (){}
        bool deleteVertex (Vertex_t _vertex1){}
        bool insertEdge (Vertex_t _vertex1, Vertex_t _vertex2){}
        bool deleteEdge (Vertex_t _vertex1, Vertex_t _vertex2){}
};

#endif // LIST_REPRESENTATION_H
