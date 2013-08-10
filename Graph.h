#ifndef GRAPH_H
#define GRAPH_H
#include "Representation.h"
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"
//в этом классе реализованы все методы, кроме преобразований.
template <typename V, typename E>//vertex,edge
class Graph
{
    private:
		bool mGraph;
		Representation<V,E>* graph;

    public:
		Graph () : mGraph(false){graph = new ListRepresentation<V,E>();}//empty l-graph
		Graph (int numberOfVertex, bool _oriented, bool _representation) : mGraph(_representation)//vithout edge
		{
			if (_representation) graph = new MatrixRepresentation<V,E>(numberOfVertex, _oriented);
			else graph = new ListRepresentation<V,E>(numberOfVertex, _oriented);
		}
		Graph (int numberOfVertex, int numberOfEdge, bool _oriented, bool _representation) : mGraph(_representation)//full
		{
			if (_representation) graph = new MatrixRepresentation<V,E>(numberOfVertex, numberOfEdge, _oriented);
			else graph = new ListRepresentation<V,E>(numberOfVertex, numberOfEdge, _oriented);
		}
		Graph (Graph &one)//copy
		{
			if (one.isMForm()) graph = new MatrixRepresentation<V,E>(one);
			else graph = new ListRepresentation<V,E>(one);
		}
		~Graph (){delete graph;}

		int numberOfVertex (){return graph->numberOfVertex();}
		int numberOfEdge (){return graph->numberOfEdge();}
		bool isDirected (){return graph->isDirected();}
		bool isMForm (){return mGraph;}
		float getSaturationCoefficent (){return graph->getSaturationCoefficent();}//коэффицент насыщенности
		bool toListGraph (){}//запилить преобразование!!!
		bool toMatrixGraph (){}//запилить преобразование!!!
		bool insertVertex (){return graph->insertVertex();}
		bool deleteVertex (V _vertex1){return graph->deleteVertex(_vertex1);}
		bool insertEdge (V _vertex1, V _vertex2){return graph->insertEdge(_vertex1, _vertex2);}
		bool deleteEdge (V _vertex1, V _vertex2){return graph->deleteEdge(_vertex1, _vertex2);}
};

#endif // GRAPH_H
