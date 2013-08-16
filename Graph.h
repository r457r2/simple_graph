#ifndef GRAPH_H
#define GRAPH_H
#include "Representation.h"
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"
//в этом классе реализованы все методы, кроме преобразований.

enum ReprType
{
	LIST_REPR = 0,
	MATRIX_REPR
};

template <typename Vertex_t, typename Edge_t>
class Graph
{
private:
	ReprType type;
	Representation<Vertex_t, Edge_t>* graph;

public:

	Graph () : type(LIST_REPR) // empty L-graph
	{
		graph = new ListRepresentation<Vertex_t, Edge_t>();
	}

	Graph (int numberOfVertex, bool _oriented, ReprType t) : type(t) // without edge
	{
		if (type == MATRIX_REPR)
			graph = new MatrixRepresentation<Vertex_t, Edge_t>(numberOfVertex, _oriented);
		else
			graph = new ListRepresentation<Vertex_t, Edge_t>(numberOfVertex, _oriented);
	}

	Graph (int numberOfVertex, int numberOfEdge, bool _oriented, ReprType t) : type(t)//full
	{
		if (type == MATRIX_REPR)
			graph = new MatrixRepresentation<Vertex_t, Edge_t>(numberOfVertex, numberOfEdge, _oriented);
		else
			graph = new ListRepresentation<Vertex_t, Edge_t>(numberOfVertex, numberOfEdge, _oriented);
	}

	Graph (Graph &one)
	{
		if (one.type == MATRIX_REPR) graph = new MatrixRepresentation<Vertex_t, Edge_t>(one);
		else graph = new ListRepresentation<Vertex_t, Edge_t>(one);
	}

	~Graph ()
	{
		delete graph;
	}

	int vertexCount (){return graph->vertexCount();}
	int edgeCount (){return graph->edgeCount();}
	bool isDirected (){return graph->isDirected();}
	ReprType getType(){return type;}

	float getSaturationCoefficent (){return graph->getSaturationCoefficent();}//коэффицент насыщенности
	bool toListGraph (){return false;}//запилить преобразование!!!
	bool toMatrixGraph (){return false;}//запилить преобразование!!!
	Vertex_t* insertVertex (){return graph->insertVertex();}
	bool deleteVertex (Vertex_t _vertex1){return graph->deleteVertex(_vertex1);}
	Edge_t* insertEdge (Vertex_t _vertex1, Vertex_t _vertex2){return graph->insertEdge(_vertex1, _vertex2);}
	bool deleteEdge (Vertex_t _vertex1, Vertex_t _vertex2){return graph->deleteEdge(_vertex1, _vertex2);}
};

#endif // GRAPH_H
