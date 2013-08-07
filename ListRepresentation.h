#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"
//нет ни одной реализации.
template <typename V, typename E>//vertex,edge
class ListRepresentation: public Representation
{
	public:
		ListRepresentation (){}
		ListRepresentation (int numberOfVertex, bool _oriented){}
		ListRepresentation (int numberOfVertex, int numberOfEge, bool _oriented){}
		ListRepresentation (ListRepresentation &one){}
		~ListRepresentation (){}

		int numberOfVertex (){}
		int numberOfEdge (){}
		bool isDirected (){}
		float getSaturationCoefficent (){}//коэффицент насыщенности
		bool insertVertex (){}
		bool deleteVertex (V _vertex1){}
		bool insertEdge (V _vertex1, V _vertex2){}
		bool deleteEdge (V _vertex1, V _vertex2){}
};

#endif // LIST_REPRESENTATION_H
