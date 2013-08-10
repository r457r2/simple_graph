#ifndef MATRIX_REPRESENTATION_H
#define MATRIX_REPRESENTATION_H
#include "Representation.h"
//нет ни одной реализации.
template <typename Vertex_t, typename Edge_t>
class MatrixRepresentation: public Representation
{
public:
	MatrixRepresentation (){}
	MatrixRepresentation (int numberOfVertex, bool _oriented){}
	MatrixRepresentation (int numberOfVertex, int numberOfEge, bool _oriented){}
	MatrixRepresentation (MatrixRepresentation &one){}
	~MatrixRepresentation (){}

	int vertexCount (){}
	int edgeCount (){}
	bool isDirected (){}
	float getSaturationCoefficent (){}

	Vertex_t insertVertex (){}
	bool deleteVertex (Vertex_t _vertex1){}
	Edge_t insertEdge (Vertex_t _vertex1, Vertex_t _vertex2){}
	bool deleteEdge (Vertex_t _vertex1, Vertex_t _vertex2){}
};

#endif // MATRIX_REPRESENTATION_H
