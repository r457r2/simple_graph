#ifndef MATRIX_REPRESENTATION_H
#define MATRIX_REPRESENTATION_H
#include "Representation.h"
//��� �� ����� ����������.
template <typename V, typename E>//vertex,edge
class MatrixRepresentation: public Representation
{
	public:
		MatrixRepresentation (){}
		MatrixRepresentation (int numberOfVertex, bool _oriented){}
		MatrixRepresentation (int numberOfVertex, int numberOfEge, bool _oriented){}
		MatrixRepresentation (MatrixRepresentation &one){}
		~MatrixRepresentation (){}

		int numberOfVertex (){}
		int numberOfEdge (){}
		bool isDirected (){}
		float getSaturationCoefficent (){}//���������� ������������
		bool insertVertex (){}
		bool deleteVertex (V _vertex1){}
		bool insertEdge (V _vertex1, V _vertex2){}
		bool deleteEdge (V _vertex1, V _vertex2){}
};

#endif // MATRIX_REPRESENTATION_H
