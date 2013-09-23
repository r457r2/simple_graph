#ifndef GRAPH_H
#define GRAPH_H
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "Representation.h"
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"

#include "QDebug"

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
	Representation<Vertex_t, Edge_t>* pgraph;
	typedef ListRepresentation<Vertex_t, Edge_t> ListRepr_t;
	typedef MatrixRepresentation<Vertex_t, Edge_t> MatrixRepr_t;

public:

	Graph () : type(LIST_REPR)
	{
		pgraph = new ListRepr_t();
	}

	Graph (int numberOfVertex, bool _directed = false, ReprType t = LIST_REPR) : type(t) // without edge
	{
		if (type == MATRIX_REPR)
			pgraph = new MatrixRepr_t(numberOfVertex, _directed);
		else
			pgraph = new ListRepr_t(numberOfVertex, _directed);
	}

	Graph (int numberOfVertex, int numberOfEdge, bool _directed = false, ReprType t = LIST_REPR) : type(t)//full
	{
		if (type == MATRIX_REPR)
			pgraph = new MatrixRepr_t(numberOfVertex, numberOfEdge, _directed);
		else
			pgraph = new ListRepr_t(numberOfVertex, numberOfEdge, _directed);
	}

	Graph (Graph &one)
	{
		this->type = one.type;
		if (one.type == MATRIX_REPR)
			pgraph = new MatrixRepr_t(*static_cast<MatrixRepr_t *>(one.pgraph));
		else
			pgraph = new ListRepr_t(*static_cast<ListRepr_t *>(one.pgraph));
	}

	~Graph ()
	{
		delete pgraph;
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
			while(!graph->isDirected()
				&& edge != ((MatrixRepr_t*)graph)->matrix[graph->vertexCount() - 1].end()
				&& (*edge)->getBegin()->getIndex() > (*edge)->getEnd()->getIndex())
				this->operator++();
			return *this;
		}

		bool operator== (const EdgeIterator& other)
		{
			return ((this->vertex == other.vertex)
					&& (this->edge == other.edge));
		}

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
		iter.iter = pgraph->vertexes.begin();
		return iter;
	}

	VertexIterator vertexEnd ()
	{
		VertexIterator iter;
		iter.iter = pgraph->vertexes.end();
		return iter;
	}

	EdgeIterator edgeBegin ()
	{
		EdgeIterator iter;
		iter.type = type;
		iter.graph = this->pgraph;
		iter.vertex = this->pgraph->vertexes.begin();

		if (type == LIST_REPR)
		{
			iter.edge = ((ListRepr_t*)pgraph)->list[(*iter.vertex)->getIndex()].begin();
			while (iter.edge == ((ListRepr_t*)pgraph)->list[(*iter.vertex)->getIndex()].end())
			{
				iter.vertex++;
				if (iter.vertex == pgraph->vertexes.end())
				{
					iter.edge = ((ListRepr_t*)pgraph)->list[pgraph->vertexCount() - 1].end();
					break;
				}
				iter.edge = ((ListRepr_t*)pgraph)->list[(*iter.vertex)->getIndex()].begin();
			}
		}
		else
		{
			iter.edge = ((MatrixRepr_t*)pgraph)->matrix[(*iter.vertex)->getIndex()].begin();
			if(*iter == NULL)
				++iter;
		}
		return iter;
	}

	EdgeIterator edgeEnd ()
	{
		EdgeIterator iter;
		iter.type = type;
		iter.graph = this->pgraph;
		iter.vertex = this->pgraph->vertexes.end();
		if (type == LIST_REPR)
			iter.edge = ((ListRepr_t*)pgraph)->list[iter.graph->vertexCount() - 1].end();
		else
			iter.edge = ((MatrixRepr_t*)pgraph)->matrix[iter.graph->vertexCount() - 1].end();
		return iter;
	}

	OutgoingEdgeIterator outgoingEdgeBegin (Vertex_t* pvertex)
	{
		if (!pgraph->belongs(pvertex))
			throw std::runtime_error("outgoingEdgeBegin");

		OutgoingEdgeIterator iter;
		if (type == LIST_REPR)
		{
			iter.row = &(((ListRepr_t*)pgraph)->list[pvertex->getIndex()]);
			iter.edge = ((ListRepr_t*)pgraph)->list[pvertex->getIndex()].begin();
		}
		else
		{
			iter.row = &(((MatrixRepr_t*)pgraph)->matrix[pvertex->getIndex()]);
			iter.edge = ((MatrixRepr_t*)pgraph)->matrix[pvertex->getIndex()].begin();
			if(*(iter.edge) == NULL)
				while(iter.edge != iter.row->end() && *(iter.edge) == NULL)
					++(iter.edge);
		}
		return iter;
	}

	OutgoingEdgeIterator outgoingEdgeEnd (Vertex_t* pvertex)
	{
		if (!pgraph->belongs(pvertex))
			throw std::runtime_error("outgoingEdgeEnd");

		OutgoingEdgeIterator iter;
		if (type == LIST_REPR)
		{
			iter.row = &(((ListRepr_t*)pgraph)->list[pvertex->getIndex()]);
			iter.edge = ((ListRepr_t*)pgraph)->list[pvertex->getIndex()].end();
		}
		else
		{
			iter.row = &(((MatrixRepr_t*)pgraph)->matrix[pvertex->getIndex()]);
			iter.edge = ((MatrixRepr_t*)pgraph)->matrix[pvertex->getIndex()].end();
		}
		return iter;
	}

	IncomingEdgeIterator incomingEdgeBegin(Vertex_t *pvertex)
	{
		if (!pgraph->belongs(pvertex))
			throw std::runtime_error("incomingEdgeBegin");

		IncomingEdgeIterator iter;
		iter.g = this;
		iter.ptarget = pvertex;
		iter.iter = this->edgeBegin();
		if(!(*iter.iter)->isComingTo(pvertex))
			++iter;
		return iter;
	}

	IncomingEdgeIterator incomingEdgeEnd(Vertex_t *pvertex)
	{
		if (!pgraph->belongs(pvertex))
			throw std::runtime_error("incomingEdgeEnd");

		IncomingEdgeIterator iter;
		iter.g = this;
		iter.ptarget = pvertex;
		iter.iter = this->edgeEnd();
		return iter;
	}
	
	int vertexCount (){return pgraph->vertexCount();}
	int edgeCount (){return pgraph->edgeCount();}
	bool isDirected (){return pgraph->isDirected();}
	ReprType getType(){return type;}

	float getDensity (){return pgraph->getDensity();}

	void toListGraph ()
	{
		if (type == LIST_REPR)
			return;

		Representation<Vertex_t, Edge_t>* newGraph = new ListRepr_t(pgraph->isDirected());
		MatrixRepr_t *old_repr = static_cast<MatrixRepr_t *>(pgraph);

		for (int i = 0; i < pgraph->vertexCount(); i++)
		{
			Vertex_t* newVertex = newGraph->insertVertex();
			*newVertex = *(pgraph->vertexes[i]);
		}
		for (int i = 0; i < pgraph->vertexCount(); i++)
		{
			for (int j = 0; j < pgraph->vertexCount(); j++)
			{
				if (old_repr->matrix[i][j] != NULL)
				{
					Edge_t* newEdge = newGraph->insertEdge(newGraph->vertexes[i], newGraph->vertexes[j]);
					if(!pgraph->isDirected() && i > j) // i >= j ?
						newEdge = newGraph->getEdge(newGraph->vertexes[i], newGraph->vertexes[j]);
					newEdge->setWeight((static_cast<MatrixRepr_t*>(pgraph))->matrix[i][j]->getWeight());
					newEdge->setData((static_cast<MatrixRepr_t*>(pgraph))->matrix[i][j]->getData());
				}
			}
		}

		delete pgraph;
		type = LIST_REPR;
		pgraph = newGraph;
	}

	void toMatrixGraph ()
	{
		if (type == MATRIX_REPR)
			return;

		Representation<Vertex_t, Edge_t>* newGraph = new MatrixRepr_t(pgraph->isDirected());
		ListRepr_t *old_repr = static_cast<ListRepr_t *>(pgraph);

		for (int i = 0; i < pgraph->vertexCount(); i++)
		{
			Vertex_t* newVertex = newGraph->insertVertex();
			*newVertex = *(pgraph->vertexes[i]);
		}
		for (int i = 0; i < pgraph->vertexCount(); i++)
		{
			for (int j = 0; j < old_repr->list[i].size(); j++)
			{
				int index = old_repr->list[i][j]->getEnd()->getIndex();
				Edge_t* newEdge = newGraph->insertEdge(newGraph->vertexes[i], newGraph->vertexes[index]);
				if(!pgraph->isDirected() && i > index) // >= ?
					newEdge = newGraph->getEdge(newGraph->vertexes[i], newGraph->vertexes[index]);
				newEdge->setWeight(old_repr->list[i][j]->getWeight());
				newEdge->setData(old_repr->list[i][j]->getData());
			}
		}

		delete pgraph;
		type = MATRIX_REPR;
		pgraph = newGraph;
	}

	void printInnerStructure()
	{
		if(type == MATRIX_REPR)
		{
			MatrixRepr_t *mgraph = static_cast<MatrixRepr_t *>(pgraph);

			typename QList<Vertex_t *>::ConstIterator vi = mgraph->vertexes.constBegin();
			std::cout << std::setw(4) << "";
			for(; vi != mgraph->vertexes.constEnd(); ++vi)
				std::cout << std::setw(2) << std::right << (*vi)->getUserIndex() << " ";
			std::cout << std::endl;

			vi = mgraph->vertexes.constBegin();
			for(int i = 0; i < mgraph->matrix.count(); ++i, ++vi)
			{
				std::cout << std::setw(2) << std::right << (*vi)->getUserIndex() << ": ";
				for(int j = 0; j < mgraph->matrix[i].count(); ++j)
					std::cout << std::setw(2) << std::right << ((mgraph->matrix[i][j]) ? 'x' : '-') << " ";
				std::cout << std::endl;
			}
		}
		else
		{
			ListRepr_t *lgraph = static_cast<ListRepr_t *>(pgraph);
			typename QList<QList<Edge_t*> >::ConstIterator i;
			int inner_idx = 0;
			for(i = lgraph->list.constBegin(); i != lgraph->list.constEnd(); ++i, ++inner_idx)
			{
				std::cout << std::setw(5) << std::right << lgraph->vertexes[inner_idx]->getUserIndex() << ": ";
				typename QList<Edge_t *>::ConstIterator j;
				for(j = (*i).constBegin(); j != (*i).constEnd(); ++j)
				{
					std::cout << (*j)->getBegin()->getUserIndex() << "->" << (*j)->getEnd()->getUserIndex() << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	Vertex_t* getVertexByIndex(int index){return pgraph->getVertexByIndex(index);}
	Vertex_t* insertVertex (){return pgraph->insertVertex();}
	bool deleteVertex (Vertex_t *_pvertex1){return pgraph->deleteVertex(_pvertex1);}
	Edge_t* insertEdge (Vertex_t *_pvertex1, Vertex_t *_pvertex2){return pgraph->insertEdge(_pvertex1, _pvertex2);}
	bool deleteEdge (Vertex_t *_pvertex1, Vertex_t *_pvertex2){return pgraph->deleteEdge(_pvertex1, _pvertex2);}
	Edge_t* getEdge (Vertex_t *_pvertex1, Vertex_t *_pvertex2){return pgraph->getEdge(_pvertex1, _pvertex2);}
};

#endif // GRAPH_H
