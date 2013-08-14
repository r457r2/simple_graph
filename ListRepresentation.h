#ifndef LIST_REPRESENTATION_H
#define LIST_REPRESENTATION_H
#include "Representation.h"

template <typename Vertex_t, typename Edge_t>
class ListRepresentation: public Representation<Vertex_t, Edge_t>
{
private:
	QList<QList<Edge_t*> > repr;

public:
	ListRepresentation (bool _oriented = false)
	{
		this->directed = _oriented;
	}

	ListRepresentation (int numberOfVertex, bool _oriented  = false)
	{
		this->directed = _oriented;

		for (int i = 0; i < numberOfVertex; i++)
		{
			this->vertexes.append(new Vertex_t());
			this->vertexes.last()->setIndex(i);
			repr.append(QList<Edge_t*>());
		}
	}

	ListRepresentation (int numberOfVertex, int numberOfEdge, bool _oriented  = false)
	{
		this->directed = _oriented;

		for (int i = 0; i < numberOfVertex; i++)
		{
			this->vertexes.append(new Vertex_t());
			this->vertexes.last()->setIndex(i);
			repr.append(QList<Edge_t*>());
		}

		qsrand(time_t(NULL));//init
		for (int i = 0; i < numberOfEdge;)
		{
			int posBegin = qrand()%numberOfVertex;
			int posEnd = qrand()%numberOfVertex;
			if (insertEdge(this->vertexes[posBegin], this->vertexes[posEnd]) != NULL)
			{
				if (this->directed == false)
					insertEdge(this->vertexes[posEnd], this->vertexes[posBegin]);
				i++;
			}
		}

	}

	ListRepresentation (ListRepresentation &one){}//need realization

	~ListRepresentation (){}//need realization

	int edgeCount ()
	{

		int edgeCount = 0;
		if (this->directed == true)
		{
			for (int i = 0; i < this->vertexes.size(); i++)
			{
				edgeCount += repr[i].size();
			}
			return edgeCount;
		}

		int loopEdgeCount = 0;
		for (int i = 0; i < this->vertexes.size(); i++)
		{
			edgeCount += repr[i].size();
			for (int j = 0; j < repr[i].size(); j++)
			{
				if (repr[i][j]->getBegin() == repr[i][j]->getEnd())
				{
					edgeCount--;
					loopEdgeCount++;
					break;
				}
			}
		}
		return ((edgeCount / 2) + loopEdgeCount);
	}

	bool isDirected ()
	{
		return this->directed;
	}

	Vertex_t* insertVertex ()
	{
		this->vertexes.append(new Vertex_t());
		this->vertexes.last()->setIndex(this->vertexes.size() - 1);
		repr.append(QList<Edge_t*>());
		return this->vertexes.last();
	}

	bool deleteVertex (Vertex_t* _vertex1)
	{
		int pos = this->vertexes.indexOf(_vertex1);

		if (pos == -1)
			return false;

		for (int i = 0; i < this->vertexes.size(); i++)
		{
			for (int j = 0; j < repr[i].size(); j++)
			{
				if (repr[i][j]->isComingTo(_vertex1) == true)
				{
					repr[i].removeAt(j);
					break;
				}
			}
		}

		this->vertexes.removeOne(_vertex1);
		repr.removeAt(pos);

		for (; pos < this->vertexes.size(); pos++)
		{
			this->vertexes[pos]->setIndex(pos);
		}

		return true;
	}

	Edge_t* insertEdge (Vertex_t* _vertex1, Vertex_t* _vertex2)
	{
		if (((this->vertexes.contains(_vertex1)) && (this->vertexes.contains(_vertex2))) == false)
			return NULL;

		for (int i = 0; i < repr[_vertex1->getIndex()].size(); i++)
		{
			if (repr[_vertex1->getIndex()][i]->isComingTo(_vertex2) == true)
				return NULL;
		}

		repr[_vertex1->getIndex()].append(new Edge_t(_vertex1, _vertex2));
		if (this->directed == false)
			repr[_vertex2->getIndex()].append(new Edge_t(_vertex2, _vertex1));
		return repr[_vertex1->getIndex()].last();
	}

	bool deleteEdge (Vertex_t* _vertex1, Vertex_t* _vertex2)
	{
		if (this->vertexes.contains(_vertex1) == false)
			return false;
		for (int i = 0; i < repr[_vertex1->getIndex()].size(); i++)
		{
			if (repr[_vertex1->getIndex()][i]->isComingTo(_vertex2) == true)
			{
				repr[_vertex1->getIndex()].removeAt(i);

				if (this->directed == false)
				{
					for (int j = 0; j < repr[_vertex2->getIndex()].size(); j++)
					{
						if (repr[_vertex2->getIndex()][j]->isComingTo(_vertex1) == true)
						{
							repr[_vertex2->getIndex()].removeAt(j);
							break;
						}
					}
				}
				return true;
			}
		}
		return NULL;
	}
};

#endif // LIST_REPRESENTATION_H
