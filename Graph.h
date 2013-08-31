#ifndef GRAPH_H
#define GRAPH_H
#include "Representation.h"
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"

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
	typedef ListRepresentation<Vertex_t, Edge_t> ListRepr_t;
	typedef MatrixRepresentation<Vertex_t, Edge_t> MatrixRepr_t;

public:

	Graph () : type(LIST_REPR)
	{
		graph = new ListRepr_t();
	}

	Graph (int numberOfVertex, bool _directed = false, ReprType t = LIST_REPR) : type(t) // without edge
	{
		if (type == MATRIX_REPR)
			graph = new MatrixRepr_t(numberOfVertex, _directed);
		else
			graph = new ListRepr_t(numberOfVertex, _directed);
	}

	Graph (int numberOfVertex, int numberOfEdge, bool _directed = false, ReprType t = LIST_REPR) : type(t)//full
	{
		if (type == MATRIX_REPR)
			graph = new MatrixRepr_t(numberOfVertex, numberOfEdge, _directed);
		else
			graph = new ListRepr_t(numberOfVertex, numberOfEdge, _directed);
	}

	Graph (Graph &one)
	{
		if (one.type == MATRIX_REPR) graph = new MatrixRepr_t(one);
		else graph = new ListRepr_t(one);
	}

	~Graph ()
	{
		delete graph;
	}

	class VertexIterator
	{
	private:
		friend class Graph;
		typename QList<Vertex_t*>::Iterator iter;

	public:
		VertexIterator(){}

		VertexIterator& operator++ ()
		{
			iter++;
			return *this;
		}

		bool operator== (const VertexIterator& other)
		{
			return (this->iter == other.iter);
		}

		VertexIterator& operator= (const VertexIterator& other)
		{
			this->iter = other.iter;
			return *this;
		}

		bool operator!= (const VertexIterator& other)
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
		friend class Graph;
		ReprType type;
		Representation<Vertex_t, Edge_t>* graph;
		typename QList<Vertex_t*>::Iterator vertex;
		typename QList<Edge_t*>::Iterator edge;

	public:
		EdgeIterator(){}

		EdgeIterator& operator++ ()
		{
			if (type == LIST_REPR)
			{
				edge++;
				while (edge == ((ListRepr_t*)graph)->list[(*vertex)->getIndex()].end())
				{
					vertex++;
					if (vertex == graph->vertexes.end())
					{
						edge = ((ListRepr_t*)graph)->list[graph->vertexCount() - 1].end();
						break;
					}
					edge = ((ListRepr_t*)graph)->list[(*vertex)->getIndex()].begin();
				}
			}
			else
			{
				edge++;
				while (*edge == NULL
					  || edge == ((MatrixRepr_t*)graph)->matrix[(*vertex)->getIndex()].end())
				{
					if (edge == ((MatrixRepr_t*)graph)->matrix[(*vertex)->getIndex()].end())
					{
						vertex++;
						if (vertex == graph->vertexes.end())
						{
							edge = ((MatrixRepr_t*)graph)->matrix[graph->vertexCount() - 1].end();
							break;
						}
						edge = ((MatrixRepr_t*)graph)->matrix[(*vertex)->getIndex()].begin();
					}
					if(*edge == NULL)
						edge++;
				}
			}
			return *this;
		}

		// Reason to put const.
		// You write this:
		// Graph::EdgeIterator it = g.edgeBegin();
		// while (it != g.edgeEnd()) <- and compiler refuses to compile this:
		// no matching operator!=
		// It is because you cannot bind a temporary object (which is created in
		// that expression) to a non-const reference.
		// Probably. At least it compiles.
		bool operator== (const EdgeIterator& other)
		{
			return ((this->vertex == other.vertex)
					&& (this->edge == other.edge));
		}

		// Okay, put const here. But what if it is self-assignment?
		// We should spend some more time understanding this const-things.
		EdgeIterator& operator=(const EdgeIterator& other)
		{
			this->type = other.type;
			this->graph = other.graph;
			this->vertex = other.vertex;
			this->edge = other.edge;
			return *this;
		}

		bool operator!=(const EdgeIterator& other)
		{
			return ((this->vertex != other.vertex)
					|| (this->edge != other.edge));
		}

		Edge_t* operator* ()
		{
			return *edge;
		}
	};

	class OutgoingEdgeIterator
	{
	private:
		friend class Graph;
		typename QList<Edge_t*>::Iterator edge;
		const QList<Edge_t *> *row;

	public:
		OutgoingEdgeIterator(){}

		OutgoingEdgeIterator& operator++ ()
		{
			edge++;
			while(edge != row->end() && *edge == NULL)
				edge++;
			return *this;
		}

		bool operator== (const OutgoingEdgeIterator& other)
		{
			return ((this->edge == other.edge)
					&& (this->row = other.row));
		}

		OutgoingEdgeIterator& operator= (const OutgoingEdgeIterator& other)
		{
			this->edge = other.edge;
			this->row  = other.row;
			return *this;
		}

		bool operator!= (const OutgoingEdgeIterator& other)
		{
			return ((this->edge != other.edge)
					|| (this->row != other.row));
		}

		Edge_t* operator* ()
		{
			return *edge;
		}
	};

	class IncomingEdgeIterator
	{
	private:
		friend class Graph;
		Vertex_t* ptarget;
		Graph<Vertex_t, Edge_t>::EdgeIterator iter;
		Graph<Vertex_t, Edge_t> *g;

	public:
		IncomingEdgeIterator() {}
		IncomingEdgeIterator& operator++()
		{
			++iter;
			while(iter != g->edgeEnd() && !(*iter)->isComingTo(ptarget))
				++iter;
			return *this;
		}

		bool operator==(const IncomingEdgeIterator &other)
		{
			return (iter == other.iter) && (ptarget == other.ptarget);
		}

		bool operator!=(const IncomingEdgeIterator &other)
		{
			return (iter != other.iter) || (ptarget != other.ptarget);
		}

		IncomingEdgeIterator &operator=(const IncomingEdgeIterator &other)
		{
			iter = other.iter;
			g = other.g;
			ptarget = other.ptarget;
			return *this;
		}

		Edge_t *operator*()
		{
			return *iter;
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
		iter.type = type;
		iter.graph = this->graph;
		iter.vertex = this->graph->vertexes.begin();

		if (type == LIST_REPR)
		{
			iter.edge = ((ListRepr_t*)graph)->list[(*iter.vertex)->getIndex()].begin();
			while (iter.edge == ((ListRepr_t*)graph)->list[(*iter.vertex)->getIndex()].end())
			{
				iter.vertex++;
				if (iter.vertex == graph->vertexes.end())
				{
					iter.edge = ((ListRepr_t*)graph)->list[graph->vertexCount() - 1].end();
					break;
				}
				iter.edge = ((ListRepr_t*)graph)->list[(*iter.vertex)->getIndex()].begin();
			}
		}
		else
		{
			iter.edge = ((MatrixRepr_t*)graph)->matrix[(*iter.vertex)->getIndex()].begin();
			if(*iter == NULL)
				++iter;
		}
		return iter;
	}

	EdgeIterator edgeEnd ()
	{
		EdgeIterator iter;
		iter.type = type;
		iter.graph = this->graph;
		iter.vertex = this->graph->vertexes.end();
		if (type == LIST_REPR)
			iter.edge = ((ListRepr_t*)graph)->list[iter.graph->vertexCount() - 1].end();
		else
			iter.edge = ((MatrixRepr_t*)graph)->matrix[iter.graph->vertexCount() - 1].end();
		return iter;
	}

	OutgoingEdgeIterator outgoingEdgeBegin (Vertex_t* pvertex)
	{
		OutgoingEdgeIterator iter;
		if (type == LIST_REPR)
		{
			iter.row = &(((ListRepr_t*)graph)->list[pvertex->getIndex()]);
			iter.edge = ((ListRepr_t*)graph)->list[pvertex->getIndex()].begin();
		}
		else
		{
			iter.row = &(((MatrixRepr_t*)graph)->matrix[pvertex->getIndex()]);
			iter.edge = ((MatrixRepr_t*)graph)->matrix[pvertex->getIndex()].begin();
		}
		return iter;
	}

	OutgoingEdgeIterator outgoingEdgeEnd (Vertex_t* pvertex)
	{
		OutgoingEdgeIterator iter;
		if (type == LIST_REPR)
		{
			iter.row = &(((ListRepr_t*)graph)->list[pvertex->getIndex()]);
			iter.edge = ((ListRepr_t*)graph)->list[pvertex->getIndex()].end();
		}
		else
		{
			iter.row = &(((MatrixRepr_t*)graph)->matrix[pvertex->getIndex()]);
			iter.edge = ((MatrixRepr_t*)graph)->matrix[pvertex->getIndex()].end();
		}
		return iter;
	}

	IncomingEdgeIterator incomingEdgeBegin(Vertex_t *pv)
	{
		IncomingEdgeIterator iter;
		iter.g = this;
		iter.ptarget = pv;
		iter.iter = this->edgeBegin();
		if(!(*iter.iter)->isComingTo(pv))
			++iter;
		return iter;
	}

	IncomingEdgeIterator incomingEdgeEnd(Vertex_t *pv)
	{
		IncomingEdgeIterator iter;
		iter.g = this;
		iter.ptarget = pv;
		iter.iter = this->edgeEnd();
		return iter;
	}
	
	int vertexCount (){return graph->vertexCount();}
	int edgeCount (){return graph->edgeCount();}
	bool isDirected (){return graph->isDirected();}
	ReprType getType(){return type;}

	float getDensity (){return graph->getDensity();}

	bool toListGraph ()
	{
		if (type == LIST_REPR)
			return false;

		Representation<Vertex_t, Edge_t>* newGraph = new ListRepr_t(graph->isDirected());

		for (int i = 0; i < graph->vertexCount(); i++)
		{
			Vertex_t* newVertex = newGraph->insertVertex();
			*newVertex = *(graph->vertexes[i]);
		}
		for (int i = 0; i < graph->vertexCount(); i++)
		{
			for (int j = 0; j < graph->vertexCount(); j++)
			{
				if ((static_cast<MatrixRepr_t*>(graph))->matrix[i][j] != NULL)
				{
					Edge_t* newEdge = newGraph->insertEdge(newGraph->vertexes[i], newGraph->vertexes[j]);
					newEdge->setWeight() = (static_cast<MatrixRepr_t*>(graph))->matrix[i][j]->getWeight();
					newEdge->setData() = (static_cast<MatrixRepr_t*>(graph))->matrix[i][j]->getData();
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

		Representation<Vertex_t, Edge_t>* newGraph = new MatrixRepr_t(graph->isDirected());

		for (int i = 0; i < graph->edgeCount(); i++)
		{
			Vertex_t* newVertex = newGraph->insertVertex();
			*newVertex = *(graph->vertexes[i]);
		}
		for (int i = 0; i < graph->edgeCount(); i++)
		{
			for (int j = 0; j < (static_cast<ListRepr_t*>(graph))->list[i].size(); j++)
			{
				Edge_t* newEdge = newGraph->insertEdge(newGraph->vertexes[i], newGraph->vertexes[j]);
				newEdge->setWeight() = (static_cast<ListRepr_t*>(graph))->list[i][j]->getWeight();
				newEdge->setData() = (static_cast<ListRepr_t*>(graph))->list[i][j]->getData();
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
