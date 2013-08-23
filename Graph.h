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

	Graph (int numberOfVertex, bool _oriented, ReprType t = LIST_REPR) : type(t) // without edge
	{
		if (type == MATRIX_REPR)
			graph = new MatrixRepresentation<Vertex_t, Edge_t>(numberOfVertex, _oriented);
		else
			graph = new ListRepresentation<Vertex_t, Edge_t>(numberOfVertex, _oriented);
	}

	Graph (int numberOfVertex, int numberOfEdge, bool _directed, ReprType t = LIST_REPR) : type(t)//full
	{
		if (type == MATRIX_REPR)
			graph = new MatrixRepresentation<Vertex_t, Edge_t>(numberOfVertex, numberOfEdge, _directed);
		else
			graph = new ListRepresentation<Vertex_t, Edge_t>(numberOfVertex, numberOfEdge, _directed);
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

	class VertexIterator
	{
	private:
		typename QList<Vertex_t*>::Iterator iter;

	public:
		VertexIterator(){}

		VertexIterator& operator++ ()
		{
			iter++;
			return *this;
		}

		bool operator== (VertexIterator& other)
		{
			return (this->iter == other.iter);
		}

		VertexIterator& operator= (VertexIterator& other)
		{
			this->iter = other.iter;
			return *this;
		}

		bool operator!= (VertexIterator& other)
		{
			return (this->iter != other.iter);
		}

		Vertex_t* operator* ()
		{
			return *iter;
		}
	};

	class EdgeIterator
	{
	private:
		Representation<Vertex_t,Edge_t>* graph;
		typename QList<Vertex_t*>::Iterator vertex;
		typename QList<Edge_t*>::Iterator edge;

	public:
		EdgeIterator(){}

		EdgeIterator& operator++ ()
		{
			if (type == LIST_REPR)
			{
				edge++;
				while (edge == ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*vertex)->getIndex()].end())
				{
					vertex++;
					if (vertex == graph->vertexes.end())
					{
						edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[graph->vertexCount() - 1].end();
						break;
					}
					edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*vertex)->getIndex()].begin();
				}
			}
			else
			{
				edge++;
				while (*edge == NULL)
				{
					edge++;
					if (edge == ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*vertex->getIndex()].end())
					{
						vertex++;
						if (vertex == graph->vertexes.end())
						{
							edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[graph->vertexCount() - 1].end();
							break;
						}
						edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*vertex->getIndex()].begin();
					}
				}
			}
			return *this;
		}

		bool operator== (EdgeIterator& other)
		{
			return ((this->graph == other.graph) &&
					(this->vertex == other.vertex) &&
					(this->edge == other.edge));
		}

		EdgeIterator& operator= (EdgeIterator& other)
		{
			this->graph = other.graph;
			this->vertex = other.vertex;
			this->edge = other.edge;
			return *this;
		}

		bool operator!= (EdgeIterator& other)
		{
			return ((this->graph != other.graph) &&
					(this->vertex != other.vertex) &&
					(this->edge != other.edge));
		}

		Edge_t* operator* ()
		{
			return *edge;
		}
	};

	class OutgoingEdgeIterator
	{
	private:
		typename QList<Edge_t*>::Iterator edge;

	public:
		OutgoingEdgeIterator(){}

		OutgoingEdgeIterator& operator++ ()
		{
			edge++;
			return *this;
		}

		bool operator== (OutgoingEdgeIterator& other)
		{
			return (this->edge == other.edge);
		}

		OutgoingEdgeIterator& operator= (OutgoingEdgeIterator& other)
		{
			this->edge = other.edge;
			return *this;
		}

		bool operator!= (OutgoingEdgeIterator& other)
		{
			return (this->edge != other.edge);
		}

		Edge_t* operator* ()
		{
			return *edge;
		}
	};

	class IncomingEdgeIterator
	{
	private:
		Representation<Vertex_t,Edge_t>* graph;
		Vertex_t* pvertex;
		typename QList<Vertex_t*>::Iterator vertex;
		typename QList<Edge_t*>::Iterator edge;

	public:
		IncomingEdgeIterator(){}

		IncomingEdgeIterator& operator++ ()
		{
			vertex++;
			if (type == LIST_REPR)
			{
				bool isSet = false;
				if (vertex == graph->vertexes.end())
				{
					edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[graph->vertexCount() - 1].end();
					return *this;
				}
				for (; vertex != graph->vertexes.end(); vertex++)
				{
					for (edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*vertex)->getIndex()].begin();
						 edge != ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*vertex)->getIndex()].end();
						 edge++)
					{
						if (*edge->getEnd() == pvertex)
						{
							isSet = true;
							break;
						}
					}
					if (isSet)
						break;
				}
			}
			else
			{
				bool isSet = false;
				if (vertex == graph->vertexes.end())
				{
					edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[graph->vertexCount() - 1].end();
					return *this;
				}
				for (; vertex != graph->vertexes.end(); vertex++)
				{
					if (((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*vertex->getIndex()][pvertex->getIndex] != NULL)
					{
						isSet = true;
						edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*vertex->getIndex()].begin();
						edge += pvertex->getIndex();
						break;
					}
					if (isSet)
						break;
				}
				if (!isSet)
				{
					edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[graph->vertexCount() - 1].end();
				}

			}
			return *this;
		}

		bool operator== (IncomingEdgeIterator& other)
		{
			return ((this->graph == other.graph) &&
					(this->vertex == other.vertex) &&
					(this->pvertex == other.pvertex) &&
					(this->edge == other.edge));
		}

		IncomingEdgeIterator& operator= (IncomingEdgeIterator& other)
		{
			this->graph = other.graph;
			this->pvertex = other.pvertex;
			this->vertex = other.vertex;
			this->edge = other.edge;
			return *this;
		}

		bool operator!= (IncomingEdgeIterator& other)
		{
			return ((this->graph != other.graph) &&
					(this->vertex != other.vertex) &&
					(this->pvertex != other.pvertex) &&
					(this->edge != other.edge));
		}

		Edge_t* operator* ()
		{
			return *edge;
		}
	};

	VertexIterator vertexBegin ()
	{
		VertexIterator iter;
		iter.iter = graph->vertexes.begin();
		return iter;
	}

	VertexIterator vertexEnd ()
	{
		VertexIterator iter;
		iter.iter = graph->vertexes.end();
		return iter;
	}

	EdgeIterator edgeBegin ()
	{
		EdgeIterator iter;
		iter.graph = this->graph;
		iter.vertex = this->graph->vertexes.begin();

		if (type == LIST_REPR)
		{
			iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*iter.vertex)->getIndex()].begin();
			while (iter.edge == ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*iter.vertex)->getIndex()].end())
			{
				iter.vertex++;
				if (iter.vertex == graph->vertexes.end())
				{
					iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[graph->vertexCount() - 1].end();
					break;
				}
				iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[(*iter.vertex)->getIndex()].begin();
			}
		}
		else
		{
			iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*iter.vertex->getIndex()].begin();
			while (*iter.edge == NULL)
			{
				iter.edge++;
				if (iter.edge == ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*iter.vertex->getIndex()].end())
				{
					iter.vertex++;
					if (iter.vertex == graph->vertexes.end())
					{
						iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[graph->vertexCount() - 1].end();
						break;
					}
					iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*iter.vertex->getIndex()].begin();
				}
			}
		}
		return iter;
	}

	EdgeIterator edgeEnd ()
	{
		EdgeIterator iter;
		iter.graph = this->graph;
		iter.vertex = this->graph->vertexes.end();
		if (type == LIST_REPR)
			iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[iter.graph->vertexCount() - 1].end();
		else
			iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[iter.graph->vertexCount() - 1].end();
		return iter;
	}

	OutgoingEdgeIterator outgoingEdgeBegin (Vertex_t* pvertex)
	{
		OutgoingEdgeIterator iter;
		if (type == LIST_REPR)
			iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[pvertex->getIndex()].begin();
		else
			iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[pvertex->getIndex()].begin();
		return iter;
	}

	OutgoingEdgeIterator outgoingEdgeEnd (Vertex_t* pvertex)
	{
		OutgoingEdgeIterator iter;
		if (type == LIST_REPR)
			iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[pvertex->getIndex()].end();
		else
			iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[pvertex->getIndex()].end();
		return iter;
	}

	IncomingEdgeIterator incomingEdgeBegin (Vertex_t* pvertex)
	{
		IncomingEdgeIterator iter;
		iter.graph = this->graph;
		iter.pvertex = pvertex;
		iter.vertex = this->graph->vertexes.begin();

		if (type == LIST_REPR)
		{
			bool isSet = false;
			for (typename QList<Vertex_t*>::Iterator i = iter.graph->vertexes.begin(); i != iter.graph->vertexes.end(); i++)
			{
				for (typename QList<Edge_t*>::Iterator j = ((ListRepresentation<Vertex_t,Edge_t>*)(iter.graph))->list[(*i)->getIndex()].begin();
					 j != ((ListRepresentation<Vertex_t,Edge_t>*)(iter.graph))->list[(*i)->getIndex()].end();
					 j++)
				{
					if (*j->getEnd() == pvertex)
					{
						isSet = true;
						iter.edge = j;
						break;
					}
				}
				if (isSet)
					break;
			}
		}
		else
		{
			bool isSet = false;
			for (typename QList<Vertex_t*>::Iterator i = iter.graph->vertexes.begin(); i != iter.graph->vertexes.end(); i++)
			{
				if (((MatrixRepresentation<Vertex_t,Edge_t>*)(iter.graph))->matrix[*i->getIndex()][pvertex->getIndex] != NULL)
				{
					isSet = true;
					iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[*iter.vertex->getIndex()].begin();
					iter.edge += iter.pvertex->getIndex();
					break;
				}
				if (isSet)
					break;
			}
			if (!isSet)
			{
				iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)(iter.graph))->matrix[iter.graph->vertexCount() - 1].end();
			}

		}
		return iter;
	}

	IncomingEdgeIterator incomingEdgeEnd (Vertex_t* pvertex)
	{
		IncomingEdgeIterator iter;
		iter.graph = this->graph;
		iter.pvertex = pvertex;
		iter.vertex = this->graph->vertexes.end();
		if (type == LIST_REPR)
			iter.edge = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[iter.graph->vertexCount() - 1].end();
		else
			iter.edge = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[iter.graph->vertexCount() - 1].end();
		return iter;
	}
	
	int vertexCount (){return graph->vertexCount();}
	int edgeCount (){return graph->edgeCount();}
	bool isDirected (){return graph->isDirected();}
	ReprType getType(){return type;}

	float getSaturationCoefficent (){return graph->getSaturationCoefficent();}

	bool toListGraph ()
	{
		if (type == LIST_REPR)
			return false;

		Representation<Vertex_t,Edge_t>* newGraph = new ListRepresentation<Vertex_t,Edge_t>(graph->isDirected());

		for (int i = 0; i < graph->edgeCount(); i++)
		{
			Vertex_t* newVertex = newGraph->insertVertex();
			*newVertex = *(graph->vertexes[i]);
		}
		for (int i = 0; i < graph->edgeCount(); i++)
		{
			for (int j = 0; j < ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[i].size(); j++)
			{
				if (graph->list[i][j] != NULL)
				{
					Edge_t* newEdge = newGraph->insertEdge(newGraph->vertexes[i], newGraph->vertexes[j]);
					newEdge->setWeight() = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[i][j]->getWeight();
					newEdge->setData() = ((ListRepresentation<Vertex_t,Edge_t>*)graph)->list[i][j]->getData();
				}
			}
		}

		delete graph;
		type = MATRIX_REPR;
		graph = newGraph;

		return true;
	}

	bool toMatrixGraph ()
	{
		if (type == MATRIX_REPR)
			return false;

		Representation<Vertex_t,Edge_t>* newGraph = new MatrixRepresentation<Vertex_t,Edge_t>(graph->isDirected());

		for (int i = 0; i < graph->edgeCount(); i++)
		{
			Vertex_t* newVertex = newGraph->insertVertex();
			*newVertex = *(graph->vertexes[i]);
		}
		for (int i = 0; i < graph->edgeCount(); i++)
		{
			for (int j = 0; j < ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[i].size(); j++)
			{
				Edge_t* newEdge = newGraph->insertEdge(newGraph->vertexes[i], newGraph->vertexes[j]);
				newEdge->setWeight() = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[i][j]->getWeight();
				newEdge->setData() = ((MatrixRepresentation<Vertex_t,Edge_t>*)graph)->matrix[i][j]->getData();
			}
		}

		delete graph;
		type = LIST_REPR;
		graph = newGraph;

		return true;
	}

	Vertex_t* insertVertex (){return graph->insertVertex();}
	bool deleteVertex (Vertex_t *_vertex1){return graph->deleteVertex(_vertex1);}
	Edge_t* insertEdge (Vertex_t *_vertex1, Vertex_t *_vertex2){return graph->insertEdge(_vertex1, _vertex2);}
	bool deleteEdge (Vertex_t *_vertex1, Vertex_t *_vertex2){return graph->deleteEdge(_vertex1, _vertex2);}
};

#endif // GRAPH_H
